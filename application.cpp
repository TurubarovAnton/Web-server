#include "application.h"

Application::Application(int argc, char * argv[]) : QCoreApplication(argc, argv)
{   
    server = new WebServer;

    WebServerSettings * settings = server->settings;

    QStringList paths = settings->paths;
    foreach(const QString & path, paths)
        addLibraryPath(path);

    QVectorIterator<QHash<QString, QString>> iterator(server->settings->connections);
    while (iterator.hasNext())
        createDatabaseConnection(iterator.next());

    server->start();
}

void Application::createDatabaseConnection(QHash<QString, QString> parameters)
{
    if (parameters.count() == 0)
        return;

    QString driver = parameters.value("driver");

    if (driver == NULL)
        return;

    QString connectionName = parameters.value("name");

    QSqlDatabase sqlDatabase = QSqlDatabase::addDatabase(driver, connectionName);
    sqlDatabase.setPort(parameters.value("port").toInt());
    sqlDatabase.setHostName(parameters.value("host"));
    sqlDatabase.setDatabaseName(parameters.value("database"));
    sqlDatabase.setUserName(parameters.value("user"));
    sqlDatabase.setPassword(parameters.value("password"));

    QTextStream stream(stdout);
    if (! sqlDatabase.isDriverAvailable(driver)) {
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
        QSqlDatabase::database(connectionName).close();
        QSqlDatabase::removeDatabase(connectionName);
    }

    server->close();
    server->deleteLater();
}






