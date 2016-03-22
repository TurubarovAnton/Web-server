#include "httprequest.h"

HttpRequest::HttpRequest(const QString & value): request(value)
{
    QStringList lines = value.split("\r\n\r\n");

    parseBody(lines.first());
    parseParameters(lines.last());
}

void HttpRequest::parseBody(const QString & value)
{
    QStringList lines = value.split("\r\n");

    QString header = lines.first();

    parseHeader(header);

    QString message = "\r\nRequest " + QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss") + ":\r\n" + header + "\r\n";

    for (int index = 1; index < lines.count(); ++index) {
        QString line = lines.value(index);
        message += line + "\r\n";
        QStringList keyValue = line.split(":");
        if (keyValue.count() < 2)
            continue;
        const QString & key = keyValue.first().trimmed();
        const QString & value = keyValue.last().trimmed();
        if (key == "Host") {
            host = value;
            continue;
        }
        if (key == "Cookie")
            parseParameters(value);
    }

    new ConsoleRunnable(message);
}

void HttpRequest::parseHeader(const QString & value)
{
    QStringList lines = value.split(" ");

    method = lines.first().trimmed();

    if (lines.count() < 2)
        return;

    parseUrl(lines.value(1).trimmed());

    if (lines.count() < 3)
        return;

    protocol = lines.value(2).trimmed();
}

void HttpRequest::parseUrl(const QString & value)
{
    QStringList lines = value.split("?");
    url = lines.first().trimmed();
    target = url.split("/").last();
    int position = target.lastIndexOf(".");
    if (position > 0)
        extension = target.right(target.count() - position - 1);

    if (lines.count() < 2)
        return;

    parseParameters(lines.last());
}

void HttpRequest::parseParameters(const QString & value)
{
    if (value.isEmpty())
        return;

    QStringList lines = QString(QUrl::fromPercentEncoding(value.toUtf8())).split("&");
    foreach (const QString line, lines) {
        QStringList keyValue = line.split("=");
        if (keyValue.count() == 2)
            parameters.insert(keyValue.first().trimmed(), keyValue.last());
    }
}

void HttpRequest::setUrl(const QString & value)
{
    url = value.trimmed();
    target = url.split("/").last();
    int position = target.lastIndexOf(".");
    if (position > 0)
        extension = target.right(target.count() - position - 1);
}
