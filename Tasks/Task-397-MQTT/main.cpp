/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "uop_msb.h"
#include "mbed.h"
#include "EthernetInterface.h"
#include <MQTTClientMbedOs.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
using namespace uop_msb;

// Network interface
EthernetInterface net;
char rbuffer[65];

#define IPV4_HOST_ADDRESS "192.168.1.220"
#define IPV4_BROKER_ADDRESS "192.168.1.6"

#define SOCKET_PORT 1883

DigitalIn BlueButton(USER_BUTTON);
AnalogIn pot(AN_POT_PIN);
LCD_16X2_DISPLAY lcdDisp;
DigitalOut backLight(LCD_BKL_PIN,1);

// cedalo management center
// http://<ip address>:8088

// Uses MQTT library for Mbed 
// https://github.com/ARMmbed/mbed-mqtt

// Subscribe from a terminal - with username "win11", password "1234" and client ID "win11" Qo0 0
// mosquitto_sub -h <ip address> -t "f429/potValue" -u "win11" -P "1234" -i "win11"  -q 0 -v

// Socket demo
int main()
{
    // Bring up the ethernet interface
    printf("MQTT publisher example\n");
    net.connect();
    bool keepGoing = true;
 
    do {
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
        TCPSocket socket;
        MQTTClient client(&socket);
        socket.open(&net);

        //Set the TCP socket port
        a.set_port(SOCKET_PORT);

        //Option 1. Look up IP address of remote machine on the Internet
        //net.gethostbyname("ifconfig.io", &a);
        //net.gethostbyname("mozziemanager.local", &a);
        //printf("Server IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");

        //Option 2. Manually set the address (In a Windows terminal, type ipconfig /all and look for the IPV4 Address for the network interface you are using)
        //a.set_ip_address(IPV4_BROKER_ADDRESS);

        //Option 3. Automatically use the gateway address (the host PC if sharing a connection)
        a.set_ip_address(gw.get_ip_address());

        //Connect to remote server
        cout << "Connect to socket" << endl;
        socket.connect(a);

        //Now to publish
        cout << "Connect to server: " << a.get_ip_address() << endl;
        lcdDisp.locate(1, 0);
        lcdDisp.printf("B:%s", a.get_ip_address());
        
        MQTTPacket_connectData pcd = MQTTPacket_connectData_initializer;
        pcd.MQTTVersion = 3;
        pcd.clientID.cstring = (char*)"nucleo_1";
        pcd.username.cstring = (char*)"nucleo";
        pcd.password.cstring = (char*)"f429zi";
        client.connect(pcd);

        char strPayload[64];
        float potValue = pot;
        sprintf(strPayload, "%5.3f", potValue);
        cout << "Publish payload \"" << strPayload << "\" with topic f429/potValue" << endl;

        MQTT::Message msg;
        msg.qos = MQTT::QoS::QOS0;
        msg.payload = (void*)strPayload;
        msg.payloadlen = strlen((char*)msg.payload);
        msg.dup = false;
        msg.retained = false;
        client.publish("f429/potValue", msg);
        nsapi_error_t e = client.yield();
        if (e != NSAPI_ERROR_OK) {
            cout << "Error" << endl;;
        } else {
            cout << "OK" << endl;
        }
        ThisThread::sleep_for(2s);
        client.disconnect();

        // Close the socket to return its memory and bring down the network interface
        socket.close();

        //Loop delay of 2.5s
        wait_us(2500000);

    } while (keepGoing);


    // Bring down the ethernet interface
    net.disconnect();
    printf("Disconnected. Now entering sleep mode\n");

    sleep();

}
