#ifndef PRODUCER_H
#define PRODUCER_H

#include <QObject>

typedef QMap<QString, QString> ProducerData;

class Producer
{
public:
    explicit Producer() : m_Id(-1), m_Name(QString()), m_Address(QString()), m_MsgRateIn(0.0), m_MsgThroughputIn(0.0), m_AverageMsgSize(0.0), m_ConnectedSince(QString()) {}
    Producer(const Producer& _other) { *this = _other; }
    Producer& operator=(const Producer& _other)
    {
        this->m_Id = _other.id();
        this->m_Name = _other.name();
        this->m_Address = _other.address();
        this->m_MsgRateIn = _other.msgRateIn();
        this->m_MsgThroughputIn = _other.msgThroughputIn();
        this->m_AverageMsgSize = _other.averageMsgSize();
        this->m_ConnectedSince = _other.connectedSince();
        return *this;
    }

    inline void setId(const int& _id) { this->m_Id = _id; }
    inline int id() const { return this->m_Id; }

    inline void setName(const QString& _name) { this->m_Name = _name; }
    inline QString name() const { return this->m_Name; }

    inline void setAddress(const QString& _address) { this->m_Address = _address; }
    inline QString address() const { return this->m_Address; }

    inline double msgRateIn() const { return this->m_MsgRateIn; }
    inline void setMsgRateIn(const double& _msgRateIn) { this->m_MsgRateIn = _msgRateIn; }

    inline double msgThroughputIn() const { return this->m_MsgThroughputIn; }
    inline void setMsgThroughputIn(const double& _msgThroughputIn) { this->m_MsgThroughputIn = _msgThroughputIn; }

    inline double averageMsgSize() const { return this->m_AverageMsgSize; }
    inline void setAverageMsgSize(const double& _averageMsgSize) { this->m_AverageMsgSize = _averageMsgSize; }

    inline void setConnectedSince(const QString& _connectedSince) { this->m_ConnectedSince = _connectedSince; }
    inline QString connectedSince() const { return this->m_ConnectedSince; }

    static Producer& fromJson(const QByteArray&, Producer&);
    ProducerData toData() const;

private:
    int m_Id;
    QString m_Name;
    QString m_Address;
    double m_MsgRateIn;
    double m_MsgThroughputIn;
    double m_AverageMsgSize;
    QString m_ConnectedSince;

};

Q_DECLARE_METATYPE(Producer);

#endif // PRODUCER_H
