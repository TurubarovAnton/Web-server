#include "controllerrunable.h"

ControllerRunnable::ControllerRunnable(const QString & message, WebServerSettings * settings, QObject * parent) : QObject(parent), message(message), settings(settings)
{
    setAutoDelete(true);
}

void ControllerRunnable::run()
{
    HttpRequest * request = new HttpRequest(message);

    completed(Controller(request, settings).response());

    delete request;
}

void ControllerRunnable::start()
{
    QThreadPool::globalInstance()->start(this);
}

