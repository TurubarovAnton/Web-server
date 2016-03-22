#include "webserver.h"

WebServer::WebServer(QObject * parent) : QTcpServer(parent)
{
    settings = new WebServerSettings(this);
}

void WebServer::incomingConnection(qintptr handle)
{
    new HttpSocket(handle, settings);
}

void WebServer::start()
{
    int port = settings->port;

    QTextStream stream(stdout);
    if (listen(QHostAddress::Any, port))
        stream << "Server listening port " + QString::number(port) + "...\r\n";
    else
        stream << "Server failed!\r\n";
}

WebServer::~WebServer()
{
    delete settings;
}



