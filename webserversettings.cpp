#include "webserversettings.h"

WebServerSettings::WebServerSettings(QObject * parent) : QObject(parent)
{
    load();
}

void WebServerSettings::load()
{
    QString path = "conf.txt";
    QFile jsonFile(path);
    if (jsonFile.exists()) {
        if (jsonFile.open(QFile::ReadOnly | QFile::Text)) {
            QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonFile.readAll());
            QJsonObject jsonObject = jsonDocument.object();

            port = jsonObject.value("port").toInt();
            root = jsonObject.value("root").toString().trimmed();
            defaultUrl = jsonObject.value("defaultUrl").toString().trimmed();
            securityUrl = jsonObject.value("securityUrl").toString().trimmed();

            parseContentTypes(jsonObject.value("contentTypes").toObject());
            parseConnections(jsonObject.value("connections").toArray());
            parsePaths(jsonObject.value("paths").toArray());
            parseSecurity(jsonObject.value("security").toArray());
        }
    }
    else
        QTextStream(stdout) << "File \"" + path + "\" not found!\r\n";
}


void WebServerSettings::parseContentTypes(QJsonObject jsonObject)
{
    QStringList keys = jsonObject.keys();
    foreach (const QString & key, keys)
        contentTypes.insert(key, jsonObject.value(key).toString().trimmed());
}

void WebServerSettings::parseConnections(QJsonArray jsonArray)
{
    foreach (QJsonValue jsonValue, jsonArray) {
        QJsonObject jsonObject = jsonValue.toObject();
        QStringList keys = jsonObject.keys();
        QHash<QString, QString> parameters;
        foreach (const QString & key, keys)
            parameters.insert(key, jsonObject.value(key).toVariant().toString().trimmed());
        connections.append(parameters);
    }
}

void WebServerSettings::parsePaths(QJsonArray jsonArray)
{
    foreach (QJsonValue jsonValue, jsonArray)
        paths.append(jsonValue.toString().trimmed());
}

void WebServerSettings::parseSecurity(QJsonArray jsonArray)
{
    foreach (QJsonValue jsonValue, jsonArray)
        security.append(jsonValue.toString().trimmed());
}




