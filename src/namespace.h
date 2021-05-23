#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <QObject>

#include "tenant.h"

class Namespace
{
public:
    explicit Namespace() : Namespace(QString()) {}
    Namespace(const QString& _name) : m_Name(_name) {}
    Namespace(const Namespace& _other) { *this = _other; }
    Namespace& operator=(const Namespace& _other);
    friend inline bool operator==(const Namespace& _one, const Namespace& _other) { return _one.name() == _other.name() && _one.tenant() == _other.tenant(); }

    inline QString name() const { return this->m_Name; }
    inline void setName(const QString& _name) { this->m_Name = _name; }

    inline Tenant tenant() const { return this->m_Tenant; }
    inline void setTenant(const Tenant& _tenant) { this->m_Tenant = _tenant; }

    inline QString role() const { return this->m_Role; }
    inline void setRole(const QString& _role) { this->m_Role = _role; }

    inline QStringList auths() const { return this->m_Auths; }
    inline void setAuths(const QStringList& _auth) { this->m_Auths = _auth; }

    QByteArray toJson() const;

private:
    QString m_Name;
    Tenant m_Tenant;
    QString m_Role;
    QStringList m_Auths;

};

Q_DECLARE_METATYPE(Namespace);

#endif // NAMESPACE_H
