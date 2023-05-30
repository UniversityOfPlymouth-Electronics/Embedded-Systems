#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QIntValidator>
#include <QTcpSocket>
#include <QMessageBox>
#include <iostream>
#include <QDebug>

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
    qDebug() << "Client Started";
}

MainWindow::~MainWindow()
{
    qDebug() << "Main Destructor";
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
            qDebug() << "Connecting";
            tcpClient.connectToHost(QHostAddress::LocalHost, port);
        } else {
            qWarning() << "Please provide a valid port value";
            ui->payload->appendPlainText(tr("Please provide a valid port value"));
        }

    }
}

void MainWindow::startTransfer()
{
    // called when the TCP client connected to the loopback server
    QString strData = ui->payload->toPlainText();
    QByteArray dat = QByteArray(strData.toUtf8());

    bytesToWrite = dat.size() - int(tcpClient.write(dat,dat.size()));
    qInfo() << "Client Connected";
}

void MainWindow::updateClientProgress(qint64 numBytes)
{
    // called when the TCP client has written some bytes
    bytesWritten += int(numBytes);

    auto b2w = tcpClient.bytesToWrite();
    qInfo() << "numBytes: " << numBytes;
    qInfo() << "bytesWritten: " << bytesWritten;
    qInfo() << "tcpClient.bytesToWrite: " << b2w;
    if (b2w == 0) {
        qInfo() << "Completed";
        tearDown();
    }
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    ui->payload->appendPlainText(tr("Error: %1").arg(tcpClient.errorString()));
    if (socketError == QTcpSocket::RemoteHostClosedError) {
        qInfo() << "Remote Host Closed";
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
    qInfo() << "Client Closed";
}
