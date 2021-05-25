#include "tenantservice.h"

#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>

#include <log4qt/logger.h>

#include "../constants.h"

QList<Tenant> TenantService::tenants(const Cluster& _cluster) const
{
    QList<Tenant> tenants;

    QString path(_cluster.adminUrl());
    path = path.append(this->m_Settings->value(GET_TENANTS_PATH_KEY).toString());
    QUrl url(path);

    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("Get the list of existing tenants service url: %1", url.toString());
    }

    QByteArray result = this->m_Client->get(url);
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(result, &error);
    if (error.error == QJsonParseError::ParseError::NoError)
    {
        QJsonArray roots = doc.array();
        for (int i = 0, n = roots.size(); i < n; ++i)
        {
            Tenant tenant(roots[i].toString());
            tenant.setCluster(_cluster);
            tenants << tenant;
        }
    }

    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("List tenants response result: %1", QString::fromLatin1(result));
    }

    return tenants;
}

void TenantService::createTenant(const Tenant& _tenant, HttpStatusCode& _code)
{
    QString path(_tenant.cluster().adminUrl());
    path = path.append(this->m_Settings->value(PUT_NEW_TENANT_PATH_KEY).toString()).arg(_tenant.name());
    QUrl url(path);

    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("Create a new tenant service url: %1", url.toString());
    }

    QVariantMap jsonObject;
    jsonObject.insert("allowedClusters", _tenant.clusters());
    QJsonDocument doc = QJsonDocument::fromVariant(jsonObject);
    QByteArray json = doc.toJson(QJsonDocument::JsonFormat::Compact);

    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("Create a new tenant request body: %1", QString::fromLatin1(json));
    }

    int statusCode;
    QByteArray result = this->m_Client->put(url, json, statusCode);
    switch (statusCode)
    {
    case 204:
        _code.code = HttpStatusCode::StatusCode::NoContent;
        break;
    case 409:
        _code.code = HttpStatusCode::StatusCode::Conflict;
        _code.errorDesc = QString(tr("Tenant already exists."));
        break;
    case 412:
        _code.code = HttpStatusCode::StatusCode::PreconditionFailed;
        _code.errorDesc = QString(tr("Clusters do not exist."));
        break;
    case 403:
        _code.code = HttpStatusCode::StatusCode::Forbidden;
        _code.errorDesc = QString(tr("The requester doesn't have admin permissions."));
        break;
    }

    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("Create a new tenant Response result: %1, status code: %2", QString::fromLatin1(result), statusCode);
    }
}

void TenantService::deleteTenant(const Tenant& _tenant, HttpStatusCode& _code)
{
    QString path(_tenant.cluster().adminUrl());
    path = path.append(this->m_Settings->value(DELETE_TENANT_PATH_KEY).toString()).arg(_tenant.name());
    QUrl url(path);

    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("Delete a tenant and all namespaces and topics under it service path: %1", url.toString());
    }

    int statusCode;
    QByteArray result = this->m_Client->deleteResource(url, statusCode);
    switch (statusCode)
    {
    case 204:
        _code.code = HttpStatusCode::StatusCode::NoContent;
        break;
    case 409:
        _code.code = HttpStatusCode::StatusCode::Conflict;
        _code.errorDesc = QString(tr("The tenant still has active namespaces."));
        break;
    case 404:
        _code.code = HttpStatusCode::StatusCode::NotFound;
        _code.errorDesc = QString(tr("Tenant does not exist."));
        break;
    case 403:
        _code.code = HttpStatusCode::StatusCode::Forbidden;
        _code.errorDesc = QString(tr("The requester doesn't have admin permissions."));
        break;
    }

    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("Delete a tenant and all namespaces and topics under it Response result: %1, status code: %2", QString::fromLatin1(result), statusCode);
    }
}
