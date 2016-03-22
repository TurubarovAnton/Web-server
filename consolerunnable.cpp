#include "consolerunnable.h"

ConsoleRunnable::ConsoleRunnable(const QString & message, QObject * parent) : QObject(parent), message(message)
{
    setAutoDelete(true);

    QThreadPool::globalInstance()->start(this);
}

void ConsoleRunnable::run()
{
    QTextStream stream(stdout);
    stream << message;
}

