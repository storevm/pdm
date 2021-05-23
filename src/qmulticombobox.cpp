#include "qmulticombobox.h"

#include <QStringList>
#include <QListWidget>
#include <QLineEdit>
#include <QListWidgetItem>
#include <QCheckBox>

#include <log4qt/logger.h>

QMultiComboBox::QMultiComboBox(const QStringList& _items, QWidget* _parent) : QComboBox(_parent), m_items(_items)
{
    this->dlList = new QListWidget(this);
    this->dlList->setContentsMargins(0, 0, 0, 0);
    this->dlList->setSpacing(2);
    //this->dlList->setStyleSheet("QListWidget {padding: 2px;} QListWidget::item { margin: 2px; }");
    this->tbLine = new QLineEdit(this);

    QStringList::const_iterator it;
    for (it = this->m_items.constBegin(); it != this->m_items.constEnd(); ++it)
    {
        QListWidgetItem* item = new QListWidgetItem(this->dlList);
        //this->list->addItem(item);
        //item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item->setData(Qt::UserRole, *it);
        QCheckBox* checkBox = new QCheckBox(this);
        checkBox->setText(*it);
        this->dlList->addItem(item);
        this->dlList->setItemWidget(item, checkBox);
        connect(checkBox, &QCheckBox::stateChanged, this, &QMultiComboBox::stateChanged);
    }
    this->setModel(this->dlList->model());
    this->setView(this->dlList);
    this->setLineEdit(this->tbLine);
    this->tbLine->setReadOnly(true);
    connect(this->tbLine, &QLineEdit::textChanged, this, &QMultiComboBox::textChanged);
}

QMultiComboBox::~QMultiComboBox() {}

void QMultiComboBox::textChanged(const QString& _text)
{
    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("textChanged: %1", _text);
    }
}

void QMultiComboBox::stateChanged(int)
{
    QCheckBox* checkbox = qobject_cast<QCheckBox*>(QObject::sender());
    if (checkbox->isChecked())
    {
        this->m_selected << checkbox->text();
    }
    else
    {
        this->m_selected.removeAll(checkbox->text());
    }
    this->tbLine->setText(this->m_selected.join(","));
    emit selectOver();
}

QStringList QMultiComboBox::selectedItems() const
{
    return this->m_selected;
}

void QMultiComboBox::reset()
{
    this->clearEditText();
    int count = this->dlList->count();
    for (int i = 0, n = count; i < n; i++)
    {
        QListWidgetItem* item = this->dlList->item(i);
        QWidget* widget = this->dlList->itemWidget(item);
        QCheckBox* checkbox = qobject_cast<QCheckBox*>(widget);
        if (checkbox->isChecked())
            checkbox->setChecked(false);
    }
}
