#ifndef NETWORKER_HTTP_NETWORKREPLYHOLDER_H
#define NETWORKER_HTTP_NETWORKREPLYHOLDER_H

#include "servicegroup.h"
#include "serviceitem.h"

#include <DSingleton>
#include <QObject>

DCORE_USE_NAMESPACE

namespace networker {
namespace http {
struct NetworkStat;

/// TODO: 网络响应Holder，可以用于统计数据
class NetworkReplyHolder : public QObject
{
  Q_OBJECT
public:
  friend class DSingleton<NetworkReplyHolder>;
  explicit NetworkReplyHolder(QObject* parent = nullptr);

  NetworkStat* getStat() const;

public slots:
  void logLatency(const ServiceItem& item, qint64 latency);

private:
  NetworkStat* stat;
};

struct NetworkRequestTaskStat;

/// 网络统计信息
struct NetworkStat
{
  // <name,NetworkRequestTaskStat>
    QMap<QString, NetworkRequestTaskStat>* stats;
};

//
struct NetworkRequestTaskStat
{
  int times{ 0 };
  double totalLatency{ 0.0 };
};

} // namespace http
} // namespace networker

#endif // NETWORKER_HTTP_NETWORKREPLYHOLDER_H
