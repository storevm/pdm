#include "message.h"

Message::Message() : m_LedgerId(-1), m_EntryId(-1) {}

Message::Message(const int& _ledgerId, const int& _entryId) : m_LedgerId(_ledgerId), m_EntryId(_entryId) {}

Message& Message::operator =(const Message& _other)
{
    this->m_LedgerId = _other.ledgerId();
    this->m_EntryId = _other.entryId();
    return *this;
}
