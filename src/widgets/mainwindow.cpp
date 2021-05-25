#include "mainwindow.h"

#include <QApplication>
#include <QDockWidget>
#include <QToolBar>
#include <QMdiArea>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QCloseEvent>
#include <QSettings>
#include <QScreen>
#include <QMessageBox>

#include "../constants.h"

#include "../services/clusterservice.h"
#include "../services/tenantservice.h"
#include "../services/namespaceservice.h"
#include "../widgets/newclusterwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), mdiMain(new QMdiArea(this)), treeTenants(new QTreeWidget(this)), treeClusters(new QTreeWidget(this)), tlbTenantToolbar(new QToolBar(this)),
    tlbClusterToolbar(new QToolBar(this)),  triPrevCluster(nullptr), m_ClusterService(new ClusterService(this)), m_TenantService(new TenantService(this)), m_NamespaceService(new NamespaceService(this)), m_SelectedCluster(nullptr)
{
    readSettings();
    createTenantsDock();
    createClustersDock();
    createActions();
    createStatusBar();

    this->mdiMain->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->mdiMain->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    //m_mdiArea->setViewMode(QMdiArea::ViewMode::TabbedView);
    this->mdiMain->setOption(QMdiArea::DontMaximizeSubWindowOnActivation, false);
    setCentralWidget(this->mdiMain);

    QString title(APPLICATION_NAME);
    setWindowTitle(title.append(" @ ").append(APPLICATION_VERSION));
    setWindowIcon(QIcon(":/pulsar"));
    setUnifiedTitleAndToolBarOnMac(true);

    connect(this, &MainWindow::loadClusters, this, &MainWindow::handleLoadClusters);
}

MainWindow::~MainWindow() {}

void MainWindow::initialize()
{
    emit loadClusters();
}

void MainWindow::closeEvent(QCloseEvent* _event)
{
    mdiMain->closeAllSubWindows();
    if (mdiMain->currentSubWindow())
    {
        _event->ignore();
    }
    else
    {
        writeSettings();
        _event->accept();
    }
}

void MainWindow::createActions()
{
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    this->actTokens = new QAction(QIcon(":/images/token.ico"), tr("&New Token..."), this);
    this->actTokens->setShortcuts(QKeySequence::New);
    this->actTokens->setStatusTip(tr("Create a new Role token."));
    //connect(this->actTokens, &QAction::triggered, this, &MainWindow::showNewTokenWindow);
    fileMenu->addAction(this->actTokens);

    fileMenu->addSeparator();

    const QIcon exitIcon = QIcon::fromTheme("application-exit", QIcon(":/images/exit.ico"));
    QAction* exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), qApp, &QApplication::closeAllWindows);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    fileMenu->addAction(exitAct);
}

