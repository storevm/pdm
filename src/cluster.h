#ifndef CLUSTER_H
#define CLUSTER_H

#include <QObject>

class Cluster
{
public:
    enum Status
    {
        Connected = 1,
        Disconnected = 2
    };

    explicit Cluster();

    Cluster(const Cluster& _other) { *this = _other; }
    Cluster& operator=(const Cluster& _other);
    bool operator==(const Cluster& _other) const;

    inline void setName(const QString& _name) { this->m_Name = _name; }
    inline QString name() const { return this->m_Name; }

    inline void setAdminUrl(const QString& _url) { this->m_AdminUrl = _url; }
    inline QString adminUrl() const { return this->m_AdminUrl; }

    inline void setFunctionUrl(const QString& _url) { this->m_FunctionUrl = _url; }
    inline QString functionUrl() const { return this->m_FunctionUrl; }

    inline void setPrestoUrl(const QString& _url) { this->m_PrestoUrl = _url; }
    inline QString prestoUrl() const { return this->m_PrestoUrl; }

    inline void setStatus(const Cluster::Status& _status) { this->m_Status = _status; }
    inline Cluster::Status status() const { return this->m_Status; }

    inline bool hasFunctionUrl() { return !this->m_FunctionUrl.isEmpty(); }
    inline bool hasPrestoUrl() { return !this->m_PrestoUrl.isEmpty(); }
    inline bool isConnected() { return this->m_Status == Cluster::Status::Connected; }

private:
    QString m_Name;
    QString m_AdminUrl;
    QString m_FunctionUrl;
    QString m_PrestoUrl;
    Cluster::Status m_Status;

};

Q_DECLARE_METATYPE(Cluster);

#endif // CLUSTER_H
