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

void MainWindow::on_bt_sendImage_clicked()
{
    //Get file name
    QString strFilter;
    QString imageFileName = QFileDialog::getOpenFileName(0,
                                    "Отправить изображение",
                                    "C:\\",
                                    "*.png ;; *.jpg ;; *.bmp",
                                    &strFilter
                                    );
    qDebug() << "Filter: " << strFilter << imageFileName;
    //check the file is image

    //Open file

    QFile imageFile(imageFileName);
    imageFile.open(QIODevice::ReadOnly);
    QByteArray rawImage = imageFile.readAll();
    imageFile.close();
    //Send to Server
    TCPTransferData imageSender;
    if(imageSender.send(rawImage, strFilter))
    {
        qDebug() << "SUCCESS send message";
    }
    else {

        qDebug() << "ERROR send message";
    }
    //GetResultFromServer
    //
}

void MainWindow::on_bt_exit_clicked()
{
    //Exit
}
