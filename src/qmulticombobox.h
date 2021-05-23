#ifndef QMULTICOMBOBOX_H
#define QMULTICOMBOBOX_H

#include <QComboBox>

class QListWidget;

class QMultiComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit QMultiComboBox(const QStringList& _items, QWidget* _parent = nullptr);
    virtual ~QMultiComboBox();

    QStringList selectedItems() const;
    void reset();

public slots:
    void stateChanged(int _state);
    void textChanged(const QString& _text);

signals:
    void selectOver();

private:
    QListWidget* dlList;
    QLineEdit* tbLine;
    QStringList m_items;
    QStringList m_selected;

};

#endif // QMULTICOMBOBOX_H
