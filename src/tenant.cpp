#include "tenant.h"

Tenant::Tenant() : Tenant(QString()) {}

Tenant& Tenant::operator =(const Tenant& _other)
{
    this->m_Name = _other.name();
    this->m_Cluster = _other.cluster();
    return *this;
}
