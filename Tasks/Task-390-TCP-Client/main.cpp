/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "EthernetInterface.h"

// Network interface
EthernetInterface net;
char rbuffer[65];

#define IPV4_HOST_ADDRESS "10.42.0.1"
#define TCP_SOCKET_PORT 8888

DigitalIn BlueButton(USER_BUTTON);
DigitalOut led(LED1);

// Socket demo
int main()
{
    // Bring up the ethernet interface
    printf("Ethernet socket example\n");
    net.connect();
    bool keepGoing = true;
 
    do {
        // Show the network address
        SocketAddress a;
        net.get_ip_address(&a);
        printf("IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");

        // Open a socket on the network interface, and create a TCP connection to the TCP server
        TCPSocket socket;
        socket.open(&net);

        //Option 1. Look up IP address of remote machine on the Internet
        //net.gethostbyname("ifconfig.io", &a);
        //printf("IP address of site: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");

        //Option 2. Manually set the address (In a Windows terminal, type ipconfig /all and look for the IPV4 Address for the network interface you are using)
        a.set_ip_address(IPV4_HOST_ADDRESS);

        //Set the TCP socket port
        a.set_port(TCP_SOCKET_PORT);

        //Connect to remote web server
        socket.connect(a);

        // Send a simple array of bytes (I've used a string so you can read it)
        char sbuffer[] = "Hello, this is the MBED Board talking!";
        char qbuffer[] = "END";

        int scount;
        if (BlueButton == 0) {
            scount = socket.send(sbuffer, sizeof sbuffer);
        } else {
            printf("Sending END\n");
            scount = socket.send(qbuffer, sizeof qbuffer);
            keepGoing = false;
        }
        
        printf("sent\r\n");

        // ***********************************************************
        // Receive a simple array of bytes as a response and print out
        // ***********************************************************

        int rcount;

        // Receieve response and print out the response line
        while ((rcount = socket.recv(rbuffer, 64)) > 0) {
            rbuffer[rcount] = 0;    //End of string character
            printf("%s", rbuffer);
        }
        printf("\n");

        //Check for error
        if (rcount < 0) {
            printf("Error! socket->recv() returned: %d\n", rcount);
            keepGoing = false;
        }

        // Close the socket to return its memory and bring down the network interface
        socket.close();

        //Loop delay of 5s
        wait_us(5000000);

    } while (keepGoing);


    // Bring down the ethernet interface
    net.disconnect();
    printf("Disconnected. Now entering sleep mode\n");

    sleep();

}
