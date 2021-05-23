#include "cluster.h"

Cluster::Cluster() : m_Name(QString()), m_AdminUrl(QString()), m_FunctionUrl(QString()), m_PrestoUrl(QString()), m_Status(Cluster::Status::Disconnected) {}

Cluster& Cluster::operator =(const Cluster& _other)
{
    this->m_Name = _other.name();
    this->m_AdminUrl = _other.adminUrl();
    this->m_FunctionUrl = _other.functionUrl();
    this->m_PrestoUrl = _other.prestoUrl();
    this->m_Status = _other.status();
    return *this;
}

bool Cluster::operator==(const Cluster& _other) const
{
    if (this->name() == _other.name())
    {
        return true;
    }
    return false;
}
