#include "sink.h"

Sink::Sink() : BaseFunction() {}

Sink& Sink::operator=(const Sink& _other)
{
    BaseFunction::operator=(_other);
    this->m_Inputs = _other.inputs();
    return *this;
}

Sink::~Sink() {}

QByteArray Sink::toJson() const
{
    QJsonObject root;
    root = createRoot(root);
    root["inputs"] = QJsonArray::fromStringList(this->inputs());
    QJsonObject configs;
    FunctionConfig::const_iterator it;
    FunctionConfig config = this->config();
    for (it = config.constBegin(); it != config.constEnd(); ++it)
        configs.insert(it.key(), it.value());
    root["configs"] = configs;
    QJsonDocument doc = QJsonDocument::fromVariant(root);
    return doc.toJson(QJsonDocument::JsonFormat::Compact);
}

void Sink::appendStatus(const QByteArray& _json)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(_json, &error);
    if (error.error == QJsonParseError::ParseError::NoError)
    {
        QJsonObject root = doc.object();
        setInstanceNum(root["numInstances"].toInt(-1));
        setRunningNum(root["numRunning"].toInt(-1));
    }
}

void Sink::appendInfo(const QByteArray& _json)
{
    BaseFunction::appendInfo(_json);

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(_json, &error);
    if (error.error == QJsonParseError::ParseError::NoError)
    {
        QJsonObject root = doc.object();
        QJsonObject inputs = root["inputSpecs"].toObject();
        QJsonObject::const_iterator it;
        for (it = inputs.constBegin(); it != inputs.constEnd(); ++it)
        {
            addInput(it.key());
        }
    }
}

SinkData Sink::toData() const
{
    SinkData data;
    data["tenant"] = this->getNamespace().tenant().name();
    data["namesapces"] = this->getNamespace().name();
    data["name"] = this->name();
    data["inputs"] = this->inputs().join(",");
    data["instanceNum"] = QString::number(this->instanceNum());
    data["runningNum"] = QString::number(this->runningNum());
    return data;
}
