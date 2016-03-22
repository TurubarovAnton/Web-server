#ifndef SECURITY_H
#define SECURITY_H

#include <QObject>
#include <QString>
#include <QMap>
#include <iostream>
#include <QTextStream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QUuid>
#include <consolerunnable.h>

struct User {
    QString id;
    QString login;
    QString name;
};

class Security
{
    private:
        static QMap<QString, User *> sessions;

    public:
        static QString createUID();
        static User * getUser(const QString & session);

        static bool login(const QString & session, const QString & login, const QString & password);
        static bool authorized(const QString & session);
        static void logOff(const QString & session);
};

#endif // SECURITY_H
