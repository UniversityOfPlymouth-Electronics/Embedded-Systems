/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "EthernetInterface.h"

// Network interface
EthernetInterface net;
char rbuffer[65];

// Socket demo
int main()
{
    // Bring up the ethernet interface
    printf("Ethernet socket example\n");
    net.connect();

    // Show the network address
    SocketAddress a;
    net.get_ip_address(&a);
    printf("IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");

    // Open a socket on the network interface, and create a TCP connection to ifconfig.io
    TCPSocket socket;
    socket.open(&net);

    //Look up IP address
    net.gethostbyname("ifconfig.io", &a);
    printf("IP address of site: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");

    //Set the TCP socket port to 80 (standard port for HTTP)
    a.set_port(80);

    //Connect to remote web server
    socket.connect(a);

    // Send a simple http request (text protocol understood by the server)
    char sbuffer[] = "GET / HTTP/1.1\r\nHost: ifconfig.io\r\nConnection: close\r\n\r\n";
    int scount = socket.send(sbuffer, sizeof sbuffer);
    printf("sent %d [%.*s]\n", scount, strstr(sbuffer, "\r\n") - sbuffer, sbuffer);

    // **************************************************************
    // Receive a simple http response and print out the response line
    // **************************************************************

    int rcount;

    // Receieve an HTTP response and print out the response line
    while ((rcount = socket.recv(rbuffer, 64)) > 0) {
        rbuffer[rcount] = 0;    //End of string character
        printf("%s", rbuffer);
    }
    printf("\n");

    //Check for error
    if (rcount < 0) {
        printf("Error! socket->recv() returned: %d\n", rcount);
    }

    // Close the socket to return its memory and bring down the network interface
    socket.close();

    // Bring down the ethernet interface
    net.disconnect();
    printf("Done\n");

    while(true);
}
