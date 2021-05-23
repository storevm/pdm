#ifndef QJSONWEBTOKEN_H
#define QJSONWEBTOKEN_H

#include <QByteArray>
#include <QString>

class QJsonWebToken
{
public:
    explicit QJsonWebToken(const QByteArray& _key, const QString& _sub);
    QJsonWebToken(const QJsonWebToken&);
    QJsonWebToken& operator=(const QJsonWebToken&);
    virtual ~QJsonWebToken();

    QString token(bool* ok) const;
    bool isValid(const QString&) const;
    static QByteArray key(const int& length = 32);

private:
    QByteArray toHeader() const;
    QByteArray toBody() const;

private:
    QByteArray m_key;
    QString m_sub;

};

#endif // QJSONWEBTOKEN_H
