#ifndef TABLE_H
#define TABLE_H

#include <QObject>

class Column
{
public:
    explicit Column() {}
    Column(const Column& _other) { *this = _other; }
    Column& operator=(const Column& _other);

    inline void setName(const QString& _name) { this->m_Name = _name; }
    inline QString name() const { return this->m_Name; }
    inline void setType(const QString& _type) { this->m_Type = _type; }
    inline QString type() const { return this->m_Type; }

private:
    QString m_Name;
    QString m_Type;

};

Q_DECLARE_METATYPE(Column);

class QueryState
{
public:
    explicit QueryState() {}
    QueryState(const QueryState& _other) { *this = _other; }
    QueryState& operator=(const QueryState& _other);

    inline void setElapsedTimeMillis(const int& _elapsedTimeMillis) { this->m_ElapsedTimeMillis = _elapsedTimeMillis; }
    inline int elapsedTimeMillis() const { return this->m_ElapsedTimeMillis; }
    inline void setProcessedRows(const int& _processedRows) { this->m_ProcessedRows = _processedRows; }
    inline int processedRows() const { return this->m_ProcessedRows; }
    inline void setProcessedBytes(const int& _processedBytes) { this->m_ProcessedBytes = _processedBytes; }
    inline int processedBytes() const { return this->m_ProcessedBytes; }
    inline void setState(const QString& _state) { this->m_State = _state; }
    inline QString state() const { return this->m_State; }

private:
    int m_ElapsedTimeMillis;
    int m_ProcessedRows;
    int m_ProcessedBytes;
    QString m_State;

};

Q_DECLARE_METATYPE(QueryState);

class Statement
{
public:
    enum Status
    {
        QUEUED = 0, RUNNING, FINISHED, FAILED = 999
    };

    explicit Statement() {}
    Statement(const Statement& _other) { *this = _other; }
    Statement& operator=(const Statement& _other);

    inline void setNextUri(const QString& _nextUri) { this->m_NextUri = _nextUri; }
    inline QString nextUri() const { return this->m_NextUri; }
    inline void setColumns(const QList<Column>& _columns) { this->m_Columns = _columns; }
    inline QList<Column> columns() const { return this->m_Columns; }
    inline void setError(const QString& _error) { this->m_Error = _error; }
    inline QString error() const { return this->m_Error; }
    inline void setCondition(const QString& _condition) { this->m_Condition = _condition; }
    inline QString condition() const { return this->m_Condition; }
    inline void setId(const QString& _id) { this->m_Id = _id; }
    inline QString id() const { return this->m_Id; }
    inline void setState(const QueryState& _state) { this->m_State = _state; }
    inline QueryState state() const { return this->m_State; }
    inline QStringList result() const { return this->m_Results; }
    inline void setCancelUri(const QString& _cancelUri) { this->m_CancelUri = _cancelUri; }
    inline QString cancelUri() const { return this->m_CancelUri; }

    void addColumn(const Column& _column) { this->m_Columns << _column; }
    void addResult(const QString& _result) { this->m_Results << _result; }
    void clearColumns() { this->m_Columns.clear(); }
    void clearResult() { this->m_Results.clear(); }
    void reset()
    {
        clearColumns();
        clearResult();
        this->m_Error = QString();
        this->m_Condition = QString();
        this->m_CancelUri = QString();
        this->m_NextUri = QString();
    }

private:
    QString m_Id;
    QueryState m_State;
    QString m_NextUri;
    QString m_CancelUri;
    QList<Column> m_Columns;
    QStringList m_Results;
    QString m_Error;
    QString m_Condition;
};

Q_DECLARE_METATYPE(Statement);

#endif // TABLE_H
