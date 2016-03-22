#ifndef CONTROLLERRUNABLE_H
#define CONTROLLERRUNABLE_H

#include <QObject>
#include <QRunnable>
#include <QThreadPool>
#include <webserversettings.h>
#include <httprequest.h>
#include <httpresponse.h>
#include <controller.h>

class ControllerRunnable : public QObject, public QRunnable
{
    Q_OBJECT
    public:
        ControllerRunnable(const QString & message, WebServerSettings * settings, QObject * parent = 0);

        void run();
        void start();
    signals:
        completed(HttpResponse * message);
    private:
        QString message;
        WebServerSettings * settings;
};

#endif // CONTROLLERRUNABLE_H
