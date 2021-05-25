#ifndef SOURCE_H
#define SOURCE_H

#include "basefunction.h"

class Source : public BaseFunction
{
public:
    explicit Source();
    Source(const Source& _other) { *this = _other; }
    Source& operator=(const Source& _other);

    QString classname() const { return this->m_Classname; };
    void setClassname(const QString& _classname) { this->m_Classname = _classname; };

    QString topicName() const { return this->m_TopicName; };
    void setTopicName(const QString& _topicName) { this->m_TopicName = _topicName; };

    QByteArray toJson() const override;

private:
    QString m_Classname;
    QString m_TopicName;

};

#endif // SOURCE_H
