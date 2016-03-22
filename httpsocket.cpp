#include "httpsocket.h"

HttpSocket::HttpSocket(qintptr descriptor,  WebServerSettings * settings, QObject * parent): QTcpSocket(parent), settings(settings)
{
    setSocketDescriptor(descriptor);

    connect(this, SIGNAL(readyRead()), this, SLOT(request()));
    connect(this, SIGNAL(disconnected()), this, SLOT(destroy()));
}

void HttpSocket::request()
{
    ControllerRunnable * runnable = new ControllerRunnable(readAll(), settings);
    connect(runnable, SIGNAL(completed(HttpResponse *)), this, SLOT(response(HttpResponse *)));
    runnable->start();
}

void HttpSocket::response(HttpResponse * response)
{
    write(response->toByteArray());
    disconnectFromHost();

    delete response;
}

void HttpSocket::destroy()
{
    close();
    deleteLater();
}

