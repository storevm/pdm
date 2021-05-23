#include "subscription.h"

#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <log4qt/logger.h>

Subscription& Subscription::fromJson(const QByteArray& _json, Subscription& _subscription)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(_json, &error);
    if (error.error == QJsonParseError::ParseError::NoError)
    {
        QJsonObject root = doc.object();
        _subscription.setType(root["type"].toString());
        _subscription.setMsgRateOut(root["msgRateOut"].toDouble());
        _subscription.setMsgThroughputOut(root["msgThroughputOut"].toDouble());
        _subscription.setMsgRateExpired(root["msgRateExpired"].toDouble());
        _subscription.setMsgBacklog(root["msgBacklog"].toInt());

        QJsonArray consumers = root["consumers"].toArray();
        for (int i = 0, n = consumers.size(); i < n; ++i)
        {
            QJsonObject obj = consumers[i].toObject();
            QJsonDocument _doc(obj);
            Consumer consumer;
            consumer = Consumer::fromJson(_doc.toJson(), consumer);
            _subscription.addConsumer(consumer);
        }
    }
    return _subscription;
}

SubscriptionData Subscription::toData() const
{
    SubscriptionData data;
    data.insert(QString("name"), this->name());
    data.insert(QString("type"), this->type());
    data.insert(QString("outRate"), QString::number(this->msgRateOut(), 'f', 2));
    data.insert(QString("outThroughput"), QString::number(this->msgThroughputOut(), 'f', 2));
    data.insert(QString("msgExpired"), QString::number(this->msgRateExpired(), 'f', 2));
    data.insert(QString("backlog"), QString::number(this->msgBacklog()));
    return data;
}
