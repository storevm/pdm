#include "namespaceservice.h"

#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>

#include <log4qt/logger.h>

#include "../constants.h"

QList<Namespace> NamespaceService::namespaces(const Tenant& _tenant) const
{
    QList<Namespace> namespaces;
    QString path(_tenant.cluster().adminUrl());
    path = path.append(this->m_Settings->value(GET_NAMESPACES_PATH_KEY).toString()).arg(_tenant.name());
    QUrl url(path);

    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("Get the list of all the namespaces for a certain tenant service url: %1", url.toString());
    }

    QByteArray result = this->m_Client->get(url);
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(result, &error);
    if (error.error == QJsonParseError::ParseError::NoError)
    {
        QJsonArray array = doc.array();
        for (int i = 0, n = array.size(); i < n; ++i)
        {
            Namespace ns;
            ns.setName(array[i].toString().section("/", 1, 1));
            ns.setTenant(_tenant);
            namespaces << ns;
        }
    }

    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("Get the list of all the namespaces for a certain tenant response result: %1", QString::fromLatin1(result));
    }

    return namespaces;
}

void NamespaceService::createNamespace(const Namespace& _namespace, HttpStatusCode& _code)
{
    QString path(_namespace.tenant().cluster().adminUrl());
    path = path.append(this->m_Settings->value(PUT_NEW_NAMESPACE_PATH_KEY).toString()).arg(_namespace.tenant().name(), _namespace.name());
    QUrl url(path);

    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("Create a new namesapce service url: %1", url.toString());
    }

    QByteArray json = _namespace.toJson();

    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("Create a new namesapce request body: %1", QString::fromLatin1(json));
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
        _code.errorDesc = QString(tr("Namespace already exists."));
        break;
    case 412:
        _code.code = HttpStatusCode::StatusCode::PreconditionFailed;
        _code.errorDesc = QString(tr("Namespace name is not valid."));
        break;
    case 404:
        _code.code = HttpStatusCode::StatusCode::NotFound;
        _code.errorDesc = QString(tr("Tenant or cluster doesn't exist."));
        break;
    case 403:
        _code.code = HttpStatusCode::StatusCode::Forbidden;
        _code.errorDesc = QString(tr("Don't have admin permission."));
        break;
    }

    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("Create a new namesapce response result: %1", QString::fromLatin1(result));
    }
}

void NamespaceService::deleteNamespace(const Namespace& _namespace, HttpStatusCode& _code)
{
    QString path(_namespace.tenant().cluster().adminUrl());
    path = path.append(this->m_Settings->value(DELETE_NAMESPACE_PATH_KEY).toString()).arg(_namespace.tenant().name(), _namespace.name());
    QUrl url(path);

    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("Delete a namespace and all the topics under it service url: %1", url.toString());
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
        _code.errorDesc = QString(tr("Namespace is not empty."));
        break;
    case 404:
        _code.code = HttpStatusCode::StatusCode::NotFound;
        _code.errorDesc = QString(tr("Tenant or cluster or namespace doesn't exist."));
        break;
    case 403:
        _code.code = HttpStatusCode::StatusCode::Forbidden;
        _code.errorDesc = QString(tr("Don't have admin permission."));
        break;
    }

    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("Delete a namespace and all the topics under it response result: %1", QString::fromLatin1(result));
    }
}
