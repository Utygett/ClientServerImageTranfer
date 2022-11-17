#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QDateTime>
#include <QMutex>
#include <QMap>
#include <iostream>


class Server : public QTcpServer
{
private:
    Q_OBJECT
    Server operator=(Server & forAssign) = delete;
    QTcpSocket *m_socket;
public:
    explicit Server(int iServerPort, QObject *parent = nullptr);
    ~Server();
    void incomingConnection(qintptr handle) override;
public slots:
    void onReadyRead();
    void onDisconnected();
};

#endif // SERVER_H
