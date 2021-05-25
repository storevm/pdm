#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QMdiArea;
class QTreeWidget;
class QToolBar;
class QTreeWidgetItem;
class ClusterService;
class TenantService;
class NamespaceService;
class Cluster;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void initialize();

signals:
    void loadClusters();
    void activateNewClusterWindow(ClusterService* _service);

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void createActions();
    void createTenantsDock();
    void createClustersDock();
    void createStatusBar();
    void readSettings();
    void writeSettings();

private slots:
    void handleLoadClusters();
    void handleNewClusterWindow(bool);
    void handleInsertTreeItem(const Cluster& _cluster);
    void handleClusterTreeItemDoubleClicked(QTreeWidgetItem* _item, int _column);
    void handleDeleteCluster(bool);

private:
    QMdiArea* mdiMain;
    QTreeWidget* treeTenants;
    QTreeWidget* treeClusters;
    QToolBar* tlbTenantToolbar;
    QToolBar* tlbClusterToolbar;
    QTreeWidgetItem* triPrevCluster;

    QAction* actTokens;
    QAction* actNewTenant;
    QAction* actNewCluster;
    QAction* actDelCluster;
    QAction* actEditCluster;
    QAction* actDelTenant;
    QAction* actNewNamespace;
    QAction* actDelNamespace;
    QAction* actFunctions;
    QAction* actSinks;
    QAction* actSources;
    QAction* actPermission;

    QAction* closeAct;
    QAction* closeAllAct;
    QAction* tileAct;
    QAction* cascadeAct;
    QAction* nextAct;
    QAction* previousAct;
    QAction* windowMenuSeparatorAct;

    ClusterService* m_ClusterService;
    TenantService* m_TenantService;
    NamespaceService* m_NamespaceService;
    Cluster* m_SelectedCluster;

};
#endif // MAINWINDOW_H
