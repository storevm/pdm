#ifndef BASESERVICE_H
#define BASESERVICE_H

#include <QObject>
#include <QSettings>

#include "../httpclient.h"

class BaseService : public QObject
{
    Q_OBJECT

public:
    explicit BaseService(QObject* parent = nullptr);

signals:

protected:
    HttpClient* m_Client;
    QSettings* m_Settings;

};

#endif // BASESERVICE_H
