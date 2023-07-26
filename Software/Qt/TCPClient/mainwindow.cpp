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
    ui->textLog->appendPlainText("Client Started");
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

        //The call back to read a response
        connect(&tcpClient, &QIODevice::readyRead, this, &MainWindow::updateResponseProgress);
        bool parsedAsInt = false;
        quint16 port = ui->port->text().toUInt(&parsedAsInt);
        QString ipAddress = ui->ip1->text() + "." + ui->ip2->text() + "." + ui->ip3->text() + "." + ui->ip4->text();
        QHostAddress targetDeviceIP = QHostAddress(ipAddress);
        if (parsedAsInt == true) {
            qDebug() << "Connecting";
            ui->textLog->appendPlainText(tr("Connecting to %1 : %2").arg(ipAddress).arg(port));
            tcpClient.connectToHost(targetDeviceIP, port);
        } else {
            qWarning() << "Please provide a valid port value";
            ui->textLog->appendPlainText("Please provide a valid port value");
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
    ui->textLog->appendPlainText("Client Connected");
}

void MainWindow::updateClientProgress(qint64 numBytes)
{
    // called when the TCP client has written some bytes
    bytesWritten += int(numBytes);

    auto b2w = tcpClient.bytesToWrite();
    ui->textLog->appendPlainText(tr("numBytes: %1").arg(numBytes));
    ui->textLog->appendPlainText(tr("bytesWritten: %1").arg(bytesWritten));
    ui->textLog->appendPlainText(tr("tcpClient.bytesToWrite(): %1").arg(b2w));
    qInfo() << "numBytes: " << numBytes;
    qInfo() << "bytesWritten: " << bytesWritten;
    qInfo() << "tcpClient.bytesToWrite: " << b2w;

    if (b2w == 0) {
        ui->textLog->appendPlainText("Completed");
        qInfo() << "Completed";
        tcpClient.readAll();
        //tearDown(); //Premature if waiting for a response
    }
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    ui->textLog->appendPlainText(tr("Error: %1").arg(tcpClient.errorString()));
    qWarning() << "Error: " << tcpClient.errorString();

    if (socketError == QTcpSocket::RemoteHostClosedError) {
        ui->textLog->appendPlainText("Remote Host Closed");
        qInfo() << "Remote Host Closed";
    } else {
        QMessageBox::information(this, tr("Network error"), tr("The following error occurred: %1.").arg(tcpClient.errorString()));
        qWarning() << "Network Error: " << tcpClient.errorString();
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
    ui->textLog->appendPlainText("Client Closed");
}

// slot for handling incoming data
void MainWindow::updateResponseProgress()
{
    qInfo() << "======>> updateServerProgress() =======";
    ui->textLog->appendPlainText(tr("======>> updateServerProgress() ======="));
    unsigned bytesThisTransaction = int(tcpClient.bytesAvailable());
    bytesReceived += bytesThisTransaction;
    QByteArray bytes = tcpClient.readAll();

    qInfo() << "Received " << bytesReceived << ", total " << bytesThisTransaction;
    ui->textLog->appendPlainText(tr("Received %1 Bytes, total %2").arg(bytesReceived).arg(bytesThisTransaction));

    //Append received data to the textbox
    QString qStrPayload = QString::fromUtf8(bytes);
    ui->textLog->appendPlainText(qStrPayload);
    qInfo() << "Response: " << qStrPayload;

    tcpClient.close();

    //Logging
    ui->textLog->appendPlainText(tr("======<< updateServerProgress() ======="));
    qInfo() << "======<< updateServerProgress() =======";

    //Sent and received - all done - tear down
    tearDown();
}

