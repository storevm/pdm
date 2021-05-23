#ifndef ROLE_H
#define ROLE_H

#include <QObject>

#include "namespace.h"

class Role
{
public:
    explicit Role();
    Role(const Role& _other) { *this = _other; }
    Role& operator=(const Role& _other);

    inline void setNamespace(const Namespace& _namespace) { this->m_Namespace = _namespace; }
    inline Namespace getNamespace() const { return  this->m_Namespace; }

    inline void setName(const QString& _name) { this->m_Name = _name; }
    inline QString name() const { return this->m_Name; }

    inline QStringList permissions() const { return this->m_Permissions; }
    inline void setPermissions(const QStringList& _permissons) { this->m_Permissions = _permissons; }

    QByteArray toJson() const;

private:
    Namespace m_Namespace;
    QString m_Name;
    QStringList m_Permissions;

};

Q_DECLARE_METATYPE(Role);

#endif // ROLE_H
