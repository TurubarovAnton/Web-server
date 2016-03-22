#ifndef WEBSERVERSETTINGS_H
#define WEBSERVERSETTINGS_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <iostream>
#include <QTextStream>
#include <QHash>
#include <QFile>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class WebServerSettings : public QObject
{
    public:
        explicit WebServerSettings(QObject * parent = 0);

        int port;
        QString root;
        QString defaultUrl;
        QString securityUrl;

        QHash<QString, QString> contentTypes;
        QHash<QString, QString> connectionParameters;

        QStringList paths;
        QStringList security;

    private:
        void load();
        void parseContentTypes(QJsonObject jsonObject);
        void parseConnectionParameters(QJsonObject jsonObject);
        void parsePaths(QJsonArray jsonArray);
        void parseSecurity(QJsonArray jsonArray);
};

#endif // WEBSERVERSETTINGS_H
