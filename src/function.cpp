#include "function.h"

FunctionStatus::FunctionStatus() : m_InstanceId(-1), m_Status(false) {}

FunctionStatus& FunctionStatus::operator =(const FunctionStatus& _other)
{
    this->m_InstanceId = _other.instanceId();
    this->m_Status = _other.status();
    return *this;
}

Function::Function() : BaseFunction(),  m_Classname(QString()), m_Inputs(QString()), m_Output(QString()) {}

Function& Function::operator =(const Function& _other)
{
    BaseFunction::operator=(_other);
    this->m_Classname = _other.classname();
    this->m_Inputs = _other.inputs();
    this->m_Output = _other.output();
    return *this;
}

QByteArray Function::toJson() const
{
    QVariantMap root;
    QStringList slist = this->m_Inputs.split(",");
    root.insert("inputs", slist);
    root.insert("output", this->m_Output);
    root.insert("name", this->name());
    root.insert("runtime", "JAVA");
    root.insert("className", this->m_Classname);
    root.insert("parallelism", this->parallelism());
    QJsonDocument doc = QJsonDocument::fromVariant(root);
    return doc.toJson(QJsonDocument::JsonFormat::Compact);
}

void Function::appendStatus(const QByteArray& _json)
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

void Function::appendInformation(const QByteArray& _json)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(_json, &error);
    if (error.error == QJsonParseError::ParseError::NoError)
    {
        QJsonObject root = doc.object();
        setName(root["name"].toString());
        setParallelism(root["parallelism"].toInt(1));
        setClassname(root["className"].toString());
        QJsonObject source = root["source"].toObject();
        QJsonObject inputs = source["inputSpecs"].toObject();
        QStringList rs;
        QJsonObject::const_iterator it;
        for (it = inputs.constBegin(); it != inputs.constEnd(); ++it)
        {
            rs << it.key();
        }
        setInputs(rs.join(","));
        QJsonObject sink = root["sink"].toObject();
        setOutput(sink["topic"].toString());
    }
}

FunctionData Function::toData() const
{
    FunctionData data;
    data["tenant"] = this->getNamespace().tenant().name();
    data["namesapces"] = this->getNamespace().name();
    data["name"] = this->name();
    data["instances"] = QString::number(this->instanceNum());
    data["running"] = QString::number(this->runningNum());
    return data;
}
