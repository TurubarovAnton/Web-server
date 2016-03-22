#ifndef CONSOLERUNNABLE_H
#define CONSOLERUNNABLE_H

#include <QObject>
#include <QThreadPool>
#include <QRunnable>
#include <QString>
#include <QTextStream>
#include <iostream>

class ConsoleRunnable : public QObject, public QRunnable
{
    Q_OBJECT
    public:
        ConsoleRunnable(const QString & message, QObject * parent = 0);
    private:
        QString message;

        void run();
};

#endif // CONSOLERUNNABLE_H
