#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::showAliveHosts() {
    QList<QString> aliveHosts = Network::aliveHosts();

    foreach(QString host, aliveHosts) {
        ui->textEdit->append(host);
    }
}

void MainWindow::on_pushButton_clicked()
{
    showAliveHosts();
}
