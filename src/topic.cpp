#include "topic.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

TopicStats::TopicStats() : m_Partitions(0), m_ProducerNum(0), m_SubscriptionNum(0), m_StorageSize(0), m_EntryNum(0) {}

TopicStats& TopicStats::operator =(const TopicStats& _other)
{
    this->m_Partitions = _other.partitions();
    this->m_ProducerNum = _other.producerNum();
    this->m_SubscriptionNum = _other.subscriptionNum();
    this->m_EntryNum = _other.entryNum();
    this->m_StorageSize = _other.storageSize();
    this->m_Publishers = _other.publishers();
    this->m_Subscriptions = _other.subscriptions();
    return *this;
}

TopicStats TopicStats::fromJson(const QByteArray& json)
{
    TopicStats stats;
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(json, &error);
    if (error.error == QJsonParseError::ParseError::NoError)
    {
        QJsonObject root = doc.object();
        QJsonArray publishers = root["publishers"].toArray();
        stats.setProducerNum(publishers.size());
        QJsonObject subscriptions = root["subscriptions"].toObject();
        stats.setSubscriptionNum(subscriptions.size());
        stats.setStorageSize(root["storageSize"].toInt(0));
        stats.setEntryNum(root["msgInCounter"].toInt(0));
    }
    return stats;
}

Topic::Topic() : m_Name(QString()), m_Domain(QString()), m_Schema(QString()), m_Role(QString()), m_Partitioned(Topic::NonPartitioned), m_Partitions(-1) {}

Topic::Topic(const QString& _name, const Namespace& _namespace) : m_Name(_name), m_Namespace(_namespace), m_Domain(QString()), m_Schema(QString()), m_Role(QString()), m_Partitioned(Topic::NonPartitioned), m_Partitions(-1) {}

Topic& Topic::operator =(const Topic& _other)
{
    this->m_Name = _other.name();
    this->m_Namespace = _other.getNamespace();
    this->m_Role = _other.role();
    this->m_Auths = _other.auths();
    this->m_Stats = _other.stats();
    this->m_Domain = _other.domain();
    this->m_Schema = _other.schema();
    this->m_Partitions = _other.partitions();
    this->m_Partitioned = _other.partitioned();
    return *this;
}

QString Topic::formatName() const
{
    return QString("%1://%2/%3/%4").arg(this->domain(), this->getNamespace().tenant().name(), this->getNamespace().name(), this->name());
}

TopicSegment& TopicSegment::operator=(const TopicSegment& _other)
{
    this->m_LedgerId = _other.ledgerId();
    this->m_Entries = _other.entries();
    this->m_Status = _other.status();
    this->m_Size = _other.size();
    this->m_Offload = _other.offload();
    return *this;
}

TopicSegmentData TopicSegment::toData() const
{
    TopicSegmentData data;
    data["ledgerId"] = QString::number(this->ledgerId());
    data["entries"] = QString::number(this->entries());
    data["size"] = this->size() > 1024.0 ? QString::number(qRound(this->size() / 1024.0)).append("KB") : QString::number(this->size()).append("Bytes");
    QString status = this->status() == TopicSegment::Status::OPEN ? QString("opening") : QString("closing");
    data["status"] = status;
    data["offload"] = this->offload() ? QString("true") : QString("false");
    return data;
}

TopicStorage& TopicStorage::operator=(const TopicStorage& _other)
{
    this->m_StorageSize = _other.storageSize();
    this->m_SegmentNum = _other.segmentNum();
    this->m_EntryNum = _other.entryNum();
    this->m_Segments = _other.segments();
    return *this;
}
