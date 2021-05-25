#ifndef SINK_H
#define SINK_H

#include "basefunction.h"

typedef QMap<QString, QString> SinkData;

class Sink : public BaseFunction
{
public:
    explicit Sink();
    Sink(const Sink& _other) { *this = _other; }
    Sink& operator=(const Sink& _other);
    virtual ~Sink();

    inline void setInputs(const QStringList& _inputs) { this->m_Inputs = _inputs; }
    inline QStringList inputs() const { return this->m_Inputs; }

    virtual QByteArray toJson() const override;
    void appendStatus(const QByteArray& _json);
    inline void addInput(const QString& _input) { this->m_Inputs.append(_input); }
    virtual void appendInfo(const QByteArray& _json) override;
    SinkData toData() const;

private:
    QStringList m_Inputs;

};

Q_DECLARE_METATYPE(Sink);

#endif // SINK_H
