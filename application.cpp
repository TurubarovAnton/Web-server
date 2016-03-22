#include "application.h"

Application::Application(int argc, char * argv[]) : QCoreApplication(argc, argv)
{   
    server = new WebServer;

    addApplicationPaths(server->settings->paths);

    postEvent(this, new QEvent(ApplicationStart));
}

bool Application::event(QEvent * event)
{
    if (event->type() == ApplicationStart) {
        createDatabaseConnection(server->settings->connectionParameters);
        server->start();
        return true;
    }
    return false;
}

void Application::addApplicationPaths(QStringList paths)
{
    foreach(const QString & path, paths)
        addLibraryPath(path);
}

void Application::createDatabaseConnection(QHash<QString, QString> connectionParameters)
{
    if (connectionParameters.count() == 0)
        return;

    QString driver = connectionParameters.value("driver");

    if (driver == NULL)
        return;

    QString connectionName = connectionParameters.value("name");

    QSqlDatabase sqlDatabase = QSqlDatabase::addDatabase(driver, connectionName);
    sqlDatabase.setPort(connectionParameters.value("port").toInt());
    sqlDatabase.setHostName(connectionParameters.value("host"));
    sqlDatabase.setDatabaseName(connectionParameters.value("database"));
    sqlDatabase.setUserName(connectionParameters.value("user"));
    sqlDatabase.setPassword(connectionParameters.value("password"));

    QTextStream stream(stdout);
    if (!sqlDatabase.isDriverAvailable(driver)) {
        stream << "SQL driver not available!\r\n";
        return;
    }
    if (sqlDatabase.open())
        stream << connectionName + " database connected!\r\n\r\n";
    else {
        stream << connectionName + " database connection failed!\r\n\r\n";
        stream << sqlDatabase.lastError().text() + "\r\n";
    }
}

Application::~Application()
{
    QStringList connectionNames = QSqlDatabase::connectionNames();
    foreach (const QString & connectionName, connectionNames) {
        QSqlDatabase sqlDatabase = QSqlDatabase::database(connectionName);
        sqlDatabase.close();
        QSqlDatabase::removeDatabase(connectionName);
    }

    server->close();
    server->deleteLater();
}






