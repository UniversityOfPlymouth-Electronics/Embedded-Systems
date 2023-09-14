/*#if !FEATURE_LWIP
    #error [NOT_SUPPORTED] LWIP not supported for this target
#endif
 */
#include "uop_msb.h"
using namespace uop_msb;
#include <iostream>
using namespace std;
#include "EthernetInterface.h"
#include "TCPSocket.h"

#define RESPONSE "AOK"
#define FINALRESPONSE "Bye"

EthernetInterface net;
LCD_16X2_DISPLAY disp;
DigitalOut lcdBacklight(LCD_BKL_PIN);
BusOut onBoardLEDs(LED1, LED2, LED3);

DigitalOut led(LED1);
 

int main()
{
    printf("\r\nBasic TCP server example\r\n");
    
    // Connect the ethernet interface
    // net.set_network(IP, NETMASK, GATEWAY);  //For static IP
    net.connect();

    // Get the network address
    SocketAddress a;
    net.get_ip_address(&a);

    // Show the network address of the server (Nucleo)
    printf("IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");
    disp.cls();
    disp.printf("%s\n", a.get_ip_address() ? a.get_ip_address() : "None");
    lcdBacklight = 1;

    // Open a TCP socket on the network interface, and create a TCP connection on port 8080
    TCPSocket socket;
    socket.open(&net);
    socket.bind(8080);

    //Set socket to listening mode (up to 5 connections)
    int err=socket.listen(5);
    if(err==0) {
        printf("Listening OK\n");
    }
    else {
        printf("Listen error=%d\n",err);
        socket.close();
        net.disconnect();
        while(1);
    }

    bool keepGoing = true;

    do
    {
        disp.locate(1, 0);
        disp.printf("Waiting...");

        // ACCEPT Accepting connections
        TCPSocket* clt_sock=socket.accept();    //Blocking
        printf("Connected accepted\n");

        //Unblocks with each connection
        disp.locate(1, 0);
        disp.printf("Connected...");

        //Read request
        string rx;
        char rxBuffer[65];
        nsapi_size_or_error_t N = clt_sock->recv(rxBuffer, sizeof(rxBuffer)-1);   //Read (upto) 64 bytes
        rxBuffer[N] = 0;
        printf("%s\n", rxBuffer);
        rx = string(rxBuffer);             //String response as C++ string

        if (rx == "END") {                      //Are we done?
            keepGoing = false;
            printf("END Sent - terminating\n");
        }
        else if (rx == "LIGHT") {
            lcdBacklight = !lcdBacklight;
            onBoardLEDs = onBoardLEDs ^ 7;
        }

        //Send response (blocking until completed)
        nsapi_size_or_error_t ret;
        if (keepGoing) {
            printf("Sending response: %s, LENGTH %d\n", RESPONSE, strlen(RESPONSE)); 
            ret = clt_sock->send(RESPONSE, strlen(RESPONSE)); 
        } else 
        {
            printf("Sending final response: %s, LENGTH %d\n", FINALRESPONSE, strlen(FINALRESPONSE)); 
            ret = clt_sock->send(FINALRESPONSE, strlen(FINALRESPONSE));             
        }
 
        //Echo how many bytes were sent
        printf("Sent %d bytes\n", ret);

        //You are responsible to close this
        clt_sock->close();
        disp.locate(1, 0);
        disp.printf("Closed...\n");

        ThisThread::sleep_for(100ms);
    } while (keepGoing);

    //Close network connection
    net.disconnect();
    printf("Disconnected\n");

    sleep();
}
 
//have to close socket to re-enter
