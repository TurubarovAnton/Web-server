#include "controller.h"

Controller::Controller(HttpRequest * request, WebServerSettings * settings) : request(request), settings(settings)
{

}

bool Controller::authorize()
{
    QHash<QString, QString> parameters = request->parameters;

    const QString & session = parameters.value("session");
    if (session == NULL || session.isEmpty())
        return false;
    if (Security::authorized(session)) {
        user = Security::getUser(session);
        return true;
    }
    if (parameters.contains("login") & parameters.contains("password")) {
        const QString & login = parameters.value("login");
        const QString & password = parameters.value("password");
        if (Security::login(session, login, password)) {
            user = Security::getUser(session);
            return true;
        }
    }
    return false;
}

void Controller::security(HttpResponse * response)
{
    QHash<QString, QString> parameters = request->parameters;
    const QString & session = parameters.value("session");
    if (session == NULL || session.isEmpty())
        response->addToHeader("Set-Cookie: session=" + Security::createUID() + "; path=/; HttpOnly");
    request->setUrl(settings->securityUrl);
    file(response);
}

HttpResponse * Controller::response()
{
    HttpResponse * response = new HttpResponse();

    const QString & url = request->url;
    const QString & target = request->target;
    const QString & method = request->method;

    if (target == NULL || target.isEmpty())
        request->setUrl(settings->defaultUrl);

    if (settings->security.contains(url)) {
        if (! authorize()) {
            security(response);
            return response;
        }
    }

    if (method == "GET") {
        get(response);
        return response;
    }

    if (method == "POST") {
        post(response);
        return response;
    }

    response->addToHeader("Content-Type: text");
    response->addContent("Unknown url " + request->url + "!");
    return response;
}

void Controller::get(HttpResponse * response)
{
    /*---------------------------------------------------------------------------------------

    Developer code should be placed here!!!

    -----------------------------------------------------------------------------------------*/

    file(response);
}

void Controller::post(HttpResponse * response)
{
    QString target = request->target;
    QHash<QString, QString> parameters = request->parameters;

    /*---------------------------------------------------------------------------------------

    Developer code should be placed here!!!

    -----------------------------------------------------------------------------------------*/

    file(response);
}

void Controller::file(HttpResponse * response)
{
    QString root = settings->root;
    QString url = request->url;
    QString path = root + url;

    QFile file(path);
    if (file.exists()) {
        if (file.open(QFile::ReadOnly)) {
            QString extension = request->extension;
            if (extension.count() > 0) {
                QString type = settings->contentTypes.value(extension);
                if (type.count() > 0)
                    response->addToHeader("Content-Type: " + type);
            }
            response->addContent(file.readAll());
            file.close();
        }
        else
            response->addContent(QString("File \"" + path + "\" not opened!\r\n").toUtf8());
    }
    else
        response->addContent(QString("File \"" + path + "\" not found!\r\n").toUtf8());
}






