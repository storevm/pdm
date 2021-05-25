#include "source.h"

Source::Source() : BaseFunction(), m_Classname(QString()), m_TopicName(QString()) {}

Source& Source::operator =(const Source& _other)
{
    BaseFunction::operator=(_other);
    this->m_Classname = _other.classname();
    this->m_TopicName = _other.topicName();
    return *this;
}

QByteArray Source::toJson() const
{
    QJsonObject root;
    root = createRoot(root);
    root["className"] = this->m_Classname;
    root["topicName"] = this->m_TopicName;
    QJsonObject configs;
    FunctionConfig::const_iterator it;
    FunctionConfig config = this->config();
    for (it = config.constBegin(); it != config.constEnd(); ++it)
        configs.insert(it.key(), it.value());
    root["configs"] = configs;
    QJsonDocument doc = QJsonDocument::fromVariant(root);
    return doc.toJson(QJsonDocument::JsonFormat::Compact);
}
