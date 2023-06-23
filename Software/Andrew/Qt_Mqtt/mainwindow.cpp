
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMqttClient>
#include <QWidget>
#include <QHostInfo>



QMqttClient* m_client;
QSerialPort serial;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){

    /***** Set up Plot Area *****/
    ui->setupUi(this);
    ui->plot_3->addGraph();
    ui->plot_3->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot_3->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plot_3->xAxis->rescale();
    ui->plot_3->yAxis->setRange(0.0,1.0);

    // Time and date labels
    original_axis_p = QSharedPointer<QCPAxisTicker>(new QCPAxisTicker);
    time_axis_p = QSharedPointer<QCPAxisTickerDateTime>(new QCPAxisTickerDateTime);
    time_axis_p->setDateTimeFormat("hh:mm:ss");

    if(ui->actionUse_Timestamp->isChecked()){
       ui->plot_3->xAxis->setTickLabelRotation(90);
       ui->plot_3->xAxis->setTicker(time_axis_p);
    }
    else{
       ui->plot_3->xAxis->setTickLabelRotation(0);
       ui->plot_3->xAxis->setTicker(original_axis_p);
    }

    // Plot area scrollbar
    connect(ui->plot_scrollbar,SIGNAL(valueChanged(int)),this,SLOT(on_plot_scrollbar_valueChanged(int)));
    ui->plot_scrollbar->setRange(0, 1000);
    ui->plot_3->replot();
    ui->plot_3->update();

    ui->plot_scrollbar->setValue(1000);

    /***** Set up Serial options *****/
    // Ports
    QSerialPortInfo info;
    QList<QSerialPortInfo> ports = info.availablePorts();
    QList<QString> stringPorts;
    for(int i = 0 ; i < ports.size(); i++){
       stringPorts.append(ports.at(i).portName());
    }
    ui->com_port_combo->addItems(stringPorts);

    // Baud Rates
    QList<qint32> baudRates = info.standardBaudRates(); // What baudrates does my computer support ?
    QList<QString> stringBaudRates;
    for(int i = 0 ; i < baudRates.size() ; i++){
        stringBaudRates.append(QString::number(baudRates.at(i)));
    }
    ui->baud_combo->addItems(stringBaudRates);

    //Setup MQTT options
    //QOS
    QList<QString> qos_strs;
    for(int i=0;i<3;i++){
        qos_strs.append(QString::number(i));
    }
    ui->qos_combo->addItems(qos_strs);
    ui->qos_combo->setCurrentIndex(0);
    ui->sub_qos_combo->addItems(qos_strs);
    ui->sub_qos_combo->setCurrentIndex(0);

    QList<QString> retained_strs;
    retained_strs.append("Yes");
    retained_strs.append("No");

    ui->retained_combo->addItems(retained_strs);
    ui->retained_combo->setCurrentIndex(1);

    //Host
    ui->ip_field->setText("192.168.11.245");
    ui->prt_field->setText("1883");

    // Setup other MQTT variables
    m_client = new QMqttClient(this);

    // Subscription callback
    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
        if(MainWindow::getPlotSource()==PLOT_SOURCE_MQTT && (!ui->actionPause_Sampling->isChecked())){
            QString content = QDateTime::currentDateTime().toString()
                                    + QLatin1String(" Received Topic: ")
                                    + topic.name()
                                    + QLatin1String(" Message: ")
                                    + message
                                    + QLatin1Char('\n');

            QStringList s_list = topic.levels();
            QString qst="";
            for (int i=0;i<topic.levelCount();i++){
                qst = qst + QString(s_list[i]) +"\r\n";
            }
            content = content + qst;
            add_to_log(content);

            QString qs = message;
            double d = qs.toDouble();
            qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
            addpoint(timestamp,data_points,d);
            data_points++;
        }

    });

    //Delete this!
    ui->username_field->setText("subscriber1");
    ui->clientID_field->setText("subscriber1");
    ui->password_field->setText("1234");
    ui->sub_topic_field->setText("f429");

    ui->MQTT_widget->setEnabled(false);
    ui->Serial_widget->setEnabled(true);
    ui->MQTT_widget->hide();
    ui->Serial_widget->show();

    MainWindow::setPlotSource(PLOT_SOURCE_SERIAL);

    connect(m_client, &QMqttClient::stateChanged, this, &MainWindow::mqtt_status_changed);


}

