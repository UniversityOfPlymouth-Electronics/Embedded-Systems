/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
 
 // cedalo management center
// http://<ip address>:8088

// Uses MQTT library for Mbed 
// https://github.com/ARMmbed/mbed-mqtt

// Uses MbedJsonValue library
// https://os.mbed.com/users/samux/code/MbedJSONValue/ 

// Subscribe from a terminal - with username "win11", password "1234" and client ID "win11" Qo0 0
// mosquitto_sub -h <ip address> -t "f429/potValue" -u "win11" -P "1234" -i "win11"  -q 0 -v



#include "mbed.h"
#include "EthernetInterface.h"
#include <MQTTClientMbedOs.h>
#include "utils.hpp"
#include <MbedJSONValue.h>


using namespace std;
using namespace uop_msb;

// Network interface
EthernetInterface net;

#define IPV4_BROKER_ADDRESS "10.208.63.128"
#define SOCKET_PORT 1883

DigitalIn BlueButton(USER_BUTTON);
AnalogIn pot(AN_POT_PIN);


TCPSocket socket;
MQTTClient client(&socket);
void messageArrived(MQTT::MessageData& md);
MQTT::Message createMessage(char* payload,MQTT::QoS qos,bool dup, bool retained);

NotificationLED nled(LED3);
Identifier id;
//Identifier id("subscriber1");

MbedJSONValue mjv;

bool keepGoing = true;

int main()
{
    
    nsapi_error_t err;
 
    // Bring up the ethernet interface
    printf("MQTT publisher example\n");
    net.disconnect();

    err = net.connect();
    if(err!=0){
        printf("Error Connecting to Ethernet Interface.\r\nError code:%d\r\nExitting...",err);
        return -1;
    }

    printf("Ethernet interface connected \r\n");


    // Show the network address
    SocketAddress a;
    net.get_ip_address(&a);

    SocketAddress gw;
    net.get_gateway(&gw);
    printf("Gateway: %s\n\r", gw.get_ip_address() ? gw.get_ip_address() : "None");

    lcdDisp.cls();
    lcdDisp.locate(0, 0);
    printf("P%s\n", a.get_ip_address() ? a.get_ip_address() : "None");

    // Open a socket on the network interface, and create a TCP connection to the TCP server
    err = socket.open(&net);
    if(err!=0){
        printf("Error Opening Socket.\r\nError code:%d\r\nExitting...",err);
        return -1;
    }

    printf("Socket Opened\r\n");

    //Set the TCP socket port
    a.set_port(SOCKET_PORT);
    net.gethostbyname("eu1.cloud.thethings.network", &a);
    printf("Server IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");
    printf("Connecting to Socket\r\n");

    err = socket.connect(a);
    if(err!=0){
        printf("Error Connecting to Socket.\r\nError code:%d\r\nExitting...",err);
        return -1;
    }

    printf("Connected to Socket\r\n");

    printf("Connecting to Server\r\n");

    MQTTPacket_connectData pcd = MQTTPacket_connectData_initializer;
    pcd.MQTTVersion = 3;
    pcd.clientID.cstring = "loratestappi1@ttn";
    pcd.username.cstring = "loratestappi1@ttn";
    pcd.password.cstring = "NNSXS.AKUWKKVZOYV4RVCPSRLNSUXMXZBXHZLB5A3VDEQ.KH4YHHFMPDIZYT2AYM2HOYHDC5ZPCE6V26MBDFAPMY2RF7I3DB4Q";
    pcd.keepAliveInterval = 0xffff;

    Timer t;
    t.start();

    while((!client.isConnected()) && t.read_ms()< 10000 ){
        err = client.connect(pcd);
    }
    
    if(err<0){
        printf("Failed to connect to Broker. Error Code:%d\n",err);
        printf("Exiting...\n");
        return -1;
    }
    printf("Connected to broker\r\n");

    std::string topic = "#";  
    //topic = "v3/+/devices/eui-70b3d57ed005c84d/up";
    topic = "v3/+/#";
    //topic = "v3/+/devices/eui-70b3d57ed005c84d/up";


    printf("Subscribing to topic %s\r\n", topic.c_str());
    if ((err = client.subscribe(topic.c_str(), MQTT::QOS0,messageArrived)) != 0){
        printf("Subscribe failed. Error code %d\n",err);
    }
    else{
        printf("Subscribed to topic %s \r\n", topic.c_str());
    }
    
    client.setDefaultMessageHandler( (MQTTClient::messageHandler) messageArrived);
    
    client.yield();
    while(keepGoing){
      //   client.yield();
         ThisThread::sleep_for(osWaitForever);
    }
   
    // Disconnect from the Server
    client.disconnect();
    // Close the socket to return its memory and bring down the network interface
    socket.close();
    // Bring down the ethernet interface
    net.disconnect();
    printf("Disconnected. Now entering sleep mode\n");

    sleep();

}

MQTT::Message createMessage(char* payload,MQTT::QoS qos,bool dup, bool retained){
    MQTT::Message msg;
    msg.qos = qos;
    msg.payload = (void*)payload;
    msg.payloadlen = strlen((char*)msg.payload);
    msg.dup = dup;
    msg.retained = true;//retained;
    return msg;
}

void messageArrived(MQTT::MessageData& md)
{
    nled.notify();
    printf("GOT\n");
    MbedJSONValue mjv;
    MQTT::Message &message = md.message;
    parse(mjv, (char*)message.payload);
    std::string my_str;
    MbedJSONValue obj_mjv;
    parse(obj_mjv,(char*)message.payload);
    my_str = obj_mjv["dev_eui"].get<std::string>();

    printf("my_str: %s\r\n", my_str.c_str());
    client.yield();
}

