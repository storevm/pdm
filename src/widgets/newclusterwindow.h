#ifndef NEWCLUSTERWINDOW_H
#define NEWCLUSTERWINDOW_H

#include <QDialog>
#include <QLineEdit>

class ClusterService;
class Cluster;

class NewClusterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewClusterWindow(QWidget* parent = nullptr);

signals:
    void completeNewCluster(const Cluster&);

public slots:
    void afterWindowActivated(ClusterService* _service);

private:
    QLineEdit* tbName;
    QLineEdit* tbServiceUrl;
    QLineEdit* tbFunctionUrl;
    QLineEdit* tbPrestoUrl;
    QPushButton* btnOk;
    QPushButton* btnCancel;

    ClusterService* m_ClusterService;

private slots:
    void handleNewCluster();

};

#endif // NEWCLUSTERWINDOW_H
