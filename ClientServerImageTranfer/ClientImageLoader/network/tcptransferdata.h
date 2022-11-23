#ifndef URLPOSTSENDER_H
#define URLPOSTSENDER_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QSettings>
#include <QEventLoop>
#include "../../utils/logmanager.h"

class TCPTransferData : public QObject
{
private:
    enum{IMAGE_TYPE_SIZE = 20};
    Q_OBJECT
    QTcpSocket  m_socket;
    bool m_tranferStatus;
public:
    TCPTransferData();
    bool send(const QByteArray& data, const QString& imageType);
public slots:
    void onReadyRead();
signals:
    void sendFinishQuery();
};

#endif // URLPOSTSENDER_H
