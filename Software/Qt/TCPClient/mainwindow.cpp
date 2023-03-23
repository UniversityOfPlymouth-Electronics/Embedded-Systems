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
        ui->payload->appendPlainText(tr("Completed"));
        tearDown();
    }
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    ui->payload->appendPlainText(tr("Error: %1").arg(tcpClient.errorString()));
    if (socketError == QTcpSocket::RemoteHostClosedError) {
        ui->payload->appendPlainText(tr("Remote Host Closed"));
    } else {
        QMessageBox::information(this, tr("Network error"), tr("The following error occurred: %1.").arg(tcpClient.errorString()));
    }
    tearDown();
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif
}


void MainWindow::tearDown()
{
    ui->sendButton->setEnabled(true);
    clientIsSending = false;
    disconnect(&tcpClient, nullptr, nullptr, nullptr);
    disconnect(&tcpClient, nullptr, nullptr, nullptr);
    disconnect(&tcpClient, nullptr, nullptr, nullptr);
    if (tcpClient.isOpen()) {
        tcpClient.close();
    }
    ui->payload->appendPlainText(tr("Client Closed"));
}
