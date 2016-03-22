#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <QObject>
#include <QTcpServer>
#include <iostream>
#include <QTextStream>
#include <webserversettings.h>
#include <httpsocket.h>

class WebServer : public QTcpServer
{
    Q_OBJECT
    public:
        WebServer(QObject * parent = 0);
        ~WebServer();

        WebServerSettings * settings;

        void incomingConnection(qintptr handle);
        void start();
};

#endif // WEBSERVER_H

