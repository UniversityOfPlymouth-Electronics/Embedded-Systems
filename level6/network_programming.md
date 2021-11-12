# [Back to Contents](README.md)

---

# Network Programming 
At the time of writing, we are observing a rapid growth in networked devices. Sometimes branded, the *Internet of Things*, what this amounts to are networked embedded systems which form part of a later network of computing devices and services. It is therefore more important than ever that we have some grounding in network programming.

## Connecting the target to the Internet
For some of the first tasks, the target board at least needs a connection to your host PC, and for later tasks, a route to the Internet. 

There are some options, and which you choose may depend on where your target board is located.

* Option 1 - local network socket. The board we are using as an ethernet port. This can be directly connected to a hub or switch for a local network. If working in a home environment, this might be directly into a home router, a network extender or maybe even an installed ethernet socket. Corporate networks may have socket security which prevent such configurations. 

* Option 2 - sharing the Internet with the host PC. Plymouth students are provided with a USB to Ethernet adapter. This adds an extra ethernet interface to a PC or Mac. The approach is to share the hosts active Internet connection with this additional adapter. By doing so, the host computer will allocate an IP address for the target, and route all Internet traffic requested from the target board. This configuration is likely to work best for students using their own PC. Corporate managed computers might not permit this.

* Option 3 - 3G/4G Access Point (charges may apply). One option some use is to source a 3G/4G access point. Some devices connect to the Internet over the cellular network, and provide access via an ethernet socket. However, some of these tasks need your host computer to share the same local network as the host. It can be quite difficult to allow the host to connect to the target network this way.

Other sophisticated options may exist. For Plymouth students, option 2 is the recommended approach (USB adapters are provided).

## TCP/IP Client
In this example, the target device will act as a simple **web client**. The server is the website http://ifconfig.io/ . 

| Task-390-TCP-Client | - |
| - | - |
| 1 | Open Task-390, build and run |
| - | Note that is output to the terminal |
| 2 | Read through the code and comments |

In this example, the NUCLEO target board is the *client*. The website http://ifconfig.io/ is a computer running an application using a **web server**.

The **client-server** relationship works as follows:

1. The *client* (NUCLEO) connects to the *server* and sends the following ASCI string (to the Internet address ifconfig.io:80) as a request:

`GET / HTTP/1.1\r\nHost: ifconfig.io\r\nConnection: close\r\n\r\n`

This is formatted using the all-pervasive `HTTP` text protocol.

2. The client now blocks waiting for a response.
3. The listening *server* receives the request, interprets it and constructs a response. 
   * This is typically performed by a *server side application*, which runs when the request is received, and outputs `HTTP` responses 
   * The response is typically formatted in either HTTP (such that it can be viewed by a web browser) or a protocol such as XML or JSON (so that it can be easily ready by a computer).
4. The response is returned (over the Internet)
5. The client unblocks and reads the response until all bytes have been received.
6. The connection is then closed (and forgotten)

This request-response cycle will close and does not persist - we say it is *stateless*.

> Note the request is formatted using the `HTTP` protocol. This widely used text-based protocol is the basis of the *World Wide Web*. 
>
> This exchange was performed using the TCP protocol, which is a lower-level (binary) protocol that expects a request and a response (or timeout). Other protocols could have been used (e.g. UDP), but TCP is the most common.
>
> All the TCP data is sent over the *Internet* using the `IP` protocol. The binary `IP` protocol is the system used to route data over a world-wide network of computers.
>
> You often see the expression `TCP/IP` which reads as `TCP` over `IP`. 

Our software is mostly concerned with write `HTTP` strings using the `TCP/IP` protocol layers. 


** TO BE CONTINUED **

## Network Time Protocol (NTP) Client
Not all Internet data is HTTP or text.

```C++
    NetworkInterface *_defaultSystemNetwork;
    
    _defaultSystemNetwork = NetworkInterface::get_default_instance();
    if (_defaultSystemNetwork == nullptr) {
        LogError("No network interface found");
        return -1;
    }

    int ret = _defaultSystemNetwork->connect();
    if (ret != 0) {
        LogError("Connection error: %d", ret);
        return -1;
    }
    cout << _defaultSystemNetwork->get_mac_address()) << endl;

    NTPClient ntp(_defaultSystemNetwork);
    ntp.set_server("time.google.com", 123);
    time_t timestamp = ntp.get_timestamp();
    if (timestamp < 0) {
        LogError("Failed to get the current time, error: %ld", timestamp);
        return -1;
    }

    cout <<"Time: " << ctime(&timestamp) << endl;
    set_time(timestamp);
```

## Cloud Services with Azure IoT Central
Before you start this section, make sure you set up a [student account](https://azure.microsoft.com/en-gb/free/students/) or a [free account](https://azure.microsoft.com) if not a student.

For this example, we are going to use Microsoft Azure IoT Central. IoT is described as "Software as a Service" (SaaS). This provides a very convenient way to upload data from an embedded device to the cloud, where is can easily be logged and displayed on charts and in tables.

> SaaS is a method of software delivery and licensing in which software is accessed online via a subscription, rather than bought and installed on individual computers.



[Video 1 - Creating the Application](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=0604b16b-38de-43f1-8828-addd010e6e9a)

[Video 2 - Device Templates](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=3d8eedf1-63f9-48c6-a1d5-addd010f0c2f)

[Video 3 - Views](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=aef77cd6-b58d-49d9-a99a-addd010fe2b1)

[Video 4 - Devices](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=0c2b3d7e-c736-4343-ae7a-addd0110973c)

[Video 5 - Configure the Target Board](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=93466dc5-325a-4a1f-869e-addd01123210)

[Video 6 - Adding Additional Parameters](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=7714d640-75b6-44a9-a923-addd0117f2d9)

[Video 7 - Sending Back Commands](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=5b536473-e042-4e6a-86cd-addd01257498)




## Further Learning
A good place to go is the following tutorial from Microsoft Learn:

[Create your first Azure IoT Central app](https://docs.microsoft.com/learn/modules/create-your-first-iot-central-app/)

**TO BE CONTINUED**



---

# [Back to Contents](README.md)