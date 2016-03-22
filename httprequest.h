#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QString>
#include <QUrl>
#include <QDateTime>
#include <QHash>
#include <consolerunnable.h>

class HttpRequest
{
    private:
        QString request;

        void parseBody(const QString &value);
        void parseHeader(const QString &value);
        void parseUrl(const QString &value);
        void parseParameters(const QString &value);
    public:
        QString method;
        QString url;
        QString target;
        QString extension;
        QString protocol;
        QString host;
        QHash<QString, QString> parameters;

        HttpRequest(const QString & value);
        void setUrl(const QString & value);
};

#endif // HTTPREQUEST_H
