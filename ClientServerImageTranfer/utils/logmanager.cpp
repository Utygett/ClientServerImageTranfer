#include "logmanager.h"
#include <QtDebug>

QMutex LogManager::m_mutexSynchFileAccess;

void LogManager::warning(const QString &strMessage)
{
    QMutexLocker lock(&m_mutexSynchFileAccess);
    QDateTime timeDate;
    std::cout << strMessage.toStdString() << std::endl;
    timeDate = QDateTime::currentDateTime();
    QScopedPointer<QFile> logFile;
    logFile.reset(new QFile("logFile.txt"));
    logFile.data()->open(QFile::Append | QFile::Text);
    QTextStream out(logFile.data());
    out << timeDate.toString("yyyy-MM-dd hh:mm:ss.zzz ") << " WARNING " << strMessage << endl;
    out.flush();
    logFile->close();
}

void LogManager::error(const QString &strMessage)
{
    QMutexLocker lock(&m_mutexSynchFileAccess);
    std::cout << strMessage.toStdString() << std::endl;
    QDateTime timeDate;
    timeDate = QDateTime::currentDateTime();
    QScopedPointer<QFile> logFile;
    logFile.reset(new QFile("logFile.txt"));
    logFile.data()->open(QFile::Append | QFile::Text);
    QTextStream out(logFile.data());
    out << timeDate.toString("yyyy-MM-dd hh:mm:ss.zzz ") << " ERROR " << strMessage << endl;
    out.flush();
    logFile->close();
}

void LogManager::fatal(const QString &strMessage)
{
    QMutexLocker lock(&m_mutexSynchFileAccess);
    QDateTime timeDate;
    timeDate = QDateTime::currentDateTime();
    QScopedPointer<QFile> logFile;
    logFile.reset(new QFile("logFile.txt"));
    logFile.data()->open(QFile::Append | QFile::Text);
    QTextStream out(logFile.data());
    out << timeDate.toString("yyyy-MM-dd hh:mm:ss.zzz ") << " FATAL " << strMessage << endl;
    out.flush();
    logFile->close();
}

void LogManager::message(const QString &strMessage)
{
    QMutexLocker lock(&m_mutexSynchFileAccess);
    std::cout << strMessage.toStdString() << std::endl;
    QDateTime timeDate;
    timeDate = QDateTime::currentDateTime();
    QScopedPointer<QFile> logFile;
    logFile.reset(new QFile("messageLog.txt"));
    logFile.data()->open(QFile::Append | QFile::Text);
    QTextStream out(logFile.data());
    out << timeDate.toString("yyyy-MM-dd hh:mm:ss.zzz ") << " MESSAGE " << strMessage << endl;
    out.flush();
    logFile->close();
}

