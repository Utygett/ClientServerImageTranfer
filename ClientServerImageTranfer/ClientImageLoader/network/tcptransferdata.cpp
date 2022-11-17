#include "TCPTransferData.h"

TCPTransferData::TCPTransferData()
{
    m_tranferStatus = false;
}

bool TCPTransferData::send(const QByteArray& data, const QString& imageType)
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    m_socket.connectToHost(QHostAddress(settings.value("serverIp","127.0.0.1").toString()), settings.value("serverPort", 55555).toInt());
    connect(&m_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    if(!m_socket.isOpen())
    {
        LogManager::error(m_socket.errorString());
        return false;
    }
    size_t dataSize = data.size();
    char strImageType[IMAGE_TYPE_SIZE];
    strImageType[0] = '\0';
    if(imageType.size() > IMAGE_TYPE_SIZE - 1)
    {
        LogManager::error(imageType + " wrong image type");
        return false;
    }
    m_socket.write(reinterpret_cast<char *>(&dataSize), 4);
    m_socket.write(strImageType, 10);
    m_socket.write(reinterpret_cast<const char *>(data.data()), dataSize);
    strncpy_s(strImageType, IMAGE_TYPE_SIZE,imageType.toStdString().c_str(), IMAGE_TYPE_SIZE);
    QEventLoop eventLoop;
    connect(this, SIGNAL(sendFinishQuery()), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    return m_tranferStatus;
}

void TCPTransferData::onReadyRead()
{
    QByteArray response = m_socket.read(1);
    bool* pResult = reinterpret_cast<bool *>(response.data());
    m_tranferStatus = pResult;
    emit sendFinishQuery();
}

