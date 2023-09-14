/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
 
 // cedalo management center
// http://<ip address>:8088

// Uses MQTT library for Mbed 
// https://github.com/ARMmbed/mbed-mqtt

// Subscribe from a terminal - with username "win11", password "1234" and client ID "win11" Qo0 0
// mosquitto_sub -h <ip address> -t "f429/potValue" -u "win11" -P "1234" -i "win11"  -q 0 -v



#include "mbed.h"
#include "EthernetInterface.h"
#include <MQTTClientMbedOs.h>
#include "utils.hpp"

using namespace std;
using namespace uop_msb;

// Network interface
EthernetInterface net;

#define IPV4_BROKER_ADDRESS "10.208.63.128"
#define SOCKET_PORT 11883

DigitalIn BlueButton(USER_BUTTON);
AnalogIn pot(AN_POT_PIN);


TCPSocket socket;
MQTTClient client(&socket);
void messageArrived(MQTT::MessageData& md);
MQTT::Message createMessage(char* payload,MQTT::QoS qos,bool dup, bool retained);



NotificationLED nled(LED3);
Identifier id;
//Identifier id("subscriber1");

bool keepGoing = true;

int main()
{
    
    std::string user_name = id.get_name();
    printf("\r\nUnique ID: %llu User Name: %s\r\n",id.get_id(),user_name.c_str());
  
    nsapi_error_t err;
 
    // Bring up the ethernet interface
    printf("MQTT publisher example\n");
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
    lcdDisp.printf("P%s\n", a.get_ip_address() ? a.get_ip_address() : "None");

    // Open a socket on the network interface, and create a TCP connection to the TCP server
    err = socket.open(&net);
    if(err!=0){
        printf("Error Opening Socket.\r\nError code:%d\r\nExitting...",err);
        return -1;
    }

    printf("Socket Opened\r\n");

    //Set the TCP socket port
    a.set_port(SOCKET_PORT);

    //Option 1. Look up IP address of remote machine on the Internet
    //net.gethostbyname("ifconfig.io", &a);
    //net.gethostbyname("mozziemanager.local", &a);
    //printf("Server IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");

    //Option 2. Manually set the address (In a Windows terminal, type ipconfig /all and look for the IPV4 Address for the network interface you are using)
    a.set_ip_address(IPV4_BROKER_ADDRESS);

    //Option 3. Automatically use the gateway address (the host PC if sharing a connection)
   // a.set_ip_address(gw.get_ip_address());

    //Connect to remote server
    printf("Connecting to Socket\r\n");
    err = socket.connect(a);
    if(err!=0){
        printf("Error Connecting to Socket.\r\nError code:%d\r\nExitting...",err);
        return -1;
    }

    printf("Connected to Socket\r\n");

    printf("Connecting to Server\r\n");
    lcdDisp.locate(1, 0);
    lcdDisp.printf("B:%s", a.get_ip_address());

    //Now to publish
    MQTTPacket_connectData pcd = MQTTPacket_connectData_initializer;
    pcd.MQTTVersion = 3;
    pcd.clientID.cstring = (char*)user_name.c_str();
    pcd.username.cstring =  (char*)user_name.c_str();
    pcd.password.cstring = (char*)"1234";
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

    //char* topic = "f429";
    char* topic = "v3/+/devices/eui-70b3d57ed005e85d/up";

    printf("Subscribing to topic %s\r\n", topic);
    if ((err = client.subscribe(topic, MQTT::QOS0, (MQTTClient::messageHandler) messageArrived)) != 0){
        printf("Subscribe failed. Error code %d\n",err);
    }
    else{
        printf("Subscribed to topic %s \r\n", topic);
    }
    
    while(keepGoing){

        char strPayload[64];
        float potValue = pot;
        sprintf(strPayload, "%5.3f", potValue);
        MQTT::Message msg = createMessage(strPayload,MQTT::QOS0,false,false);

        err = client.publish("f429", msg);
        printf("%s\r\n",(err==0) ? "Publish successful" : "Failed to publish");
        client.yield();
        // //Loop delay of 2.5s
        ThisThread::sleep_for(2500ms);

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
    msg.retained = retained;
    return msg;
}

void messageArrived(MQTT::MessageData& md)
{
    nled.notify();
    MQTT::Message &message = md.message;
    printf("\x1B[92m");
    printf("\r\nMessage arrived: qos %d, retained %d, dup %d, packetid %d\r\n", message.qos, message.retained, message.dup, message.id);
    printf("Payload %.*s\n", message.payloadlen, (char*)message.payload);
    printf("\x1B[97m");
    client.yield();
}

