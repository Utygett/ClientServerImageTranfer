#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Server *server = new Server(55555);
    connect(server, &Server::sendImage, this, &MainWindow::slotImageRecieve);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotImageRecieve(const QPixmap &image)
{
    ui->label->setPixmap(image);
}
