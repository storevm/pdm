#ifndef FUNCTIONINSTANCE_H
#define FUNCTIONINSTANCE_H

#include "basefunction.h"

typedef QMap<QString, QString> FunctionInstanceData;

class FunctionInstance : public BaseFunction
{
public:
    explicit FunctionInstance();
    FunctionInstance(const FunctionInstance& _other);
    FunctionInstance& operator=(const FunctionInstance& _other);

    inline int instanceId() const { return this->m_instanceId; }
    inline void setInstanceId(const int& _instanceId) { this->m_instanceId = _instanceId; }

    inline bool isRunning() const { return this->m_running; };
    inline void setRunning(bool _running) { this->m_running = _running; };

    inline int receivedNum() const { return this->m_receivedNum; };
    inline void setReceivedNum(int _receivedNum) { this->m_receivedNum = _receivedNum; };

    inline int writtenNum() const { return this->m_writtenNum; };
    inline void setWrittenNum(int _writtenNum) { this->m_writtenNum = _writtenNum; };

    inline int errorNum() const { return this->m_errorNum; };
    inline void setErrorNum(int _errorNum) { this->m_errorNum = _errorNum; };

    virtual QByteArray toJson() const override;
    FunctionInstanceData toData() const;

private:
    int m_instanceId;
    bool m_running;
    int m_receivedNum;
    int m_writtenNum;
    int m_errorNum;
};

Q_DECLARE_METATYPE(FunctionInstance);

inline FunctionInstance::FunctionInstance() : BaseFunction(), m_instanceId(-1), m_running(false), m_receivedNum(-1), m_writtenNum(-1), m_errorNum(-1) {}

inline FunctionInstance::FunctionInstance(const FunctionInstance& _other) : BaseFunction(_other)
{
    *this = _other;
}

inline FunctionInstance& FunctionInstance::operator=(const FunctionInstance& _other)
{
    BaseFunction::operator=(_other);
    this->m_instanceId = _other.instanceId();
    this->m_running = _other.isRunning();
    this->m_receivedNum = _other.receivedNum();
    this->m_writtenNum = _other.writtenNum();
    this->m_errorNum = _other.errorNum();
    return *this;
}

inline QByteArray FunctionInstance::toJson() const { return QByteArray(); }

inline FunctionInstanceData FunctionInstance::toData() const
{
    FunctionInstanceData data;
    data["tenant"] = this->getNamespace().tenant().name();
    data["namesapces"] = this->getNamespace().name();
    data["name"] = this->name();
    data["id"] = QString::number(this->instanceId());
    data["status"] = this->isRunning() ? "true" : "false";
    data["received"] = QString::number(this->receivedNum());
    data["written"] = QString::number(this->writtenNum());
    data["errors"] = QString::number(this->errorNum());
    return data;
}

#endif // FUNCTIONINSTANCE_H
