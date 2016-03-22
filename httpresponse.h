#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QString>
#include <QByteArray>

class HttpResponse
{
    private:
        QString header;
        QByteArray content;
    public:
        HttpResponse();

        void addToHeader(const QString & value);
        void addContent(const QString & value);
        void addContent(QByteArray value);        
        QByteArray toByteArray();
};

#endif // HTTPRESPONSE_H
