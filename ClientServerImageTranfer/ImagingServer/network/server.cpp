#include "server.h"

Server::Server(int iServerPort, QObject *parent) :  QTcpServer(parent)
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
}

void Server::incomingConnection(qintptr handle)
{
    m_socket = new QTcpSocket();
    m_socket->setSocketDescriptor(handle);
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()), Qt::DirectConnection);
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()), Qt::DirectConnection);
    connect(m_socket, SIGNAL(disconnected()), m_socket, SLOT(deleteLater()), Qt::DirectConnection);
}

void Server::onReadyRead()
{
    size_t imageSize = *(reinterpret_cast<size_t *>(m_socket->read(4).data()));
    qDebug() << "image size" << imageSize;
    QString format(m_socket->read(20));
    qDebug() << "Image Format" << format;
    while(m_socket->bytesAvailable() < imageSize){
        if (!m_socket->waitForReadyRead() || !m_socket->isOpen()) {
            LogManager::error(m_socket->errorString());
            LogManager::error("read from socket interrepted");
            break ;
        }
    }
    QByteArray imageData =  m_socket->read(imageSize);
    qDebug() << "DATA size" << imageData.size();
    QPixmap image;
    image.loadFromData(imageData,format.toStdString().c_str());
    emit sendImage(image);
    bool result = false;
    m_socket->write(reinterpret_cast<char *>(&result),1);
}

void Server::onDisconnected()
{
    m_socket->close();
}