MainWindow::~MainWindow(){
    delete ui;
    delete m_client;
    serial.close();
}

/***** Function to add a new point on the plot *****/
void MainWindow::addpoint(qint64 timestamp, double x, double y){

   // QDateTime tim = QDateTime::fromMSecsSinceEpoch(timestamp);
    if(!ui->actionPause_Sampling->isChecked()){
        qv_tms.append(timestamp);
        qv_t.append(timestamp/1000);
        qv_x.append(x);
        qv_y.append(y);
        if(!ui->actionPause_Plot->isChecked()){
            plot();
        }
    }
}

/***** Function to update the plot area *****/
void MainWindow::plot(){
    if(ui->actionUse_Timestamp->isChecked()){
        ui->plot_3->xAxis->setTickLabelRotation(90);
        ui->plot_3->xAxis->setTicker(time_axis_p);
        ui->plot_3->graph(0)->setData(qv_t,qv_y);
    }
    else{
        ui->plot_3->xAxis->setTickLabelRotation(0);
        ui->plot_3->xAxis->setTicker(original_axis_p);
        ui->plot_3->graph(0)->setData(qv_x,qv_y);
    }

    if(ui->plot_scrollbar->value()>980){
        if(qv_x.size()>0){
            int pos,size;

            if(qv_x.size()<=12){
                if(ui->actionUse_Timestamp->isChecked()){
                    pos = qv_t[qv_t.size()-1];
                    size = qv_t[qv_t.size()-1]- qv_t[0];
                }
                else{
                    pos=12;
                    size=12;
                }
            }
            else{
                if(ui->actionUse_Timestamp->isChecked()){
                    pos = qv_t[qv_t.size()-1];
                    size = qv_t[qv_t.size()-1]-qv_t[qv_t.size()-12];
                }
                else{
                    pos = qv_x[qv_x.size()-1];
                    size = qv_x[qv_x.size()-1]-qv_x[qv_x.size()-12];
                }
            }
            ui->plot_3->xAxis->setRange(pos,size,Qt::AlignRight);
        }
    }


    ui->plot_3->replot();
    ui->plot_3->update();
}
/***** Function to clear the plot data *****/
void MainWindow::clear(){
    qv_x.clear();
    qv_y.clear();
    qv_t.clear();
    qv_tms.clear();
    data_points=0;
    plot();
}

/***** Serial rx callback *****/
void MainWindow::serialRec(){
    if(MainWindow::getPlotSource() == PLOT_SOURCE_SERIAL){
        QString qs = serial.readAll();
        if(!ui->actionPause_Sampling->isChecked()){
            add_to_log(qs + "\r\n");
            double d = qs.toDouble();
            qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
            addpoint(timestamp,data_points,d);
            data_points++;
        }
    }
}

/***** Connect button Slot *****/
void MainWindow::on_connect_button_clicked(){
    if(!serial.isOpen()){
        add_to_log("Opening Serial Port\r\n");
        QSerialPortInfo info;

        QString portstr = info.availablePorts().at(ui->com_port_combo->currentIndex()).portName();
        serial.setPortName(portstr);

        qint32 baud_int =info.standardBaudRates().at(ui->com_port_combo->currentIndex());

        serial.setBaudRate(baud_int);

        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::SoftwareControl);

        QElapsedTimer timer;
        timer.start();

        while((!serial.open(QIODevice::ReadWrite))&& (timer.nsecsElapsed()<10));

        add_to_log(serial.isOpen() ? "Serial Port Opened\r\n" : "Unable to open Serial Port\r\n");

        connect(&serial,SIGNAL(readyRead()),this,SLOT(serialRec()));
        serial.setDataTerminalReady(true);
        serial.waitForReadyRead();
    }
    else{
        add_to_log("Already Connected\r\n");
    }


    MainWindow::setPlotSource(PLOT_SOURCE_SERIAL);
}


