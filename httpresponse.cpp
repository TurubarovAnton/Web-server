#include "httpresponse.h"

HttpResponse::HttpResponse()
{
    header = "HTTP/1.1 200 OK";
}

void HttpResponse::addToHeader(const QString & value)
{
    header += "\r\n" + value;
}

void HttpResponse::addContent(const QString & value)
{
    content += value.toUtf8();
}

void HttpResponse::addContent(QByteArray value)
{
    content += value;
}

QByteArray HttpResponse::toByteArray()
{
    return QString(header + "\r\n\r\n").toUtf8() + content;
}

