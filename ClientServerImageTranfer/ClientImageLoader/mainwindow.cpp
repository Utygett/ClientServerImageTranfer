#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotAppendMessageOnBoard(const QString &message)
{
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    ui->tb_mainBoard->append(currentTime + message);
}

void MainWindow::on_bt_sendImage_clicked()
{
    //Get file name
    QString strFilter;
    QString imageFileName = QFileDialog::getOpenFileName(0,
                                    "Отправить изображение",
                                    "C:\\emploerPhoto\\Photo",
                                    "*.jpg ;; *.png ;; *.bmp",
                                    &strFilter
                                    );
    qDebug() << "Filter: " << strFilter << imageFileName;
    //check the file is image
    QPixmap image(imageFileName);
    if(image.isNull())
    {
        QString message(imageFileName + " не удалось отправить изображение, файл поврежден.");
        slotAppendMessageOnBoard(message);
        LogManager::error(message);
        return ;
    }
    //Open file
    QFile imageFile(imageFileName);
    imageFile.open(QIODevice::ReadOnly);
    QByteArray rawImage = imageFile.readAll();
    imageFile.close();
    //Send to Server
    TCPTransferData imageSender;
    if(imageSender.send(rawImage, strFilter.remove("*.")))
    {
        QString message(imageFileName + " изображение успешно отправлено.");
        slotAppendMessageOnBoard(message);
        LogManager::message(message);
    }
    else {
        QString message(imageFileName + " не удалось отправить изображение, ошибка на сервере.");
        slotAppendMessageOnBoard(message);
        LogManager::message(message);
    }
    //GetResultFromServer
    //
}

void MainWindow::on_bt_exit_clicked()
{
    //Exit
}
