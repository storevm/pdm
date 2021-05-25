#ifndef TENANTSERVICE_H
#define TENANTSERVICE_H

#include "baseservice.h"

#include "../tenant.h"

class TenantService : public BaseService
{
    Q_OBJECT

public:
    explicit TenantService(QObject* parent = nullptr) : BaseService(parent) {}

    QList<Tenant> tenants(const Cluster& _cluster) const;
    void createTenant(const Tenant& _tenant, HttpStatusCode& _code);
    void deleteTenant(const Tenant& _tenant, HttpStatusCode& _code);

};

#endif // TENANTSERVICE_H
