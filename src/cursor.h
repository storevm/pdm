#ifndef CURSOR_H
#define CURSOR_H

#include <QObject>

class Cursor
{
public:
    explicit Cursor();
    Cursor(const Cursor& _other) { *this = _other; }
    Cursor& operator=(const Cursor& _other);

    inline void setName(const QString& _name) { this->m_Name = _name; }
    inline QString name() const { return this->m_Name; }

    inline void setMarkDeletePosition(const QString& _markDeletePosition) { this->m_MarkDeletePosition = _markDeletePosition; }
    inline QString markDeletePosition() const { return this->m_MarkDeletePosition; }

    inline void setReadPosition(const QString& _readPosition) { this->m_ReadPosition = _readPosition; }
    inline QString readPosition() const { return this->m_ReadPosition; }

    inline void setWaitingReadOp(const bool& _waitingReadOp) { this->m_WaitingReadOp = _waitingReadOp; }
    inline bool waitingReadOp() const { return this->m_WaitingReadOp; }

    inline void setPendingReadOps(const int& _pendingReadOps) { this->m_PendingReadOps = _pendingReadOps; }
    inline int pendingReadOps() const { return this->m_PendingReadOps; }

    inline void setEntries(const int& _entries) { this->m_Entries = _entries; }
    inline int entries() const { return this->m_Entries; }

    static Cursor& fromJson(const QByteArray&, Cursor&);
    //Cursor toData() const;
    int deletePositionLedgerId();

private:
    QString m_Name;
    QString m_MarkDeletePosition;
    QString m_ReadPosition;
    bool m_WaitingReadOp;
    int m_PendingReadOps;
    int m_Entries;

};

Q_DECLARE_METATYPE(Cursor);

#endif // CURSOR_H
