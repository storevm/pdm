#ifndef CLUSTERSERVICE_H
#define CLUSTERSERVICE_H

#include "baseservice.h"

#include "../cluster.h"

class ClusterService : public BaseService
{
    Q_OBJECT

public:
    explicit ClusterService(QObject* parent = nullptr);

    QStringList clusters(const Cluster&) const;
    bool exist(const QString&) const;
    inline void addCluster(const Cluster& _cluster) { this->m_Clusters << _cluster; }
    void removeCluster(const Cluster&);
    void write();

    inline QList<Cluster> tolist() const { return this->m_Clusters; }

signals:
    void completeRead();

public slots:
    void read();

private:
    QList<Cluster> m_Clusters;

};

#endif // CLUSTERSERVICE_H
