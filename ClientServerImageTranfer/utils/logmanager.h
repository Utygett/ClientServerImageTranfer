#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMutexLocker>
#include <iostream>
class LogManager
{
private:
    static QMutex m_mutexSynchFileAccess;
    LogManager() = delete;
    ~LogManager() = delete;
public:
    static void warning(const QString &);
    static void error(const QString &);
    static void fatal(const QString &);
    static void message(const QString &);
};

#endif // ERRORMANAGER_H
