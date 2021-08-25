#include "servicegrouprepo.h"

const QList<ServiceGroup> &ServiceGroupRepo::getServiceGroups() {
  if (serviceGroups.length() == 0) {
    // 获取一下看看是不是没有读取
  }
  return this->serviceGroups;
}

ServiceGroupRepo::ServiceGroupRepo() {}
