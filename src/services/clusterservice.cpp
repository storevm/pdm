#include "clusterservice.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QSettings>
#include <QDir>

#include <log4qt/logger.h>

#include "../cluster.h"
#include "../constants.h"

ClusterService::ClusterService(QObject* parent) : BaseService(parent) {}

QStringList ClusterService::clusters(const Cluster& _cluster) const
{
    QStringList clusters;
    QString path(_cluster.adminUrl());
    path = path.append(this->m_Settings->value(GET_CLUSTERS_PATH_KEY).toString());
    QUrl url(path);

    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("Get the list of all the Pulsar clusters service url: %1", url.toString());
    }

    QByteArray result = this->m_Client->get(url);
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(result, &error);
    if (error.error == QJsonParseError::ParseError::NoError)
    {
        QJsonArray roots = doc.array();
        for (int i = 0; i < roots.size(); ++i)
        {
            clusters << roots[i].toString();
        }

        if (Log4Qt::Logger::logger("main")->isDebugEnabled())
        {
            Log4Qt::Logger::logger("main")->debug("Get the list of all the Pulsar clusters response result: %1", QString::fromLatin1(result));
        }
    }
    return clusters;
}

bool ClusterService::exist(const QString& _name) const
{
    bool ok = false;
    if (this->m_Clusters.size() > 0)
    {
        Q_FOREACH (const Cluster& cluster, this->m_Clusters)
        {
            if (cluster.name() == _name)
            {
                ok = true;
                break;
            }
        }
    }
    return ok;
}

void ClusterService::removeCluster(const Cluster& _cluster)
{
    Q_FOREACH (const Cluster& cluster, this->m_Clusters)
    {
        if (cluster.name() == _cluster.name())
        {
            this->m_Clusters.removeOne(cluster);
        }
    }
}

void ClusterService::write()
{
    QDir dir(CONFIG_DIR);
    QFile file(dir.absoluteFilePath("clusters.dat"));
    if (file.open(QIODevice::WriteOnly))
    {
        QJsonArray roots;
        Q_FOREACH (const Cluster& cluster, this->m_Clusters)
        {
            QJsonObject object;
            object["name"] = QJsonValue(cluster.name());
            object["serviceUrl"] = QJsonValue(cluster.adminUrl());
            object["functionUrl"] = QJsonValue(cluster.functionUrl());
            object["prestoUrl"] = QJsonValue(cluster.prestoUrl());
            roots << QJsonValue(object);
        }
        QJsonDocument doc(roots);
        QByteArray json = doc.toJson(QJsonDocument::Compact);

        if (Log4Qt::Logger::logger("main")->isDebugEnabled())
        {
            Log4Qt::Logger::logger("main")->debug("Write clusters json: %1", QString::fromLatin1(json));
        }

        file.write(json);
        file.close();
    }
}

void ClusterService::read()
{
    //read data from binary file, its format is JSON.
    QDir dir(CONFIG_DIR);
    QFile file(dir.absoluteFilePath("clusters.dat"));
    if (file.exists())
    {
        if (file.open(QIODevice::ReadOnly))
        {
            QJsonParseError error;
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
            if (error.error == QJsonParseError::ParseError::NoError)
            {
                if (Log4Qt::Logger::logger("main")->isDebugEnabled())
                {
                    Log4Qt::Logger::logger("main")->debug("Read clusters json: %1", QString::fromLatin1(doc.toJson(QJsonDocument::Compact)));
                }

                QJsonArray roots = doc.array();
                for (int i = 0; i < roots.size(); ++i)
                {
                    QJsonObject object = roots[i].toObject();
                    Cluster cluster;
                    cluster.setName(object["name"].toString());
                    cluster.setAdminUrl(object["serviceUrl"].toString());
                    cluster.setFunctionUrl(object["functionUrl"].toString());
                    cluster.setPrestoUrl(object["prestoUrl"].toString());
                    this->m_Clusters << cluster;
                }
            }
            else
            {
                Log4Qt::Logger::logger("main")->error("parse JSON error: %1", error.error);
            }
        }
        file.close();

    }
    emit completeRead();
}
