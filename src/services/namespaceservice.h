#ifndef NAMESPACESERVICE_H
#define NAMESPACESERVICE_H

#include "baseservice.h"

#include "../namespace.h"

class NamespaceService : public BaseService
{
    Q_OBJECT

public:
    explicit NamespaceService(QObject* parent = nullptr) : BaseService(parent) {}

    QList<Namespace> namespaces(const Tenant& _tenant) const;
    void createNamespace(const Namespace& _namespace, HttpStatusCode& _code);
    void deleteNamespace(const Namespace& _namespace, HttpStatusCode& _code);

};

#endif // NAMESPACESERVICE_H
