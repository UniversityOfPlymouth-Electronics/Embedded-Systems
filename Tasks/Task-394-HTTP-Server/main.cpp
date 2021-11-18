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
        
        //Construct response string (in C++)
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

        //You are responsible to close this
        clt_sock->close();
        disp.locate(1, 0);
        disp.printf("Closed...       ");

        ThisThread::sleep_for(1s);
    }


}
 
//have to close socket to re-enter