/***** Save menu slot *****/
void MainWindow::on_actionSave_triggered(){
    QString file_name = QFileDialog::getSaveFileName(this,"Save as CSV",QDir::homePath(),"CSV (*.csv)");
    if(!file_name.contains(".csv")){
        file_name.append(".csv");
    }


    QFile file(file_name);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        for (int c=0; c < qv_x.size(); c++ )
            stream << qv_tms[c]<< "," << qv_x[c] << "," << qv_y[c]   << Qt::endl;
    }
    file.close();
}

/***** MQTT connect button slot *****/
void MainWindow::on_mqtt_connect_button_clicked()
{
    m_client->setHostname(ui->ip_field->text());

//    QHostInfo hinf;
//    hinf.setHostName("broker.hivemq.com");
//    m_client->setHostname(hinf.addresses()[0].toString());
//    QHostInfo::HostInfoError err;
//    err = hinf.error();

//    QList ls = hinf.addresses();

    //add_to_log(err==QHostInfo::HostInfoError::NoError ? ("Host lookup success. IP:" + ls[0].toString()) : ("Host lookup failed. Error:" + hinf.errorString()));

    //m_client->setHostname(hinf.hostName());

    m_client->setPort(ui->prt_field->text().toInt());
    m_client->setClientId(ui->clientID_field->text());
    m_client->setUsername(ui->username_field->text());
    m_client->setPassword(ui->password_field->text());
    m_client->connectToHost();
    //Now wait for the statechanged callback
}


/***** MQTT publish button slot *****/
void MainWindow::on_publish_button_clicked()
{
    if(m_client->state()!= QMqttClient::Connected){
        add_to_log("Could not publish, please reconnect and retry\r\n");
        return;
    }
    QString topic = ui->pub_topic_field->text();
    auto q = ui->qos_combo->currentIndex();
    bool ret =ui->retained_combo->currentIndex()==0 ? true : false;
    QByteArray payload = ui->payload_field->toPlainText().toUtf8();
    m_client->publish(QMqttTopicName(topic),payload, q, ret);
}


/***** MQTT subscribe button slott *****/
void MainWindow::on_sub_button_clicked()
{

    bool already_subed = false;
    for(int i=0;i<subscribed_topics.count();i++){
        if(subscribed_topics[i].compare(ui-> sub_topic_field->text())==0){
            already_subed = true;
        }
    }

    if(already_subed){
        add_to_log("Already subscribed to topic:" + ui->sub_topic_field->text() + "\r\n");
    }
    else{
        auto subscription = m_client->subscribe(ui-> sub_topic_field->text(),ui->sub_qos_combo->currentIndex());

        if (!subscription) {
            add_to_log("Could not subscribe. Is there a valid connection?\r\n");
            return;
        }
        else{
            subscribed_topics.append(ui-> sub_topic_field->text());
            add_to_log("Subscribed to " + ui-> sub_topic_field->text()+"\r\n");
            ui->subed_textb->clear();
            for(auto str : subscribed_topics){
                ui->subed_textb->insertPlainText(str +"\r\n");
            }
        }
    }
}


/***** MQTT connect button slot *****/
void MainWindow::on_actionSerial_triggered()
{
    ui->MQTT_widget->setEnabled(false);
    ui->Serial_widget->setEnabled(true);
    ui->MQTT_Vlayout->setEnabled(false);
    ui->Serial_Vlayout->setEnabled(true);
    ui->MQTT_widget->hide();
    ui->Serial_widget->show();
    MainWindow::setPlotSource(PLOT_SOURCE_SERIAL);
}

