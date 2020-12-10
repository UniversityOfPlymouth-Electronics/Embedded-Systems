/*#if !FEATURE_LWIP
    #error [NOT_SUPPORTED] LWIP not supported for this target
#endif
 */
#include "mbed.h"
#include "EthernetInterface.h"
#include "TCPSocket.h"
 
#define HTTP_STATUS_LINE "HTTP/1.0 200 OK"
#define HTTP_HEADER_FIELDS "Content-Type: text/html; charset=utf-8"
#define HTTP_MESSAGE_BODY ""                                     \
"<html>" "\r\n"                                                  \
"  <body style=\"display:flex;text-align:center\">" "\r\n"       \
"    <div style=\"margin:auto\">" "\r\n"                         \
"      <h1>Hello World</h1>" "\r\n"                              \
"      <p>It works !</p>" "\r\n"                                 \
"    </div>" "\r\n"                                              \
"  </body>" "\r\n"                                               \
"</html>" "\r\n"
    
#define HTTP_RESPONSE HTTP_STATUS_LINE "\r\n"   \
                      HTTP_HEADER_FIELDS "\r\n" \
                      "\r\n"                    \
                      HTTP_MESSAGE_BODY "\r\n"
#define HTTP_TITLE     "<head><title> Plymouth Uni Weather Page </title></head>" "\r\n"
#define HTTP_FORMAT_1 "<body style=\"display:flex;text-align:center\">" "\r\n" \
                      "<div style=\"margin:auto\">" "\r\n"
#define HTTP_BOTTOM "</html>" "\r\n"

 

#define IP        "10.0.0.10"
#define NETMASK   "255.255.255.0"
#define GATEWAY   "10.0.0.1"

 


//const char *const myHTTP = HTTP_RESPONSE; //This if you wish to set above Compiler defines into Flash Silicon

 

void ReadFlag_ISR(void);
bool ReadFlag=true;

 

int main()
{
    printf("\r\nBasic HTTP server example\r\n");
    
    //generic error code handle
    int err=0;
    
    // Ethernet Interface 
    EthernetInterface eth;
    eth.set_network(IP, NETMASK, GATEWAY); // comment this line out if you wish to use DHCP
    eth.connect();
    printf("\r\nThe target IP address is '%s'\r\n", eth.get_ip_address());
    
    // Use to be :- TCPServer srv;!!!
    TCPSocket srv;
    TCPSocket *clt_sock;
    
    // Open the server on ethernet stack
    srv.open(&eth);
    
    // BIND the server to the HTTP port (TCP 80)
    SocketAddress a;
    eth.get_ip_address(&a);
    err=srv.bind(a.get_ip_address(), 80);
    
    printf("IP Address confirm at : %s\n\r",eth.get_ip_address());
    
    if(err==0){printf("Bind OK\n\r");}
    else  printf("Bind error=%d\n\r",err);

 

    // LISTEN Can handle 5 simultaneous connections
    err=srv.listen(5);
    if(err==0){printf("Listening OK\n\r");}
    else  printf("Listen error=%d\n\r",err);
    
    // ACCEPT Accepting connections now.....
    //clt_sock=srv.accept();

 

    while (true)
    {
        // ACCEPT Accepting connections now.....
        clt_sock=srv.accept();
        printf("Waiting.....\n\r");
        printf("%s STRING LENGTH is:%d\n\r",HTTP_RESPONSE,strlen(HTTP_RESPONSE)); // the rest of this line to use Flash Silicon *see notes above line number 35" myHTTP,strlen(myHTTP));
        clt_sock->send(HTTP_RESPONSE, strlen(HTTP_RESPONSE));  //myHTTP,mydatasize)the rest of this line to use Flash Silicon *see notes above line number 35" myHTTP,strlen(myHTTP));
        if(err==0){printf("Sent OK!\n\r");}
        else printf("Send error=%d\n\r",err);
        clt_sock->close();
        wait_us(1000000);//Delay 1 second
    }
}
 
//have to close socket to re-enter