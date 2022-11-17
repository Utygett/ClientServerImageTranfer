#include "server.h"

Server::Server( int iServerPort, QObject *parent) :  QTcpServer(parent)
{
    if(listen(QHostAddress::Any,(iServerPort))){
        LogManager::message(QString("Server start listening on port: ") + std::to_string(iServerPort).c_str());
    }
    else {
        LogManager::fatal("Error while server starting, check the server port.");
        exit(1);
    }
}

Server::~Server()
{
    qDebug() << "Server DELETE";
}

void Server::incomingConnection(qintptr handle)
{
    m_socket = new QTcpSocket();
    m_socket->setSocketDescriptor(handle);
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()), Qt::DirectConnection);
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()), Qt::DirectConnection);
}

void Server::onReadyRead()
{

}

void Server::onDisconnected()
{
    m_socket->close();
    delete m_socket;
}
