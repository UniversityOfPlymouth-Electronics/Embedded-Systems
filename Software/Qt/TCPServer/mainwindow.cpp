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
        ui->listenButton->setText("&LISTEN");

        if (tcpServerConnection != nullptr) {
            if (tcpServerConnection->isOpen()) {
                ui->payload->appendPlainText(tr("Closing server connection"));
                tcpServerConnection->close();
            }
        }
        if (tcpServer.isListening()) {
            ui->payload->appendPlainText(tr("Closing server"));
            tcpServer.close();
        }
        serverIsListening = false;
    }
}

void MainWindow::acceptConnection()
{
    tcpServerConnection = tcpServer.nextPendingConnection();
    if (!tcpServerConnection) {
        ui->payload->appendPlainText(tr("Error: got invalid pending connection!"));
        return;
    }

    connect(tcpServerConnection, &QIODevice::readyRead, this, &MainWindow::updateServerProgress);
    connect(tcpServerConnection, &QAbstractSocket::errorOccurred,this, &MainWindow::displayError);
    connect(tcpServerConnection, &QTcpSocket::disconnected, tcpServerConnection, &QTcpSocket::deleteLater);

    ui->payload->appendPlainText(tr("Accepted connection"));
    //tcpServer.close();
}

void MainWindow::updateServerProgress()
{
    unsigned bytesThisTransaction = int(tcpServerConnection->bytesAvailable());
    bytesReceived += bytesThisTransaction;
    QByteArray bytes = tcpServerConnection->readAll();

    ui->payload->appendPlainText(tr("Received %1 Bytes, total %2").arg(bytesReceived).arg(bytesThisTransaction));
    for (unsigned n=0; n<bytesThisTransaction; n++) {
        ui->payload->appendPlainText(tr("%1").arg(bytes[n]));
        std::cout << bytes[n];
    }
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    if (socketError == QTcpSocket::RemoteHostClosedError) {
        ui->payload->appendPlainText(tr("Remote Host Closed"));
        return;
    }
    tcpServer.close();
    ui->payload->appendPlainText(tr("Server ready"));
    ui->listenButton->setEnabled(true);
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif
}
