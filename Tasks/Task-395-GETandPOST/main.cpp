/*#if !FEATURE_LWIP
    #error [NOT_SUPPORTED] LWIP not supported for this target
#endif
 */
#include "uop_msb.h"
#include <cstdio>
using namespace uop_msb;

#include <iostream>
using namespace std;

#include "EthernetInterface.h"
#include "TCPSocket.h"
 

void extractRxData(TCPSocket* rxSock);
uint32_t FindParam (const char* pRxString, const char* pParamName, char* pParam);
void echoRxData(TCPSocket* rxSock);


 // HTTP string template. The {{0}} is a placeholder and will be replaced with a numerical value
 // Note how \ is used to break a string across lines without adding additional characters
#define HTTP_STATUS_LINE "HTTP/1.0 200 OK"
#define HTTP_HEADER_FIELDS "Content-Type: text/html; charset=utf-8"
#define HTTP_MESSAGE_BODY ""                                     \
"<html>" "\r\n"                                                  \
"  <body style=\"display:flex;text-align:center\">" "\r\n"       \
"    <div style=\"margin:auto\">" "\r\n"                         \
"      <h1>POT Value</h1>" "\r\n"                              \
"      <p>{{0}}</p>" "\r\n"                                 \
"    </div>" "\r\n"                                              \
"  </body>" "\r\n"                                               \
"</html>" "\r\n"
    
#define HTTP_TEMPLATE HTTP_STATUS_LINE "\r\n"   \
                      HTTP_HEADER_FIELDS "\r\n" \
                      "\r\n"                    \
                      HTTP_MESSAGE_BODY "\r\n"
#define HTTP_TITLE     "<head><title> Plymouth Uni Weather Page </title></head>" "\r\n"
#define HTTP_FORMAT_1 "<body style=\"display:flex;text-align:center\">" "\r\n" \
                      "<div style=\"margin:auto\">" "\r\n"
#define HTTP_BOTTOM "</html>" "\r\n"

 
//For the static IP version
#define IP        "10.0.0.10"
#define NETMASK   "255.255.255.0"
#define GATEWAY   "10.0.0.1"

//const char *const myHTTP = HTTP_RESPONSE; //This if you wish to set above Compiler defines into Flash Silicon

EthernetInterface net;
LCD_16X2_DISPLAY disp;
DigitalOut lcdBacklight(LCD_BKL_PIN);
AnalogIn pot(AN_POT_PIN);
DigitalOut redLED(LED3);

int main()
{
    printf("\r\nBasic HTTP server example\r\n");
    
    // Connect the ethernet interface
    //net.set_network(IP, NETMASK, GATEWAY);  //For static IP
    net.connect();

    // Get the network address
    SocketAddress a;
    net.get_ip_address(&a);

    // Show the network address
    printf("IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");
    disp.cls();
    disp.printf("%s\n", a.get_ip_address() ? a.get_ip_address() : "None");
    lcdBacklight = 1;

    // Open a TCP socket on the network interface, and create a TCP connection on port 80
    TCPSocket socket;
    socket.open(&net);
    socket.bind(80);

    //Set socket to listening mode (up to 5 connections)
    int err=socket.listen(5);
    if(err==0) {
        printf("Listening OK\n\r");
    }
    else {
        printf("Listen error=%d\n\r",err);
        socket.close();
        while(1);
    }

    while (true)
    {
        disp.locate(1, 0);
        disp.printf("Waiting...      ");

        // ACCEPT Accepting connections
        TCPSocket* clt_sock=socket.accept();    //Blocking

        //Unblocks with each connection
        disp.locate(1, 0);
        disp.printf("Connected...    ");

        //Construct web page
        float p = pot;  //Get pot value

        char buff[6];
        sprintf(buff, "%5.3f", p);  //Convert float to string
        
        //Construct response string (in C++) - BLAH
        string html = string(HTTP_TEMPLATE);
        size_t index = html.find("{{0}}");  //Find placeholder {{0}}
        if (index) {
            html.replace(index, 5, buff);   //Replace with pot value string
        }
        cout << html << endl;               //For debug purposes

        //Send response string (blocking until completed)
        printf("%s STRING LENGTH is: %d\n\r", html.c_str(), strlen(html.c_str())); // the rest of this line to use Flash Silicon *see notes above line number 35" myHTTP,strlen(myHTTP));
        nsapi_size_or_error_t ret = clt_sock->send(html.c_str(), strlen(html.c_str()));  //myHTTP,mydatasize)the rest of this line to use Flash Silicon *see notes above line number 35" myHTTP,strlen(myHTTP));
        
        //Echo how many bytes were sent
        printf("Sent %d bytes\n", ret);

        //Set redLED
        //extractRxData(clt_sock);
        echoRxData(clt_sock);

        //You are responsible to close this
        clt_sock->close();
        disp.locate(1, 0);
        disp.printf("Closed...       ");

        ThisThread::sleep_for(1s);
    }


}

#define ESC \x1b    //Escape character
#define CSI ESC[    //Command Sequence Initiator
#define CUU A       //Cursor UP
#define CUD B       //Cursor DOWN
#define CUF C       //Cursor FORWARD
#define CUB D       //Cursor BACKWARD

void echoRxData(TCPSocket* rxSock) 
{
    fflush(stdout);

    rxSock->set_blocking(false);
    char c;
    int rcount;
    int col = 0;
    printf("\n\r");
    do  {
        rcount = rxSock->recv(&c, 1);
        printf("%2X", c);
        printf("\x1b[1B\x1b[2D");   //Down 1, back 2
        //printf(" %c", c) but not the new lines etc..
        if (c == '\n') {
            printf("\\n");
        } else if (c == '\r') {
            printf("\\n");
        } else {
            printf("%2c", c);
        }
        printf("\x1b[1A\x1b[2C");   //Up 1, forward 2
        col++;
        if (col == 32) {
            col = 0;
            printf("\r\n\n\n\n");    //Return, down 4
        }
    } while (rcount == 1);

    rxSock->set_blocking(true);
}

void extractRxData(TCPSocket* rxSock)
{
        // Read data sent from the browser
        printf("*************recv***************\n\r");
        //clt_sock->set_timeout(2000);
        rxSock->set_blocking(false);
        char rbuffer[1024];
        int rcount = rxSock->recv(rbuffer, sizeof rbuffer);
        //Check for errors
        if (rcount > 0)
        {
            //The data will not have a 0 to mark the end of string so the following line will work around this by using a formatted string
            printf("recv %d [%.*s]\n", rcount, strstr(rbuffer, "\r\n") - rbuffer, rbuffer);

            //Let's see if the red LED state is set?
            char *redStr = strstr(rbuffer, "red=");
            if (redStr[4] == '1') {
                cout << "RED ON" << endl;
                redLED = 1;
            } else if  (redStr[4] == '0') {
                cout << "RED OFF" << endl;
                redLED = 0;
            }
            printf("************~recv***************\n\r");
        }
        rxSock->set_blocking(true);
}

uint32_t FindParam (const char* pRxString, const char* pParamName, char* pParam) 
{
    //Basic error checking
    if ((!pRxString) || (!pParam)) return -1;
 
    //Find parameter name
    const char* pLoc = strstr(pRxString, pParamName);
    if (!pLoc) return 0;

    //Extract pointer to value
    pParam = (char*)pLoc + strlen(pParamName);
    return (uint32_t)pLoc-(uint32_t)pRxString;
}