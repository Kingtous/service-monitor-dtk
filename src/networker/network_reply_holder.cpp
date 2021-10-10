#include "network_reply_holder.h"

namespace networker {
namespace http {

NetworkReplyHolder::NetworkReplyHolder(QObject* parent)
  : QObject(parent)
{
  this->stat = new NetworkStat();
}

void
NetworkReplyHolder::logLatency(const ServiceItem& item, qint64 latency)
{}

NetworkStat*
NetworkReplyHolder::getStat() const
{
  return stat;
}

} // namespace http
} // namespace networker
