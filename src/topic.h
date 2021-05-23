#ifndef TOPIC_H
#define TOPIC_H

#include <QObject>

#include "namespace.h"
#include "producer.h"
#include "subscription.h"

class TopicStats
{
public:
    explicit TopicStats();
    TopicStats(const TopicStats& _other) { *this = _other; }
    TopicStats& operator=(const TopicStats& _other);

    inline int partitions() const { return this->m_Partitions; }
    inline void setPartitions(const int& _partitions) { this->m_Partitions = _partitions; }

    inline int producerNum() const { return this->m_ProducerNum; }
    inline void setProducerNum(const int& _producers) { this->m_ProducerNum = _producers; }

    inline int subscriptionNum() const { return this->m_SubscriptionNum; }
    inline void setSubscriptionNum(const int& _subscriptions) { this->m_SubscriptionNum = _subscriptions; }

    inline int storageSize() const { return this->m_StorageSize; }
    inline void setStorageSize(const int& _storageSize) { this->m_StorageSize = _storageSize; }

    inline int entryNum() const { return this->m_EntryNum; }
    inline void setEntryNum(const int& _entries) { this->m_EntryNum = _entries; }

    inline QList<Producer> publishers() const { return this->m_Publishers; }
    inline QList<Subscription> subscriptions() const { return this->m_Subscriptions; }

    static TopicStats fromJson(const QByteArray& json);
    void addProducer(const Producer& _producer) { this->m_Publishers.append(_producer); }
    void addSubscription(const Subscription& _subscription) { this->m_Subscriptions.append(_subscription); }

private:
    int m_Partitions;
    int m_ProducerNum;
    int m_SubscriptionNum;
    int m_StorageSize;
    int m_EntryNum;
    QList<Producer> m_Publishers;
    QList<Subscription> m_Subscriptions;

};

Q_DECLARE_METATYPE(TopicStats);

class Topic
{
public:
    enum TopicPartitioned
    {
        Partitioned = 0x0,
        NonPartitioned = 0x1,
    };

    explicit Topic();
    Topic(const QString& _name, const Namespace& _namespace);
    Topic(const Topic& _other) { *this = _other; }
    Topic& operator=(const Topic& _other);
    friend bool operator==(const Topic& _one, const Topic& _other) { return _one.name() == _other.name() && _one.getNamespace() == _other.getNamespace(); }

    inline QString name() const { return this->m_Name; }
    inline void setName(const QString& _name) { this->m_Name = _name; }

    inline QString role() const { return this->m_Role; }
    inline void setRole(const QString& _role) { this->m_Role = _role; }

    inline QStringList auths() const { return this->m_Auths; }
    inline void setAuths(const QStringList& _auth) { this->m_Auths = _auth; }

    inline Namespace getNamespace() const { return this->m_Namespace; }
    inline void setNamespace(const Namespace& _namespace) { this->m_Namespace = _namespace; }

    inline TopicStats stats() const { return  this->m_Stats; }
    inline void setStats(const TopicStats& _stats) { this->m_Stats = _stats; }

    inline QString domain() const { return this->m_Domain; }
    inline void setDomain(const QString& _domain) { this->m_Domain = _domain; }

    inline Topic::TopicPartitioned partitioned() const { return this->m_Partitioned; }
    inline void setPartitioned(const Topic::TopicPartitioned& _partitioned) { this->m_Partitioned = _partitioned; }

    inline QString schema() const { return this->m_Schema; }
    inline void setSchema(const QString& _schema) { this->m_Schema = _schema; }

    inline int partitions() const { return this->m_Partitions; }
    inline void setPartitions(const int& _partitions) { this->m_Partitions = _partitions; }

    QString formatName() const;

private:
    QString m_Name;
    Namespace m_Namespace;
    QString m_Domain;
    QString m_Schema;
    QString m_Role;
    QStringList m_Auths;
    TopicStats m_Stats;
    Topic::TopicPartitioned m_Partitioned;
    int m_Partitions;
};

Q_DECLARE_METATYPE(Topic);

typedef QMap<QString, QString> TopicSegmentData;

class TopicSegment
{
public:
    enum Status
    {
        OPEN = 0, CLOSE
    };

    explicit TopicSegment() {};
    TopicSegment(const TopicSegment& _other) { *this = _other; };
    TopicSegment& operator=(const TopicSegment& _other);

    inline void setLedgerId(const int& _ledgerId) { this->m_LedgerId = _ledgerId; }
    inline int ledgerId() const { return this->m_LedgerId; }

    inline void setEntries(const int& _entries) { this->m_Entries = _entries; }
    inline int entries() const { return this->m_Entries; }

    inline void setSize(const int& _size) { this->m_Size = _size; }
    inline int size() const { return this->m_Size; }

    inline void setStatus(const TopicSegment::Status& _status) { this->m_Status = _status; }
    inline TopicSegment::Status status() const { return this->m_Status; }

    inline void setOffload(const bool& _offload) { this->m_Offload = _offload; }
    inline bool offload() const { return this->m_Offload; }

    TopicSegmentData toData() const;

private:
    int m_LedgerId;
    int m_Entries;
    int m_Size;
    TopicSegment::Status m_Status;
    bool m_Offload;

};

Q_DECLARE_METATYPE(TopicSegment);

typedef QList<TopicSegment> TopicSegments;

class TopicStorage
{
public:
    explicit TopicStorage() {};
    TopicStorage(const TopicStorage& _other) { *this = _other; };
    TopicStorage& operator=(const TopicStorage& _other);

    inline void setStorageSize(const int& _storageSize) { this->m_StorageSize = _storageSize; }
    inline int storageSize() const { return this->m_StorageSize; }

    inline void setEntryNum(const int& _entryNum) { this->m_EntryNum = _entryNum; }
    inline int entryNum() const { return this->m_EntryNum; }

    inline void setSegmentNum(const int& _segmentNum) { this->m_SegmentNum = _segmentNum; }
    inline int segmentNum() const { return this->m_SegmentNum; }

    inline void setSegments(const TopicSegments& _segments) { this->m_Segments = _segments; }
    inline TopicSegments segments() const { return this->m_Segments; }

private:
    int m_StorageSize;
    int m_EntryNum;
    int m_SegmentNum;
    TopicSegments m_Segments;

};

Q_DECLARE_METATYPE(TopicStorage);

#endif // TOPIC_H
