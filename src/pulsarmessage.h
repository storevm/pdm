#ifndef PULSARMESSAGE_H
#define PULSARMESSAGE_H

#include <QObject>
#include <QByteArray>
#include <QMap>

#include "message.h"

typedef QMap<QString, QString> Properties;

class PulsarMessage : public Message
{
public:
    explicit PulsarMessage() : Message() {}
    PulsarMessage(const QByteArray& _data);
    PulsarMessage(const PulsarMessage& _other) { *this = _other; }
    PulsarMessage& operator=(const PulsarMessage& _other);

    inline Properties properties() const { return this->m_Properties; }
    inline void setProperties(const Properties& _properties) { this->m_Properties = _properties; }

    inline QByteArray data() const { return this->m_Data; }
    inline QString key() const { return this->m_Key; }
    inline QByteArray body() const { return this->m_Body; }

    inline void addProperties(const QString& _key, const QString& _value) { this->m_Properties[_key] = _value; }
    QString toJson() const;
    QString formatProperties();
    QString toString();
    QString toHex();

private:
    QByteArray m_Data;
    Properties m_Properties;
    QString m_Key;
    QByteArray m_Body;
    QByteArray m_Header;

    int m_Length;
    int m_HeaderLength;
    int m_BodyLength;
    int m_Position;

    const int HEADER_LENGTH = 4;

private:
    void readHeader(int& _pos);
    void readProperty(const QByteArray& _property);

};

Q_DECLARE_METATYPE(PulsarMessage);

#endif // PULSARMESSAGE_H
