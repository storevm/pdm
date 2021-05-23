#ifndef TENANT_H
#define TENANT_H

#include <QObject>

#include "cluster.h"

class Tenant
{
public:
    explicit Tenant();
    Tenant(const QString& _name) : m_Name(_name) {}
    Tenant(const Tenant& _other) { *this = _other; }
    Tenant& operator=(const Tenant&);
    friend inline bool operator==(const Tenant& _one, const Tenant& _other) { return _one.name() == _other.name(); }

    inline QString name() const { return this->m_Name; }
    inline void setName(const QString& _name) { this->m_Name = _name; }

    inline Cluster cluster() const { return this->m_Cluster; }
    inline void setCluster(const Cluster& _cluster) { this->m_Cluster = _cluster; }

    inline QStringList clusters() const { return this->m_Clusters; }

    void addCluster(const QString& _name) { this->m_Clusters << _name; }

private:
    QString m_Name;
    QStringList m_Roles;
    QStringList m_Clusters;
    Cluster m_Cluster;

};

Q_DECLARE_METATYPE(Tenant);

#endif // TENANT_H
