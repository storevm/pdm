#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

class Message
{
public:
    explicit Message();
    Message(const int& _ledgerId, const int& _entryId);
    Message(const Message& _other) { *this = _other; }
    Message& operator=(const Message& _other);

    inline void setLedgerId(const int& _ledgerId) { this->m_LedgerId = _ledgerId; }
    inline int ledgerId() const { return this->m_LedgerId; }

    inline void setEntryId(const int& _entryId) { this->m_EntryId = _entryId; }
    inline int entryId() const { return this->m_EntryId; }

private:
    int m_LedgerId;
    int m_EntryId;

};

Q_DECLARE_METATYPE(Message);

#endif // MESSAGE_H
