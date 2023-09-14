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
    ui->port->setValidator(new QIntValidator(0,65536,this));
    ui->payload->setPlainText("Hello World!");
    qDebug() << "Server Started";
}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug() << "Server Destroyed";
}

// Button slot
void MainWindow::on_listenButton_clicked()
{
    ui->textLog->appendPlainText(tr("======>> on_listenButton_clicked() ======="));

    bytesReceived = 0;

    if (serverIsListening == false) {
        ui->listenButton->setText("&STOP");

        //Set port
        bool parsedAsInt = false;
        quint16 port = ui->port->text().toUInt(&parsedAsInt);
        if (parsedAsInt == true) {
            qInfo() << "Setting port to " << port;
            ui->textLog->appendPlainText(tr("Setting port to %1").arg(port));
        } else {
            qWarning() << "Cannot read port value: using server assigned.";
            ui->textLog->appendPlainText(tr("Cannot read port value: using server assigned."));
            port = 0;
        }

        //Hook up signals and slots for the server events
        connect(&tcpServer, &QTcpServer::newConnection, this, &MainWindow::acceptConnection);
        connect(&tcpServer, &QTcpServer::pendingConnectionAvailable, this, &MainWindow::pendingConnection);
        connect(&tcpServer, &QTcpServer::acceptError, this, &MainWindow::acceptError);

        //Non-blocking call to put server into listening state
        while (!tcpServer.listen(QHostAddress::Any, port)) {
            QMessageBox::StandardButton ret = QMessageBox::critical(this,tr("Loopback"), tr("Unable to start the test: %1.").arg(tcpServer.errorString()), QMessageBox::Retry | QMessageBox::Cancel);
            if (ret == QMessageBox::Cancel)
                return;
        }

        qInfo() << "Listening on port " << tcpServer.serverPort();
        ui->textLog->appendPlainText(tr("Listening on port %1").arg(tcpServer.serverPort()));
        serverIsListening = true;
    } else {
        //User clicked the disconnect button
        tearDown();
    }
    qDebug() << "======<< on_listenButton_clicked() =======";
    ui->textLog->appendPlainText(tr("======<< on_listenButton_clicked() ======="));
}

// slot for pendingConnectionAvailable signal
void MainWindow::pendingConnection() {
    qInfo() << "====== PENDING CONNECTION SIGNAL AVAILABLE =======";
    ui->textLog->appendPlainText(tr("====== PENDING CONNECTION SIGNAL AVAILABLE ======="));
}

//slot for newConnection signal
void MainWindow::acceptConnection()
{
    qInfo() << "======>> acceptConnection() =======";
    ui->textLog->appendPlainText(tr("======>> acceptConnection() ======="));

    //Get the TCP/IP socket (type QTcpSocket)
    tcpServerConnection = tcpServer.nextPendingConnection();
    if (!tcpServerConnection) {
        qWarning() << "======<< FAILED: acceptConnection() " << tcpServer.errorString() << "=======";
        ui->textLog->appendPlainText(tr("======<< FAILED: acceptConnection() %s =======").arg(tcpServer.errorString()));
        tearDown();
        return;
    }

    //Hook up signals and slots for TCP/IP socket
    connect(tcpServerConnection, &QIODevice::readyRead, this, &MainWindow::updateServerProgress);
    connect(tcpServerConnection, &QAbstractSocket::errorOccurred,this, &MainWindow::displayError);
    connect(tcpServerConnection, &QTcpSocket::disconnected, tcpServerConnection, &QTcpSocket::deleteLater);

    ui->textLog->appendPlainText(tr("======<< acceptConnection() ======="));
    qInfo() << "======<< acceptConnection() =======";
}

// slot for case where accept did not succeed.
void MainWindow::acceptError(QAbstractSocket::SocketError err)
{
    qWarning() << "====== ACCEPT ERROR =======";
    qWarning() << err << " " << tcpServer.errorString();
    ui->textLog->appendPlainText(tr("====== ACCEPT ERROR ======="));
    ui->textLog->appendPlainText(tr("%1 %2").arg(err).arg(tcpServer.errorString()));
}

// slot for handling incoming data
void MainWindow::updateServerProgress()
{
    qInfo() << "======>> updateServerProgress() =======";
    ui->textLog->appendPlainText(tr("======>> updateServerProgress() ======="));
    unsigned bytesThisTransaction = int(tcpServerConnection->bytesAvailable());
    bytesReceived += bytesThisTransaction;
    QByteArray bytes = tcpServerConnection->readAll();

    qInfo() << "Received " << bytesReceived << ", total " << bytesThisTransaction;
    ui->textLog->appendPlainText(tr("Received %1 Bytes, total %2").arg(bytesReceived).arg(bytesThisTransaction));

    //Append received data to the textbox
    QString qStrPayload = QString::fromUtf8(bytes);
    ui->payload->appendPlainText(qStrPayload);
    qInfo() << "+" << qStrPayload;

    //Respond and close
    const char* strACK = "ACK";
    tcpServerConnection->write(strACK, 3);
    tcpServerConnection->close();

    //Logging
    ui->textLog->appendPlainText(tr("======<< updateServerProgress() ======="));
    qInfo() << "======<< updateServerProgress() =======";
}

// slot for error handling, including the remote host closing
void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    qInfo() << "======>> displayError() =======";
    qWarning() << tcpServer.errorString();
    ui->textLog->appendPlainText(tr("======>> displayError() ======="));
    ui->textLog->appendPlainText(tr("displayError: %1").arg(tcpServer.errorString()));

    if (socketError == QTcpSocket::RemoteHostClosedError) {
        qInfo() << "Remote Host Closed";
        ui->textLog->appendPlainText(tr("Remote Host Closed"));
        tearDownTCPSocket();
        return;
    }

    //For all other errors, tear down everything
    tearDown();

#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif
    ui->textLog->appendPlainText(tr("======<< displayError() ======="));

}

void MainWindow::tearDownTCPSocket()
{
    //Close current TCP connection (there is only one in this application)
    if (tcpServerConnection) {
        if (tcpServerConnection->isOpen()) {
            disconnect(tcpServerConnection, nullptr, nullptr, nullptr);
            tcpServerConnection->close();
            tcpServerConnection = nullptr; //IMPORTANT!
            qInfo() << "Server connection closed";
            ui->textLog->appendPlainText(tr("Server connection closed"));
        }
    }
}
void MainWindow::tearDown()
{
    tearDownTCPSocket();

    //Stop the server from accepting incoming connections
    if (tcpServer.isListening()) {
        tcpServer.close();
        qInfo() << "Server closed";
        ui->textLog->appendPlainText(tr("Server closed"));
    }
    //Disconnect signals from slots
    disconnect(&tcpServer, nullptr, nullptr, nullptr);

    //Update UI
    ui->listenButton->setEnabled(true);
    ui->listenButton->setText("&LISTEN");
    serverIsListening = false;
}
