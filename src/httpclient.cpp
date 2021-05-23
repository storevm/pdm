#include "httpclient.h"

#include <QtCore/QString>
#include <QtCore/QTextCodec>
#include <QtCore/QEventLoop>
#include <QtNetwork/QSslConfiguration>
#include <QtNetwork/QSslSocket>
#include <QtNetwork/QSsl>
#include <QHttpMultiPart>

#include <log4qt/logger.h>

HttpClient::HttpClient(QObject* parent) : QObject(parent), m_Client(new QNetworkAccessManager(this))
{
    //this->qnam->setTransferTimeout(500);
}


HttpClient::~HttpClient()
{
    if (m_Client)
    {
        delete m_Client;
        m_Client = Q_NULLPTR;
    }
}

QByteArray HttpClient::get(const QUrl& _url) const
{
    QNetworkRequest request(_url);
    QNetworkReply* reply = this->m_Client->get(request);
    QByteArray response =  waitFor(reply);
    QVariant status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    int code = status.toInt();
    if (code == HttpStatusCode::StatusCode::TemporaryRedirect)
    {
        QVariant redirection = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        response = get(redirection.toUrl());

        if (Log4Qt::Logger::logger("main")->isDebugEnabled())
        {
            Log4Qt::Logger::logger("main")->debug("RedirectionTargetAttribute: %1", redirection.toString());
        }

    }
    reply->deleteLater();
    return response;
}

QByteArray HttpClient::get(const QUrl& _url, int& _code) const
{
    QNetworkRequest request(_url);
    QNetworkReply* reply = this->m_Client->get(request);
    QByteArray response =  waitFor(reply);
    QVariant status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    _code = status.toInt();
    if (_code == HttpStatusCode::StatusCode::TemporaryRedirect)
    {
        QVariant redirection = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        response = get(redirection.toUrl(), _code);

        if (Log4Qt::Logger::logger("main")->isDebugEnabled())
        {
            Log4Qt::Logger::logger("main")->debug("RedirectionTargetAttribute: %1", redirection.toString());
        }
    }
    reply->deleteLater();
    return response;
}

QByteArray HttpClient::deleteResource(const QUrl& _url) const
{
    QNetworkRequest request(_url);
    QNetworkReply* reply = this->m_Client->deleteResource(request);
    QByteArray response =  waitFor(reply);
    QVariant status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    int code = status.toInt();
    if (code == HttpStatusCode::StatusCode::TemporaryRedirect)
    {
        QVariant redirection = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        response = deleteResource(redirection.toUrl(), code);

        if (Log4Qt::Logger::logger("main")->isDebugEnabled())
        {
            Log4Qt::Logger::logger("main")->debug("RedirectionTargetAttribute: %1", redirection.toString());
        }
    }
    reply->deleteLater();
    return response;
}

QByteArray HttpClient::deleteResource(const QUrl& _url, int& _code) const
{
    QNetworkRequest request(_url);
    QNetworkReply* reply = this->m_Client->deleteResource(request);
    QByteArray response =  waitFor(reply);
    QVariant status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    _code = status.toInt();
    if (_code == HttpStatusCode::StatusCode::TemporaryRedirect)
    {
        QVariant redirection = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        response = deleteResource(redirection.toUrl(), _code);

        if (Log4Qt::Logger::logger("main")->isDebugEnabled())
        {
            Log4Qt::Logger::logger("main")->debug("RedirectionTargetAttribute: %1", redirection.toString());
        }
    }
    reply->deleteLater();
    return response;
}

QByteArray HttpClient::post(const QUrl& _url, const QByteArray& _body, const QString& _contentType) const
{
    QNetworkRequest request(_url);
    setupRequest(request, _contentType, _body.length());
    QNetworkReply* reply = this->m_Client->post(request, _body);
    QByteArray response = waitFor(reply);
    QVariant status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    int code = status.toInt();
    if (code == HttpStatusCode::StatusCode::TemporaryRedirect)
    {
        QVariant redirection = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        response = post(redirection.toUrl(), _body, _contentType);

        if (Log4Qt::Logger::logger("main")->isDebugEnabled())
        {
            Log4Qt::Logger::logger("main")->debug("RedirectionTargetAttribute: %1", redirection.toString());
        }
    }
    reply->deleteLater();
    return response;
}

