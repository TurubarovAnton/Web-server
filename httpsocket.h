#ifndef HTTPSOCKET_H
#define HTTPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <webserversettings.h>
#include <controllerrunable.h>
#include <httpresponse.h>

class HttpSocket : public QTcpSocket
{
    Q_OBJECT
    public:
        HttpSocket(qintptr descriptor, WebServerSettings * settings, QObject * parent = 0);
    private:
        WebServerSettings * settings;
    public slots:
        void request();
        void response(HttpResponse * response);
        void destroy();
};

#endif // HTTPSOCKET_H
