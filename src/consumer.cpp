#include "consumer.h"

#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <log4qt/logger.h>

Consumer& Consumer::fromJson(const QByteArray& _json, Consumer& _consumer)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(_json, &error);
    if (error.error == QJsonParseError::ParseError::NoError)
    {
        QJsonObject root = doc.object();
        _consumer.setName(root["consumerName"].toString());
        _consumer.setMsgRateOut(root["msgRateOut"].toDouble());
        _consumer.setMsgThroughputOut(root["msgThroughputOut"].toDouble());
        _consumer.setAddress(root["address"].toString());
        _consumer.setConnectedSince(root["connectedSince"].toString());
    }
    return _consumer;
}

ConsumerData Consumer::toData() const
{
    ConsumerData data;
    data["name"] = this->name();
    data["outRate"] = QString::number(this->msgRateOut(), 'f', 2);
    data["outThroughput"] = QString::number(this->msgThroughputOut(), 'f', 2);
    data["avgMsgSize"] = QString::number(this->averageMsgSize(), 'f', 2);
    data["address"] = this->address();
    data["since"] = this->connectedSince();
    return data;
}
