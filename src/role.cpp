#include "role.h"

#include <QByteArray>
#include <QVariantList>
#include <QJsonDocument>

Role::Role() : m_Name(QString()) {}

Role& Role::operator =(const Role& _other)
{
    this->m_Namespace = _other.getNamespace();
    this->m_Name = _other.name();
    this->m_Permissions = _other.permissions();
    return *this;
}

QByteArray Role::toJson() const
{
    QVariantList root;
    Q_FOREACH (const QString& s, this->m_Permissions)
    {
        root << s;
    }
    QJsonDocument doc = QJsonDocument::fromVariant(root);
    return doc.toJson(QJsonDocument::JsonFormat::Compact);
}
