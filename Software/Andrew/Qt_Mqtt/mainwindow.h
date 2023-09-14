
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include "qcustomplot.h"
//#include <QMqttClient>
//#include <QtSerialPort/QSerialPortInfo>
//#include <QtSerialPort/QSerialPort>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addpoint(qint64 timestamp, double x, double y);
    void plot();
    void clear();

    int data_points=0;

    typedef enum{
        PLOT_SOURCE_SERIAL,PLOT_SOURCE_MQTT
    }plot_source_t;


    plot_source_t getPlotSource();

    void setPlotSource(plot_source_t);

    plot_source_t plot_source;

    QSharedPointer<QCPAxisTicker> original_axis_p;
    QSharedPointer<QCPAxisTickerDateTime> time_axis_p;

    void add_to_log(QString str);

private slots:
    void serialRec();

    void on_connect_button_clicked();

    void on_actionSave_triggered();

    void on_mqtt_connect_button_clicked();

    void on_publish_button_clicked();

    void on_sub_button_clicked();

    void on_actionSerial_triggered();

    void on_actionMQTT_Broker_triggered();

    void on_unsub_button_clicked();

    void on_plot_scrollbar_valueChanged(int value);

    void mqtt_status_changed();

    void on_actionClear_Data_triggered();

private:
    Ui::MainWindow *ui;
    QVector<double> qv_x, qv_y,qv_t;
    QVector<qint64> qv_tms;
    QString serialInData;
    QVector<QString> subscribed_topics;
   // QMqttClient m_client;
};

#endif // MAINWINDOW_H
