#!/bin/bash

ARCH=""

if [[ -n $1 ]]; then
	ARCH=$1
else
	echo "Usage: ./build-package.sh [amd64|arm64]"
	exit
fi

QT_VERSION=qt5
QT_SELECT=${QT_VERSION} sh -c "qmake && make -j4"
INSTALL_LOCATION=$PWD/build/opt/apps/cn.kingtous.service-monitor/files/bin

if [[ -f $PWD/src/service_monitor ]]; 
then
	chmod -R 755 $PWD/build
	mkdir -p $INSTALL_LOCATION
	cp $PWD/src/service_monitor $INSTALL_LOCATION
	# edit arch
	sed -i "3c\Architecture: ${ARCH}" $PWD/build/DEBIAN/control
	# build debs
	dpkg-deb -b ./build
	mv build.deb cn.kingtous.service-monitor.deb
else
	echo "service monitor binary file not found. Compilation Failed."
fi