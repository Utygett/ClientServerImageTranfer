#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include "network/tcptransferdata.h"
#include "utils/logmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_bt_sendImage_clicked();
    void on_bt_exit_clicked();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
