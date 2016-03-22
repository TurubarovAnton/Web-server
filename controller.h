#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <webserversettings.h>
#include <httprequest.h>
#include <httpresponse.h>
#include <consolerunnable.h>
#include <security.h>

class Controller
{
    private:
        HttpRequest * request;
        WebServerSettings * settings;
        User * user;

        void get(HttpResponse * response);
        void post(HttpResponse * response);
        void file(HttpResponse * response);

        bool authorize();
        void security(HttpResponse * response);
    public:
        Controller(HttpRequest * request, WebServerSettings * settings);

        HttpResponse * response();
};

#endif // CONTROLLER_H
