#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QStringList>
#include <QVector>
#include <QHash>
#include <iostream>
#include <QTextStream>
#include <webserversettings.h>
#include <webserver.h>

class Application : public QCoreApplication
{
    Q_OBJECT
    public:
        Application(int argc, char * argv[]);
        ~Application();

        WebServer * server;

        static void createDatabaseConnection(QHash<QString, QString> parameters);
};

#endif // APPLICATION_H
