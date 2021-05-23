#ifndef FUNCTION_H
#define FUNCTION_H

#include "basefunction.h"

class FunctionStatus
{
public:
    explicit FunctionStatus();
    FunctionStatus(const FunctionStatus& _other) { *this = _other; }
    FunctionStatus& operator=(const FunctionStatus& _other);

    inline void setInstanceId(const int& _instanceId) { this->m_InstanceId = _instanceId; }
    inline int instanceId() const { return this->m_InstanceId; }

    inline void setStatus(const bool& _status) { this->m_Status = _status; }
    inline bool status() const { return this->m_Status; }

private:
    int m_InstanceId;
    bool m_Status;
};

Q_DECLARE_METATYPE(FunctionStatus);

typedef QMap<QString, QString> FunctionData;

class Function : public BaseFunction
{
public:
    explicit Function();
    Function(const Function& _other) { *this = _other; }
    Function& operator=(const Function& _other);

    QByteArray toJson() const override;

    inline void setClassname(const QString& _classname) { this->m_Classname = _classname; }
    inline QString classname() const { return  this->m_Classname; }

    inline void setInputs(const QString& _inputs) { this->m_Inputs = _inputs; }
    inline QString inputs() const { return  this->m_Inputs; }

    inline void setOutput(const QString& _output) { this->m_Output = _output; }
    inline QString output() const { return  this->m_Output; }

    void appendStatus(const QByteArray& _json);
    void appendInformation(const QByteArray& _json);

    FunctionData toData() const;

private:
    QString m_Classname;
    QString m_Inputs;
    QString m_Output;

};

#endif // FUNCTION_H
