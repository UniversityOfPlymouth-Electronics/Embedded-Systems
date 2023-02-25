#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QIntValidator>
#include <QTcpSocket>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QIntValidator* v = new QIntValidator(0,255,this);
    ui->ip1->setValidator(v);
    ui->ip2->setValidator(v);
    ui->ip3->setValidator(v);
    ui->ip4->setValidator(v);
    ui->port->setValidator(new QIntValidator(0,65536,this));
    ui->payload->setPlainText("Hello World!");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ********************************* CLIENT *********************************
void MainWindow::on_sendButton_clicked()
{
    if (clientIsSending == false) {
        ui->listenButton->setEnabled(false);
        ui->sendButton->setEnabled(false);
        clientIsSending = true;
        connect(&tcpClient, &QAbstractSocket::connected, this, &MainWindow::startTransfer);
        connect(&tcpClient, &QIODevice::bytesWritten, this, &MainWindow::updateClientProgress);
        connect(&tcpClient, &QAbstractSocket::errorOccurred, this, &MainWindow::displayError);

        bool parsedAsInt = false;
        quint16 port = ui->port->text().toUInt(&parsedAsInt);
        if (parsedAsInt == true) {
            ui->payload->appendPlainText(tr("Connecting"));
            tcpClient.connectToHost(QHostAddress::LocalHost, port);
        } else {
            ui->payload->appendPlainText(tr("Please provide a valid port value"));
        }

    }
}
void MainWindow::startTransfer()
{
    // called when the TCP client connected to the loopback server
//    QString strData = ui->payload->toPlainText();
    QByteArray dat = QByteArray("Hello World");

    bytesToWrite = dat.size() - int(tcpClient.write(dat,dat.size()));
    ui->payload->appendPlainText(tr("Client Connected"));
}
void MainWindow::updateClientProgress(qint64 numBytes)
{
    // called when the TCP client has written some bytes
    bytesWritten += int(numBytes);

    // only write more if not finished and when the Qt write buffer is below a certain size.

//    if (bytesToWrite > 0 && tcpClient.bytesToWrite() <= 4 * PayloadSize)
//        bytesToWrite -= tcpClient.write(QByteArray(qMin(bytesToWrite, PayloadSize), '@'));

    auto b2w = tcpClient.bytesToWrite();
    ui->payload->appendPlainText(tr("numBytes: %1").arg(numBytes));
    ui->payload->appendPlainText(tr("bytesWritten: %1").arg(bytesWritten));
    ui->payload->appendPlainText(tr("tcpClient.bytesToWrite(): %1").arg(b2w));
    if (b2w == 0) {
        ui->listenButton->setEnabled(true);
        ui->sendButton->setEnabled(true);
        clientIsSending = false;
        tcpClient.close();
        ui->payload->appendPlainText(tr("Client Disconnected"));
    }
}
// ********************************* SERVER *********************************
void MainWindow::on_listenButton_clicked()
{
    bytesWritten = 0;
    bytesReceived = 0;

    if (serverIsListening == false) {
        ui->sendButton->setEnabled(false);
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
    int bytesThisTransaction = int(tcpServerConnection->bytesAvailable());
    bytesReceived += bytesThisTransaction;
    QByteArray bytes = tcpServerConnection->readAll();

    ui->payload->appendPlainText(tr("Received %1 Bytes, total %2").arg(bytesReceived).arg(bytesThisTransaction));
    for (unsigned n=0; n<bytesThisTransaction; n++) {
        ui->payload->appendPlainText(tr("%1").arg(bytes[n]));
        std::cout << bytes[n];
    }
}


// ********************************* COMMON *********************************
void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    if (socketError == QTcpSocket::RemoteHostClosedError) {
        ui->payload->appendPlainText(tr("Remote Host Closed"));
        return;
    }

    QMessageBox::information(this, tr("Network error"),
                             tr("The following error occurred: %1.")
                             .arg(tcpClient.errorString()));

    tcpClient.close();
    tcpServer.close();
    ui->payload->appendPlainText(tr("Client ready"));
    ui->payload->appendPlainText(tr("Server ready"));
    ui->sendButton->setEnabled(true);
    ui->listenButton->setEnabled(true);
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif
}
