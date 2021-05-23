#include "namespace.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

Namespace& Namespace::operator =(const Namespace& _other)
{
    this->m_Name = _other.name();
    this->m_Tenant = _other.tenant();
    this->m_Role = _other.role();
    this->m_Auths = _other.auths();
    return *this;
}

QByteArray Namespace::toJson() const
{
    QJsonObject root;
    QJsonObject authPolicies;
    QJsonObject namespaceAuth;
    namespaceAuth.insert(this->m_Role, QJsonArray::fromStringList(this->m_Auths));
    authPolicies.insert("namespace_auth", namespaceAuth);
    root.insert("auth_policies", authPolicies);
    QJsonDocument doc = QJsonDocument::fromVariant(root);
    return doc.toJson(QJsonDocument::JsonFormat::Compact);
}
