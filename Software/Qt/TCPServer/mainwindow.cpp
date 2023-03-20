#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QIntValidator>
#include <QTcpSocket>
#include <QMessageBox>
#include <iostream>

//Main window (there is only one)
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->port->setValidator(new QIntValidator(0,65536,this));
    ui->payload->setPlainText("Hello World!");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ********************************* SERVER *********************************
void MainWindow::on_listenButton_clicked()
{
    ui->payload->appendPlainText(tr("======>> on_listenButton_clicked() ======="));

    bytesReceived = 0;

    if (serverIsListening == false) {
        ui->listenButton->setText("&STOP");
        connect(&tcpServer, &QTcpServer::newConnection, this, &MainWindow::acceptConnection);

        while (!tcpServer.listen()) {
            QMessageBox::StandardButton ret = QMessageBox::critical(this,tr("Loopback"),
                                                                    tr("Unable to start the test: %1.").arg(tcpServer.errorString()),
                                                                    QMessageBox::Retry | QMessageBox::Cancel);
            if (ret == QMessageBox::Cancel)
                return;
        }

        ui->payload->appendPlainText(tr("Listening on port %1").arg(tcpServer.serverPort()));
        serverIsListening = true;
    } else {
        tearDown();
    }
    ui->payload->appendPlainText(tr("======<< on_listenButton_clicked() ======="));
}

void MainWindow::acceptConnection()
{
    ui->payload->appendPlainText(tr("======>> acceptConnection() ======="));
    tcpServerConnection = tcpServer.nextPendingConnection();
    if (!tcpServerConnection) {
        tearDown();
        return;
    }

    //Hook up signals
    connect(tcpServerConnection, &QIODevice::readyRead, this, &MainWindow::updateServerProgress);
    connect(tcpServerConnection, &QAbstractSocket::errorOccurred,this, &MainWindow::displayError);
    connect(tcpServerConnection, &QTcpSocket::disconnected, tcpServerConnection, &QTcpSocket::deleteLater);

    ui->payload->appendPlainText(tr("Accepted connection"));
    //tcpServer.close();
    ui->payload->appendPlainText(tr("======<< acceptConnection() ======="));

}



void MainWindow::updateServerProgress()
{
    ui->payload->appendPlainText(tr("======>> updateServerProgress() ======="));
    unsigned bytesThisTransaction = int(tcpServerConnection->bytesAvailable());
    bytesReceived += bytesThisTransaction;
    QByteArray bytes = tcpServerConnection->readAll();

    ui->payload->appendPlainText(tr("Received %1 Bytes, total %2").arg(bytesReceived).arg(bytesThisTransaction));
    for (unsigned n=0; n<bytesThisTransaction; n++) {
        ui->payload->appendPlainText(tr("%1").arg(bytes[n]));
        std::cout << bytes[n];
    }
    ui->payload->appendPlainText(tr("======<< updateServerProgress() ======="));
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    ui->payload->appendPlainText(tr("======>> displayError() ======="));

    tearDown();

    if (socketError == QTcpSocket::RemoteHostClosedError) {
        ui->payload->appendPlainText(tr("Remote Host Closed"));
    }

#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif
    ui->payload->appendPlainText(tr("======<< displayError() ======="));

}

void MainWindow::tearDown()
{
    disconnect(&tcpServer, nullptr, nullptr, nullptr);

    if (tcpServerConnection) {
        disconnect(tcpServerConnection, nullptr, nullptr, nullptr);
        disconnect(tcpServerConnection, nullptr, nullptr, nullptr);
        disconnect(tcpServerConnection, nullptr, nullptr, nullptr);

        if (tcpServerConnection->isOpen()) {
            tcpServerConnection->close();
            ui->payload->appendPlainText(tr("Server connection closed"));
        }
    }
    if (tcpServer.isListening()) {
        tcpServer.close();
        ui->payload->appendPlainText(tr("Server closed"));
    }
    ui->listenButton->setEnabled(true);
    ui->listenButton->setText("&LISTEN");
    serverIsListening = false;
}