// Source menu MQTT selected slot
void MainWindow::on_actionMQTT_Broker_triggered()
{
    ui->MQTT_widget->setEnabled(true);
    ui->Serial_widget->setEnabled(false);
    ui->MQTT_Vlayout->setEnabled(true);
    ui->Serial_Vlayout->setEnabled(false);
    ui->MQTT_widget->show();
    ui->Serial_widget->hide();
    MainWindow::setPlotSource(PLOT_SOURCE_MQTT);
}

/***** MQTT unsub button slot *****/
void MainWindow::on_unsub_button_clicked()
{
    if(m_client->state()!= QMqttClient::Connected){
        add_to_log("Could not unsubscribe, please reconnect and retry\r\n");
        return;
    }
    for(int i=0;i<subscribed_topics.count();i++){
        if(subscribed_topics[i].compare(ui->unsub_topic_field->text())==0){
            subscribed_topics.remove(i);

            ui->subed_textb->clear();

            for(auto str : subscribed_topics){
                ui->subed_textb->insertPlainText(str +"\r\n");
            }

            m_client->unsubscribe(ui->unsub_topic_field->text());
        }
    }
}

/***** Function to return current plot source (MQTT/Serial) *****/
MainWindow::plot_source_t MainWindow::getPlotSource(){
    return plot_source;
}

/***** Function to set current plot source (MQTT/Serial) *****/
void MainWindow::setPlotSource(MainWindow::plot_source_t ps){
    plot_source = ps;
    subscribed_topics.clear();
    ui->subed_textb->clear();
    if(ps==PLOT_SOURCE_SERIAL){
        m_client->disconnectFromHost();
    }

    else if (ps==PLOT_SOURCE_MQTT){
        serial.disconnect();
        serial.close();
    }
}

/***** Slot to update the plot view when scrollbar is moved) *****/
void MainWindow::on_plot_scrollbar_valueChanged(int value)
{

    if (qAbs(ui->plot_3->xAxis->range().center()-value/1000.0) > 0.01) // if user is dragging plot, we don't want to replot twice
    {
        int selected = qv_x.size()>0 ? (((qv_x.size()-1)*value)/1000) : 0;
        int pos,size;
        if(qv_x.size()>12){
            if(ui->actionUse_Timestamp->isChecked()){
                pos = value<(12000/(qv_x.size()-1)) ? qv_t[12] : qv_t[selected];
                size = value<(12000/qv_x.size()-1) ? qv_t[12]-qv_t[0] : qv_t[selected]-qv_t[selected-12];
            }
            else{
                pos = value<(12000/(qv_x.size()-1)) ? 12 : qv_x[selected];
                size = value<(12000/(qv_x.size()-1)) ? 12 : qv_x[selected]-qv_x[selected-12];
            }
            ui->plot_3->xAxis->setRange(pos,size,Qt::AlignRight);
            ui->plot_3->replot();
        }
    }
}

/***** MQTT status changed callback *****/
void MainWindow::mqtt_status_changed(){

    QMqttClient::ClientState state = m_client->state();

    if(state==QMqttClient::Connecting){
        add_to_log("Connecting to broker\r\n");
        return;
    }
    else if(state==QMqttClient::Connected){
        add_to_log("Connected to broker\r\n");
    }
    else{
        char buf [64];
        sprintf(buf,"Unable to connect to broker. Error Code: %d\r\n",m_client->error());
        add_to_log(buf);
        return;
    }
}


/***** Clear data slot) *****/
void MainWindow::on_actionClear_Data_triggered()
{
    qv_x.clear();
    qv_y.clear();
    qv_t.clear();
    data_points=0;
    ui->plot_3->graph(0)->setData(qv_x,qv_y);
    ui->plot_3->replot();
    ui->serial_log->clear();
    serialInData.clear();
}

/***** Function to add new data to the log *****/
void MainWindow::add_to_log(QString str){

    if(!ui->actionPause_Log->isChecked()){
        serialInData.append(str);
        ui->serial_log->setText(serialInData);
        QScrollBar *sb = ui->serial_log->verticalScrollBar();
        sb->setValue(sb->maximum());
    }

}
