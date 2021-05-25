#include "table.h"

Column& Column::operator=(const Column& _other)
{
    this->m_Name = _other.name();
    this->m_Type = _other.type();
    return *this;
}

QueryState& QueryState::operator=(const QueryState& _other)
{
    this->m_ElapsedTimeMillis = _other.elapsedTimeMillis();
    this->m_ProcessedRows = _other.processedRows();
    this->m_ProcessedBytes = _other.processedBytes();
    this->m_State = _other.state();
    return *this;
}

Statement& Statement::operator=(const Statement& _other)
{
    this->m_State = _other.state();
    this->m_NextUri = _other.nextUri();
    this->m_Columns = _other.columns();
    this->m_Error = _other.error();
    this->m_Condition = _other.condition();
    this->m_Results = _other.result();
    this->m_CancelUri = _other.cancelUri();
    return *this;
}
