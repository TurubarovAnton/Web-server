#include "security.h"

QMap<QString, User *> Security::sessions;

QString Security::createUID()
{
    QString uid = QUuid::createUuid().toString();
    uid = uid.replace(QRegExp("[{}-]"), NULL);
    return uid;
}

User * Security::getUser(const QString & session)
{
    return sessions.value(session.trimmed());
}

bool Security::login(const QString & session, const QString & login, const QString & password)
{
    /*---------------------------------------------------------------------------------------

    Developer code should be placed here!!!

    -----------------------------------------------------------------------------------------*/

    return false;
}

bool Security::authorized(const QString & session)
{
    return sessions.contains(session.trimmed());
}

void Security::logOff(const QString & session)
{
    sessions.remove(session.trimmed());
}
