#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QSqlDatabase>
#include <QSettings>
#include <QtCrypto/QtCrypto>
#include <QTextCodec>

#include <log4qt/propertyconfigurator.h>
#include <log4qt/logger.h>

#include "constants.h"

int main(int argc, char* argv[])
{
    Q_INIT_RESOURCE(resources);

#if(QT_VERSION >=QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);

    //at first, initialize Log4qt
    QDir dir(CONFIG_DIR);
    Log4Qt::PropertyConfigurator::configure(dir.absoluteFilePath(LOG_CFG_FILE));

    QDir path(QCoreApplication::applicationDirPath());
    QCoreApplication::addLibraryPath(path.absoluteFilePath("plugins"));
    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("Application plugins library paths: %1", QCoreApplication::libraryPaths().join(";"));
    }

    //the second, initialize database connection.
    QStringList drivers = QSqlDatabase::drivers();
    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Q_FOREACH (const QString& driver, drivers)
            Log4Qt::Logger::logger("main")->debug("database driver: %1", driver);
    }
    QSettings* settings = new QSettings(QDir(CONFIG_DIR).absoluteFilePath(INI_FILE), QSettings::IniFormat);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=10;");
    db.setHostName(settings->value("MYSQL_SERVER/HOST").toString());
    db.setPort(settings->value("MYSQL_SERVER/PORT").toInt());
    db.setDatabaseName(settings->value("MYSQL_SERVER/DATABASE").toString());
    db.setUserName(settings->value("MYSQL_SERVER/USERNAME").toString());
    db.setPassword(settings->value("MYSQL_SERVER/PASSWORD").toString());
    bool success = db.open();
    if (!success)
    {
        db.setConnectOptions();
    }
    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        Log4Qt::Logger::logger("main")->debug("database connect: %1", success ? "true" : "false");
    }
    delete settings;

    QCA::Initializer init;
    if (Log4Qt::Logger::logger("main")->isDebugEnabled())
    {
        QStringList paths = QCA::pluginPaths();
        Q_FOREACH (const QString& path, paths)
            Log4Qt::Logger::logger("main")->debug("QCA plugins path: %1", QDir::toNativeSeparators(path));

        QCA::ProviderList list = QCA::providers();
        for (int n = 0; n < list.count(); ++n)
        {
            QString str = QCA::pluginDiagnosticText();
            Log4Qt::Logger::logger("main")->debug("Available Plugin Diagnostic: %1", str);
            QCA::clearPluginDiagnosticText();

            Log4Qt::Logger::logger("main")->debug("Available Providers: %1", list[n]->name());
            QString credit = list[n]->credit();
            Log4Qt::Logger::logger("main")->debug("Available Providers Credit: %1", credit);
        }
        QStringList features = QCA::supportedFeatures();
        Q_FOREACH (const QString& feature, features)
            Log4Qt::Logger::logger("main")->debug("QCA feature: %1", feature);
    }

    // codec
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setApplicationVersion(APPLICATION_VERSION);

    MainWindow w;
    w.show();
    return a.exec();
}
