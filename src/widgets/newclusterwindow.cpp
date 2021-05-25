#include "newclusterwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QIcon>
#include <QPushButton>
#include <QMessageBox>
#include <QSettings>
#include <QCoreApplication>

#include <log4qt/logger.h>

#include "../services/clusterservice.h"

NewClusterWindow::NewClusterWindow(QWidget* parent) : QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;

    QFormLayout* formLayout = new QFormLayout;
    this->tbName = new QLineEdit;
    this->tbServiceUrl =  new QLineEdit;
    this->tbFunctionUrl = new QLineEdit;
    this->tbPrestoUrl = new QLineEdit;
    formLayout->addRow(tr("&Cluster Name:"), this->tbName);
    formLayout->addRow(tr("&Admin Service URL:"), this->tbServiceUrl);
    formLayout->addRow(tr("&Function Service URL:"), this->tbFunctionUrl);
    formLayout->addRow(tr("&Presto Service URL:"), this->tbPrestoUrl);


    QHBoxLayout* buttonLayout = new QHBoxLayout;

#ifdef Q_OS_MACX
    this->btnOk = new QPushButton(tr("&Ok"));
    this->btnCancel = new QPushButton(tr("&Cancel"));
#else
    const QIcon okIcon = QIcon::fromTheme("emblem-default", QIcon(":/ok.png"));
    this->btnOk = new QPushButton(okIcon, tr("&Ok"));
    const QIcon cancelIcon = QIcon::fromTheme("window-close", QIcon(":/cancel.png"));
    this->btnCancel = new QPushButton(cancelIcon, tr("&Cancel"));
#endif

    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->addStretch();
    buttonLayout->addWidget(this->btnOk);
    buttonLayout->addSpacing(5);
    buttonLayout->addWidget(this->btnCancel);
    layout->addLayout(formLayout);
    layout->addLayout(buttonLayout);

    setLayout(layout);
    setFixedSize(QSize(560, 190));
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(tr("New Cluster"));
    setWindowIcon(QIcon(":/newcluster.png"));
    setWindowFlags(Qt::WindowCloseButtonHint);

    connect(this->btnOk, &QPushButton::clicked, this, &NewClusterWindow::handleNewCluster);
    connect(this->btnCancel, &QPushButton::clicked, this, &NewClusterWindow::close);
}

void NewClusterWindow::afterWindowActivated(ClusterService* _service)
{
    this->m_ClusterService = _service;
}

void NewClusterWindow::handleNewCluster()
{
    //check input items
    if (this->tbName->text().isEmpty())
    {
        QMessageBox::critical(this, tr("Error"), tr("Name input items must be entered."));
        this->tbName->setFocus();
        return;
    }
    else if (this->tbServiceUrl->text().isEmpty())
    {
        QMessageBox::critical(this, tr("Error"), tr("Admin Service URL input items must be entered."));
        this->tbServiceUrl->setFocus();
        return;
    }
    else if (this->m_ClusterService->exist(this->tbName->text()))
    {
        QMessageBox::critical(this, tr("Error"), tr("Broker is exist."));
        this->tbName->setFocus();
        return;
    }

    //todo:is check the url invalid?
    Cluster cluster;
    cluster.setName(this->tbName->text());
    cluster.setAdminUrl(this->tbServiceUrl->text());
    cluster.setFunctionUrl(this->tbFunctionUrl->text());
    cluster.setPrestoUrl(this->tbPrestoUrl->text());
    this->m_ClusterService->addCluster(cluster);

    emit completeNewCluster(cluster);
    close();
}