void MainWindow::createTenantsDock()
{
    QDockWidget* dock = new QDockWidget(tr("Tenants/Namespaces"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setFeatures(QDockWidget::NoDockWidgetFeatures);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(2, 2, 2, 2);
    layout->setSpacing(1);

    this->tlbTenantToolbar->setEnabled(false);
    this->tlbTenantToolbar->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonFollowStyle);
    this->tlbTenantToolbar->setIconSize(QSize(16, 16));
    this->actNewTenant = new QAction(QIcon(":/newtenant"), tr("&New Tenant"));
    this->actNewTenant->setStatusTip(tr("Create a new Tenant."));
    QAction* actExpandAll = new QAction(QIcon(":/expandall"), tr("&Expand All"));
    actExpandAll->setStatusTip(tr("Expand all Tenants and Namespaces."));
    QAction* actCollapseAll = new QAction(QIcon(":/collapseall"), tr("&Collapse All"));
    actCollapseAll->setStatusTip(tr("Collapse all Tenants and Namespaces."));
    QAction* actRefresh = new QAction(QIcon(":/refresh"), tr("&Reflesh"));
    actRefresh->setStatusTip(tr("Reflesh Tenants and Namespaces."));
    //connect(this->actNewTenant, &QAction::triggered, this, &MainWindow::showNewTenantWindow);
    //connect(actExpandAll, &QAction::triggered, this, &MainWindow::handleExpandAll);
    //connect(actCollapseAll, &QAction::triggered, this, &MainWindow::handleCollapseAll);
    //connect(actRefresh, &QAction::triggered, this, &MainWindow::handleReflashAll);
    this->tlbTenantToolbar->addAction(this->actNewTenant);
    this->tlbTenantToolbar->addSeparator();
    this->tlbTenantToolbar->addAction(actExpandAll);
    this->tlbTenantToolbar->addAction(actCollapseAll);
    this->tlbTenantToolbar->addSeparator();
    this->tlbTenantToolbar->addAction(actRefresh);
    layout->addWidget(this->tlbTenantToolbar);

    this->treeTenants->setHeaderHidden(true);
    layout->addWidget(this->treeTenants);

    QWidget* dockWidget = new QWidget(dock);
    dockWidget->setLayout(layout);
    dock->setWidget(dockWidget);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    //this->m_viewMenu->addAction(dock->toggleViewAction());
}

void MainWindow::createClustersDock()
{
    QDockWidget* dock = new QDockWidget(tr("Clusters"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setFeatures(QDockWidget::NoDockWidgetFeatures);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(2, 2, 2, 2);
    layout->setSpacing(1);

    this->tlbClusterToolbar->setToolButtonStyle(Qt::ToolButtonFollowStyle);
    this->tlbClusterToolbar->setIconSize(QSize(16, 16));
    this->actNewCluster = new QAction(QIcon(":/addnew"), tr("&New Cluster"));
    this->actNewCluster->setStatusTip(tr("Create a new cluster."));
    this->actEditCluster = new QAction(QIcon(":/modify"), tr("&Modify Cluster"));
    this->actEditCluster->setStatusTip(tr("Modify an existing cluster."));
    this->actDelCluster = new QAction(QIcon(":/remove"), tr("&Delete Cluster"));
    this->actDelCluster->setStatusTip(tr("Delete an existing cluster."));
    connect(this->actNewCluster, &QAction::triggered, this, &MainWindow::handleNewClusterWindow);
    connect(this->actDelCluster, &QAction::triggered, this, &MainWindow::handleDeleteCluster);
    this->tlbClusterToolbar->addAction(this->actNewCluster);
    this->tlbClusterToolbar->addAction(this->actEditCluster);
    this->tlbClusterToolbar->addSeparator();
    this->tlbClusterToolbar->addAction(this->actDelCluster);
    layout->addWidget(this->tlbClusterToolbar);

    this->treeClusters->setHeaderHidden(true);
    connect(this->treeClusters, &QTreeWidget::itemDoubleClicked, this, &MainWindow::handleClusterTreeItemDoubleClicked);
    layout->addWidget(this->treeClusters);

    QWidget* dockWidget = new QWidget(dock);
    dockWidget->setLayout(layout);
    dock->setWidget(dockWidget);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    //this->m_viewMenu->addAction(dock->toggleViewAction());
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty())
    {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
    else
    {
        restoreGeometry(geometry);
    }
    this->m_ClusterService->read();
}

void MainWindow::writeSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
    this->m_ClusterService->write();
}

void MainWindow::handleLoadClusters()
{
    this->treeClusters->clear();
    //load all Clusters into the tree widget.
    QList<Cluster> roots = this->m_ClusterService->tolist();
    Q_FOREACH (const Cluster& _cluster, roots)
    {
        QTreeWidgetItem* item = new  QTreeWidgetItem(this->treeClusters);
        item->setText(0, _cluster.name());
        item->setIcon(0, QIcon(":/disconnected"));
        item->setData(0, Qt::UserRole, QVariant::fromValue(_cluster));
        this->treeClusters->insertTopLevelItem(0, item);
    }
}

void MainWindow::handleNewClusterWindow(bool)
{
    NewClusterWindow* win = new NewClusterWindow;
    connect(win, SIGNAL(completeNewCluster(Cluster)), this, SLOT(handleInsertTreeItem(Cluster)));
    connect(this, &MainWindow::activateNewClusterWindow, win, &NewClusterWindow::afterWindowActivated);
    emit activateNewClusterWindow(this->m_ClusterService);
    win->exec();
}

void MainWindow::handleInsertTreeItem(const Cluster& _cluster)
{
    QTreeWidgetItem* item = new QTreeWidgetItem(this->treeClusters);
    item->setText(0, _cluster.name());
    item->setIcon(0, QIcon(":/disconnected"));
    item->setData(0, Qt::UserRole, QVariant::fromValue(_cluster));
    this->treeClusters->insertTopLevelItem(0, item);
}

void MainWindow::handleClusterTreeItemDoubleClicked(QTreeWidgetItem* _item, int)
{
    QVariant data = _item->data(0, Qt::UserRole);
    if (data.canConvert<Cluster>())
    {
        Cluster cluster = data.value<Cluster>();
        this->m_SelectedCluster = &cluster;
        if (this->m_SelectedCluster->status() == Cluster::Status::Disconnected)
        {
            this->mdiMain->closeAllSubWindows();
        }
        this->m_SelectedCluster->setStatus(Cluster::Status::Connected);
        this->treeTenants->clear();
        //load all Tenants and Namespaces.
        QList<Tenant> roots = this->m_TenantService->tenants(cluster);
        Q_FOREACH (const Tenant& tenant, roots)
        {
            QTreeWidgetItem* item = new  QTreeWidgetItem(this->treeTenants);
            item->setText(0, tenant.name());
            item->setIcon(0, QIcon(":/tenant"));
            item->setData(0, Qt::UserRole, QVariant::fromValue(tenant));

            QList<Namespace> namespaces = this->m_NamespaceService->namespaces(tenant);
            foreach (const Namespace& ns, namespaces)
            {
                QTreeWidgetItem* subitem = new QTreeWidgetItem(item);
                subitem->setText(0, ns.name());
                subitem->setIcon(0, QIcon(":/namespace"));
                subitem->setData(0, Qt::UserRole, QVariant::fromValue(ns));
            }
            this->treeTenants->insertTopLevelItem(0, item);
        }
        if (this->triPrevCluster && this->triPrevCluster != _item)
        {
            this->triPrevCluster->setIcon(0, QIcon(":/disconnected"));
            Cluster prev = this->triPrevCluster->data(0, Qt::UserRole).value<Cluster>();
            prev.setStatus(Cluster::Status::Disconnected);
            this->triPrevCluster->setData(0, Qt::UserRole, QVariant::fromValue(prev));
        }
        this->triPrevCluster = _item;
        _item->setIcon(0, QIcon(":/connected"));
        _item->setData(0, Qt::UserRole, QVariant::fromValue(cluster));
        this->tlbTenantToolbar->setEnabled(true);
    }
}

void MainWindow::handleDeleteCluster(bool)
{
    QMessageBox::StandardButton button = QMessageBox::question(this, tr("Delete Cluster"), tr("Would you like to remove this Cluster?"));
    if (button == QMessageBox::Yes)
    {
        QTreeWidgetItem* item = this->treeClusters->currentItem();
        if (item)
        {
            QVariant data = item->data(0, Qt::UserRole);
            if (data.canConvert<Cluster>())
            {
                Cluster cluster = data.value<Cluster>();

                if (cluster.status() == Cluster::Status::Connected)
                {
                    this->tlbTenantToolbar->setEnabled(false);
                    this->mdiMain->closeAllSubWindows();
                    this->treeTenants->clear();
                }
                this->m_ClusterService->removeCluster(cluster);
                delete item;
            }
        }
        else
        {
            QMessageBox::warning(this, "Warning", "The Cluster must be selected at first.");
        }
    }
}

