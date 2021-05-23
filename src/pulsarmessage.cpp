#include "pulsarmessage.h"

#include <QJsonDocument>
#include <QTextCodec>

#include <log4qt/logger.h>

PulsarMessage::PulsarMessage(const QByteArray& _data) : Message(), m_Data(_data), m_Key(QString()), m_Body(QByteArray())
{
    this->m_Length = m_Data.length();
    bool ok;
    int length = this->m_Data.left(HEADER_LENGTH).toHex().toInt(&ok, 16);
    if (length < this->m_Length)
    {
        this->m_HeaderLength = length;
        if (Log4Qt::Logger::logger("main")->isDebugEnabled())
        {
            Log4Qt::Logger::logger("main")->debug("read header length: %1", QString::number(this->m_HeaderLength));
        }

        this->m_Position = HEADER_LENGTH;
        if (Log4Qt::Logger::logger("main")->isDebugEnabled())
        {
            Log4Qt::Logger::logger("main")->debug("current read position: %1", this->m_Position);
        }

        this->m_Header = this->m_Data.mid(this->m_Position, this->m_HeaderLength);
        this->m_Position += this->m_HeaderLength;

        if (Log4Qt::Logger::logger("main")->isDebugEnabled())
        {
            Log4Qt::Logger::logger("main")->debug("read header data: %1, current pos: %2", QString::fromLatin1(this->m_Header.toHex(' ')), this->m_Position);
        }

        this->m_Body = this->m_Data.mid(this->m_Position, (this->m_Length - this->m_Position));

        if (Log4Qt::Logger::logger("main")->isDebugEnabled())
        {
            Log4Qt::Logger::logger("main")->debug("read body data: %1", QString::fromLatin1(this->m_Body.toHex(' ')));
        }

        int pos = 0;
        readHeader(pos);
    }
    else
    {
        this->m_Body = this->m_Data.mid(0, this->m_Length);
    }
}

PulsarMessage& PulsarMessage::operator=(const PulsarMessage& _other)
{
    Message::operator=(_other);
    this->m_Data = _other.data();
    this->m_Properties = _other.properties();
    this->m_Key = _other.key();
    this->m_Body = _other.body();
    return *this;
}

QString PulsarMessage::toJson() const
{
    if (this->m_Body.length() > 0)
    {
        QByteArray message = this->m_Body.mid(0, this->m_BodyLength);
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(message, &error);
        if (error.error == QJsonParseError::ParseError::NoError)
        {
            QTextCodec* codec = QTextCodec::codecForName("UTF-8");
            return codec->toUnicode(doc.toJson(QJsonDocument::JsonFormat::Indented));
        }
    }
    return QString("{}");
}

QString PulsarMessage::formatProperties()
{
    if (this->m_Properties.size() > 0)
    {
        QVariantMap map;
        QMap<QString, QString>::const_iterator it;
        for (it = this->m_Properties.constBegin(); it != this->m_Properties.constEnd(); ++it)
        {
            map[it.key()] = it.value();
        }
        QJsonDocument doc = QJsonDocument::fromVariant(map);
        return QString::fromLatin1(doc.toJson(QJsonDocument::JsonFormat::Indented));
    }
    return QString();
}

QString PulsarMessage::toHex()
{
    QString str;
    if (this->m_Body.length() > 0)
    {
        return QString::fromLatin1(this->m_Body.toHex(' '));
    }
    return str;
}

QString PulsarMessage::toString()
{
    QString str;
    if (this->m_Body.length() > 0)
    {
        QTextCodec* codec = QTextCodec::codecForName("UTF-8");
        str = codec->toUnicode(this->m_Body);
    }
    return str;
}

void PulsarMessage::readHeader(int& _pos)
{
    bool ok;
    QByteArray id = this->m_Header.mid(_pos++, 1);
    if (id == QString("\n"))
    {
        //读取一个字节(property的长度)
        int len = this->m_Header.mid(_pos++, 1).toHex().toInt(&ok, 16);
        //读取len字节(property)
        QByteArray property = this->m_Header.mid(_pos, len);
        _pos += len;
        readProperty(property);
        readHeader(_pos); //继续读
    }
    else if (id == QString("\x12"))
    {
        //读取一个字节(message key的长度)
        int len = this->m_Header.mid(_pos++, 1).toHex().toInt(&ok, 16);
        //读取len字节(message key)
        QByteArray key = this->m_Header.mid(_pos, len);
        _pos += len;
        this->m_Key = QString::fromLatin1(key);
        readHeader(_pos); //继续读
    }
    else if (id == QString("\x18"))
    {
        //读取一个字节(body的长度)
        int len = this->m_Header.mid(_pos++, 1).toHex().toInt(&ok, 16);
        if (len >= 128)
        {
            int exlen = this->m_Header.mid(_pos++, 1).toHex().toInt(&ok, 16);
            len += (exlen - 1) * 128;
        }
        this->m_BodyLength = len;
    }
}

void PulsarMessage::readProperty(const QByteArray& _property)
{
    bool ok;
    int pos = 0;
    int keyLength = _property.mid(++pos, 1).toHex().toInt(&ok, 16); //key length
    QByteArray key = _property.mid(++pos, keyLength);
    pos += keyLength;
    int valueLength = _property.mid(++pos, 1).toHex().toInt(&ok, 16); //value length
    QByteArray value = _property.mid(++pos, valueLength);
    this->addProperties(QString::fromLatin1(key), QString::fromLatin1(value));
}
