/*
 * File:   httpclinet.h
 * Author: Administrator
 *
 */

#ifndef HTTPCLINET_H
#define HTTPCLINET_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

struct HttpStatusCode
{
    enum StatusCode
    {
        OK = 200,
        NoContent = 204,
        Forbidden = 403,
        Conflict = 409,
        NotFound = 404,
        PreconditionFailed = 412,
        TemporaryRedirect = 307,
        InternalServerError = 500,
        ServiceUnavailable = 503,
        Unauthorized = 401,
        BadRequest = 400,
        RequestTimeout = 408,
        MethodNotAllowed = 405,
        NotImplemented = 501,
    };

    QString errorString() const { return errorDesc; };

    QString errorDesc;
    StatusCode code;
};

class HttpClient : public QObject
{
public:
    HttpClient(QObject* parent = Q_NULLPTR);
    virtual ~HttpClient();

    QByteArray get(const QUrl& _url) const;
    QByteArray get(const QUrl& _url, int& _code) const;

    QByteArray post(const QUrl& _url, const QByteArray& _body, const QString& _contentType = "application/json") const;
    QByteArray post(const QUrl& _url, QHttpMultiPart* _multiPart, int& _code);
    QByteArray post(const QUrl& _url, const QByteArray& _body, int& _code, const QString& _contentType = "application/json") const;

    QByteArray put(const QUrl& _url, const QByteArray& _body, const QString& _contentType = "application/json") const;
    QByteArray put(const QUrl& _url, const QByteArray& _body, int& _code, const QString& _contentType = "application/json") const;
    QByteArray put(const QUrl& _url, QHttpMultiPart* _multiPart, int& _code);

    QByteArray deleteResource(const QUrl& _url) const;
    QByteArray deleteResource(const QUrl& _url, int& _code) const;



protected:
    QByteArray waitFor(QNetworkReply* _reply) const;
    void setupRequest(QNetworkRequest& _req, const QString& _contentType = "application/json", int _length = 0) const;

private:
    QNetworkAccessManager* m_Client;

private slots:
    void handleRequestError(QNetworkReply::NetworkError);

};

#endif  /* HTTPCLINET_H */

