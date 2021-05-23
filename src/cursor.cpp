#include "cursor.h"

#include <QJsonDocument>
#include <QJsonObject>

Cursor::Cursor() : m_Name(QString()), m_MarkDeletePosition(QString()), m_ReadPosition(QString()), m_WaitingReadOp(false), m_PendingReadOps(0), m_Entries(0) {}

Cursor& Cursor::operator=(const Cursor& _other)
{
    this->m_Name = _other.name();
    this->m_MarkDeletePosition = _other.markDeletePosition();
    this->m_ReadPosition = _other.readPosition();
    this->m_WaitingReadOp = _other.waitingReadOp();
    this->m_PendingReadOps = _other.pendingReadOps();
    this->m_Entries = _other.entries();
    return *this;
}

Cursor& Cursor::fromJson(const QByteArray& _json, Cursor& _cursor)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(_json, &error);
    if (error.error == QJsonParseError::ParseError::NoError)
    {
        QJsonObject root = doc.object();
        _cursor.setMarkDeletePosition(root["markDeletePosition"].toString());
        _cursor.setReadPosition(root["readPosition"].toString());
        _cursor.setWaitingReadOp(root["waitingReadOp"].toBool());
        _cursor.setPendingReadOps(root["pendingReadOps"].toInt());
        _cursor.setEntries(root["numberOfEntriesSinceFirstNotAckedMessage"].toInt());
    }
    return _cursor;
}

int Cursor::deletePositionLedgerId()
{
    QStringList list = this->m_MarkDeletePosition.split(":");
    if (list.length() > 1)
    {
        return list[0].toInt();
    }
    return -1;
}