QByteArray HttpClient::post(const QUrl& _url, const QByteArray& _body, int& _code, const QString& _contentType) const
{
    QNetworkRequest request(_url);
    setupRequest(request, _contentType, _body.length());
    QNetworkReply* reply = this->m_Client->post(request, _body);
    QByteArray response = waitFor(reply);
    QVariant status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    _code = status.toInt();
    if (_code == HttpStatusCode::StatusCode::TemporaryRedirect)
    {
        QVariant redirection = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        response = post(redirection.toUrl(), _body, _code, _contentType);

        if (Log4Qt::Logger::logger("main")->isDebugEnabled())
        {
            Log4Qt::Logger::logger("main")->debug("RedirectionTargetAttribute: %1", redirection.toString());
        }
    }
    reply->deleteLater();
    return response;
}

QByteArray HttpClient::post(const QUrl& _url, QHttpMultiPart* _multiPart, int& _code)
{
    QNetworkRequest request(_url);
    setupRequest(request);
    QNetworkReply* reply = this->m_Client->post(request, _multiPart);
    QByteArray response = waitFor(reply);
    _multiPart->setParent(reply);
    QVariant status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    _code = status.toInt();
    reply->deleteLater();
    return response;
}


QByteArray HttpClient::put(const QUrl& _url, const QByteArray& _body, const QString& _contentType) const
{
    QNetworkRequest request(_url);
    setupRequest(request, _contentType, _body.length());
    QNetworkReply* reply = this->m_Client->put(request, _body);
    QByteArray response = waitFor(reply);
    QVariant status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    int code = status.toInt();
    if (code == HttpStatusCode::StatusCode::TemporaryRedirect)
    {
        QVariant redirection = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        response = put(redirection.toUrl(), _body, _contentType);

        if (Log4Qt::Logger::logger("main")->isDebugEnabled())
        {
            Log4Qt::Logger::logger("main")->debug("RedirectionTargetAttribute: %1", redirection.toString());
        }
    }
    reply->deleteLater();
    return response;
}

QByteArray HttpClient::put(const QUrl& _url, const QByteArray& _body, int& _code, const QString& _contentType) const
{
    QNetworkRequest request(_url);
    setupRequest(request, _contentType, _body.length());
    QNetworkReply* reply = this->m_Client->put(request, _body);
    QByteArray response = waitFor(reply);
    QVariant status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    _code = status.toInt();
    if (_code == HttpStatusCode::StatusCode::TemporaryRedirect)
    {
        QVariant redirection = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        response = put(redirection.toUrl(), _body, _code, _contentType);

        if (Log4Qt::Logger::logger("main")->isDebugEnabled())
        {
            Log4Qt::Logger::logger("main")->debug("RedirectionTargetAttribute: %1", redirection.toString());
        }
    }
    reply->deleteLater();
    return response;
}

QByteArray HttpClient::put(const QUrl& _url, QHttpMultiPart* _multiPart, int& _code)
{
    QNetworkRequest request(_url);
    setupRequest(request);
    QNetworkReply* reply = this->m_Client->put(request, _multiPart);
    QByteArray response = waitFor(reply);
    _multiPart->setParent(reply);
    QVariant status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    _code = status.toInt();
    reply->deleteLater();
    return response;
}


void HttpClient::setupRequest(QNetworkRequest& _req, const QString& _contentType, int _length) const
{
    QString scheme = _req.url().scheme();
    if (scheme == "https")
    {
        QSslConfiguration config;
        config.setPeerVerifyMode(QSslSocket::VerifyNone);
        config.setProtocol(QSsl::TlsV1SslV3);
        _req.setSslConfiguration(config);
    }
    if (_length > 0)
    {
        _req.setHeader(QNetworkRequest::ContentTypeHeader, _contentType);
        _req.setHeader(QNetworkRequest::ContentLengthHeader, _length);
        _req.setRawHeader(QString("X-Presto-User").toLatin1(), QString("test-user").toLatin1());
    }
}

void HttpClient::handleRequestError(QNetworkReply::NetworkError _error)
{
    Log4Qt::Logger::logger("main")->debug("Http request has occurred error: %1", _error/* == QNetworkReply::NetworkError::OperationCanceledError*/);
}

QByteArray HttpClient::waitFor(QNetworkReply* reply) const
{
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::errorOccurred, this, &HttpClient::handleRequestError);
    connect(this->m_Client, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    connect(reply, &QNetworkReply::errorOccurred, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(); //block until finish
    return reply->readAll();
}
