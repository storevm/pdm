#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>

typedef QMap<QString, QString> ConsumerData;

class Consumer
{
public:
    explicit Consumer() : m_Name(QString()), m_MsgRateOut(0.0), m_MsgThroughputOut(0.0), m_AverageMsgSize(0.0), m_Address(QString()), m_ConnectedSince(QString()) {}
    Consumer(const Consumer& _other) { *this = _other; }
    Consumer& operator=(const Consumer& _other)
    {
        this->m_Name = _other.name();
        this->m_MsgRateOut = _other.msgRateOut();
        this->m_MsgThroughputOut = _other.msgThroughputOut();
        this->m_AverageMsgSize = _other.averageMsgSize();
        this->m_Address = _other.address();
        this->m_ConnectedSince = _other.connectedSince();
        return *this;
    }

    inline void setName(const QString& _name) { this->m_Name = _name; }
    inline QString name() const { return this->m_Name; }

    inline double msgRateOut() const { return this->m_MsgRateOut; }
    inline void setMsgRateOut(const double& _msgRateOut) { this->m_MsgRateOut = _msgRateOut; }

    inline double msgThroughputOut() const { return this->m_MsgThroughputOut; }
    inline void setMsgThroughputOut(const double& _msgThroughputOut) { this->m_MsgThroughputOut = _msgThroughputOut; }

    inline double averageMsgSize() const { return this->m_AverageMsgSize; }
    inline void setAverageMsgSize(const double& _averageMsgSize) { this->m_AverageMsgSize = _averageMsgSize; }

    inline void setConnectedSince(const QString& _connectedSince) { this->m_ConnectedSince = _connectedSince; }
    inline QString connectedSince() const { return this->m_ConnectedSince; }

    inline void setAddress(const QString& _address) { this->m_Address = _address; }
    inline QString address() const { return this->m_Address; }

    static Consumer& fromJson(const QByteArray&, Consumer&);
    ConsumerData toData() const;

private:
    QString m_Name;
    double m_MsgRateOut;
    double m_MsgThroughputOut;
    double m_AverageMsgSize;
    QString m_Address;
    QString m_ConnectedSince;
};

Q_DECLARE_METATYPE(Consumer);

#endif // CONSUMER_H
