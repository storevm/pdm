#include "qjsonwebtoken.h"

#include <QVariantMap>
#include <QJsonDocument>
#include <QtCrypto/QtCrypto>

#include <log4qt/logger.h>

QJsonWebToken::QJsonWebToken(const QByteArray& _key, const QString& _sub) : m_key(_key), m_sub(_sub) {}

QJsonWebToken::QJsonWebToken(const QJsonWebToken& _other)
{
    *this = _other;
}

QJsonWebToken& QJsonWebToken::operator =(const QJsonWebToken& _other)
{
    this->m_key = _other.m_key;
    this->m_sub = _other.m_sub;
    return *this;
}

QJsonWebToken::~QJsonWebToken() {}

QString QJsonWebToken::token(bool* ok) const
{
    QByteArray header = toHeader();
    QByteArray body = toBody();
    if (body.length() <= 0)
    {
        *ok = false;
    }
    else
    {
        QByteArray data = header + "." + body;
        if (!QCA::isSupported("hmac(sha256)"))
        {
            *ok = false;
        }
        else
        {
            QCA::MessageAuthenticationCode hmac(QStringLiteral("hmac(sha256)"), QCA::SecureArray());
            QCA::SymmetricKey key(this->m_key);
            hmac.setup(key);
            hmac.update(data);
            QCA::SecureArray code = hmac.final();
            QString sign = QString::fromLatin1(code.toByteArray().toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals));
            *ok = true;
            return QString("%1.%2.%3").arg(QString::fromLatin1(header), QString::fromLatin1(body), sign);
        }
    }
    return QString();
}

bool QJsonWebToken::isValid(const QString& _token) const
{
    QStringList parts = _token.split(".");
    if (parts.length() != 3)
    {
        return false;
    }
    else
    {
        QByteArray header = toHeader();
        QByteArray body = toBody();
        if (body.length() <= 0)
        {
            return false;
        }
        else
        {
            QByteArray data = header + "." + body;
            if (!QCA::isSupported("hmac(sha256)"))
            {
                return false;
            }
            else
            {
                QCA::MessageAuthenticationCode hmac(QStringLiteral("hmac(sha256)"), QCA::SecureArray());
                QCA::SymmetricKey key(this->m_key);
                hmac.setup(key);
                hmac.update(data);
                QCA::SecureArray code = hmac.final();
                QString sign = QString::fromLatin1(code.toByteArray().toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals));
                return sign == parts[2];
            }
        }
    }
}

QByteArray QJsonWebToken::key(const int& _length)
{
    QCA::Random rand;
    QCA::SecureArray randBytes(_length);
    randBytes = rand.nextBytes(_length);
    return randBytes.toByteArray();
}

QByteArray QJsonWebToken::toHeader() const
{
    QVariantMap header;
    header.insert("alg", "HS256");
    QJsonDocument doc = QJsonDocument::fromVariant(header);
    QByteArray json = doc.toJson(QJsonDocument::JsonFormat::Compact);

    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("Json header: %1", QString::fromLatin1(json));
    }

    return json.toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);
}

QByteArray QJsonWebToken::toBody() const
{
    if (!this->m_sub.isEmpty())
    {
        QVariantMap body;
        body.insert("sub", this->m_sub);
        QJsonDocument doc = QJsonDocument::fromVariant(body);
        QByteArray json = doc.toJson(QJsonDocument::JsonFormat::Compact);

        if (Log4Qt::Logger::logger("main")->isDebugEnabled())
        {
            Log4Qt::Logger::logger("main")->debug("Json body: %1", QString::fromLatin1(json));
        }

        return json.toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);
    }

    return QByteArray();
}
