#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QStringList>
#include <QHash>
#include <webserversettings.h>
#include <webserver.h>

class Application : public QCoreApplication
{
    Q_OBJECT
    public:
        Application(int argc, char * argv[]);
        ~Application();

        WebServer * server;

        static void createDatabaseConnection(QHash<QString, QString> connectionParameters);
    private:
        const QEvent::Type ApplicationStart = (QEvent::Type)(QEvent::User + 1);

        void addApplicationPaths(QStringList paths);
    protected:
        bool event(QEvent * event);

};

#endif // APPLICATION_H
