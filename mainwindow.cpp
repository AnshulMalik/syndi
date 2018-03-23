#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "samba/source3/include/libsmbclient.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
//    SMBCCTX *context;
    delete ui;
//    context = smbc_new_context();
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
