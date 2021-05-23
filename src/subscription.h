#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <QObject>

#include "consumer.h"

typedef QMap<QString, QString> SubscriptionData;

class Subscription
{
public:
    explicit Subscription() : m_Name(QString()), m_Type(QString()), m_MsgBacklog(0), m_MsgRateOut(0.0), m_MsgThroughputOut(0.0), m_MsgRateExpired(0.0) {}
    Subscription(const Subscription& _other) { *this = _other; }
    Subscription& operator=(const Subscription& _other)
    {
        this->m_Name = _other.name();
        this->m_Type = _other.type();
        this->m_MsgBacklog = _other.msgBacklog();
        this->m_MsgRateOut = _other.msgRateOut();
        this->m_MsgThroughputOut = _other.msgThroughputOut();
        this->m_MsgRateExpired = _other.msgRateExpired();
        this->m_Consumers = _other.consumers();
        return *this;
    }

    inline void setName(const QString& _name) { this->m_Name = _name; }
    inline QString name() const { return this->m_Name; }

    inline void setType(const QString& _type) { this->m_Type = _type; }
    inline QString type() const { return this->m_Type; }

    inline void setMsgBacklog(const int& _msgBacklog) { this->m_MsgBacklog = _msgBacklog; }
    inline int msgBacklog() const { return this->m_MsgBacklog; }

    inline double msgRateOut() const { return this->m_MsgRateOut; }
    inline void setMsgRateOut(const double& _msgRateOut) { this->m_MsgRateOut = _msgRateOut; }

    inline double msgThroughputOut() const { return this->m_MsgThroughputOut; }
    inline void setMsgThroughputOut(const double& _msgThroughputOut) { this->m_MsgThroughputOut = _msgThroughputOut; }

    inline double msgRateExpired() const { return this->m_MsgRateExpired; }
    inline void setMsgRateExpired(const double& _msgRateExpired) { this->m_MsgRateExpired = _msgRateExpired; }

    inline QList<Consumer> consumers() const { return this->m_Consumers; }

    static Subscription& fromJson(const QByteArray&, Subscription&);
    inline void addConsumer(const Consumer& _consumer) { this->m_Consumers << _consumer; }
    SubscriptionData toData() const;

private:
    QString m_Name;
    QString m_Type;
    int m_MsgBacklog;
    double m_MsgRateOut;
    double m_MsgThroughputOut;
    double m_MsgRateExpired;
    QList<Consumer> m_Consumers;

};

Q_DECLARE_METATYPE(Subscription);

#endif // SUBSCRIPTION_H
