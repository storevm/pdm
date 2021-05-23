#ifndef BASEFUNCTION_H
#define BASEFUNCTION_H

#include <QString>
#include <QMap>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "namespace.h"

typedef QMap<QString, QString> QFunctionConfig;

class BaseFunction
{
public:
    explicit BaseFunction();
    BaseFunction(const BaseFunction& _other);
    BaseFunction& operator=(const BaseFunction& _other);

    inline Namespace getNamespace() const { return this->m_Namespace; };
    inline void setNamespace(const Namespace& _namespace) { this->m_Namespace = _namespace; }

    inline QString name() const { return this->m_Name; };
    inline void setName(const QString& _name) { this->m_Name = _name; };

    inline int instanceNum() const { return this->m_InstanceNum; };
    inline void setInstanceNum(int _instanceNum) { this->m_InstanceNum = _instanceNum; };

    inline int runningNum() const { return this->m_RunningNum; };
    inline void setRunningNum(int _runningNum) { this->m_RunningNum = _runningNum; };

    inline int parallelism() const { return this->m_Parallelism; }
    inline void setParallelism(const int& _parallelism) {this->m_Parallelism = _parallelism; }

    inline QFunctionConfig config() const { return this->m_Config; }
    inline void setConfig(const QFunctionConfig& _config) { this->m_Config = _config; }

    void addConfig(const QString& _key, const QString& _value);
    QVariantMap& createRoot(QVariantMap& _root) const;
    virtual QByteArray toJson() const = 0;
    virtual void appendInfo(const QByteArray& _json);

private:
    Namespace m_Namespace;
    QString m_Name;
    int m_InstanceNum;
    int m_RunningNum;
    int m_Parallelism;
    QFunctionConfig m_Config;
};

inline BaseFunction::BaseFunction() : m_InstanceNum(-1), m_RunningNum(-1), m_Parallelism(-1) {}

inline BaseFunction::BaseFunction(const BaseFunction& _other)
{
    *this = _other;
}

inline BaseFunction& BaseFunction::operator=(const BaseFunction& _other)
{
    if (this == &_other)
        return *this;
    this->m_Namespace = _other.getNamespace();
    this->m_Name = _other.name();
    this->m_InstanceNum = _other.instanceNum();
    this->m_RunningNum = _other.runningNum();
    this->m_Parallelism = _other.parallelism();
    this->m_Config = _other.m_Config;
    return *this;
}

inline void BaseFunction::addConfig(const QString& _key, const QString& _value)
{
    this->m_Config.insert(_key, _value);
}

inline QVariantMap& BaseFunction::createRoot(QVariantMap& _root) const
{
    _root["tenant"] = this->getNamespace().tenant().name();
    _root["namespace"] = this->getNamespace().name();
    _root["name"] = this->name();
    _root["processingGuarantees"] = "EFFECTIVELY_ONCE";
    _root["parallelism"] = this->parallelism();
    return _root;
}

inline void BaseFunction::appendInfo(const QByteArray& _json)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(_json, &error);
    if (error.error == QJsonParseError::ParseError::NoError)
    {
        QJsonObject root = doc.object();
        setName(root["name"].toString());
        setParallelism(root["parallelism"].toInt(-1));
        QJsonObject configs = root["configs"].toObject();
        QJsonObject::const_iterator it;
        for (it = configs.constBegin(); it != configs.constEnd(); ++it)
        {
            addConfig(it.key(), it.value().toString());
        }
    }
}

#endif // BASEFUNCTION_H
