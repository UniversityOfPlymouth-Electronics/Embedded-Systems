#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_listenButton_clicked();
    void acceptConnection();
    void pendingConnection();
    void acceptError(QAbstractSocket::SocketError err);

private:
    Ui::MainWindow *ui;
    void tearDown();
    void tearDownTCPSocket();

    //Server
    QTcpServer tcpServer;
    QTcpSocket *tcpServerConnection = nullptr;
    void updateServerProgress();
    void displayError(QAbstractSocket::SocketError socketError);
    int bytesReceived = 0;
    bool serverIsListening = false;

};
#endif // MAINWINDOW_H
