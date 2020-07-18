[Table of Contents](/README.md) 

<img src="img/Icon-jpg-small.jpg" width="80px" align="right">

---

# Getting Started

In this section, we will look at how to setup your own development environment so that you can work on your own computer. 

## Hardware
There are two pieces of hardware provided with this course:

* **Target Board** - A small low-powered "microcontroller", typically _embedded_ into a larger electronic system, that we will be programming to monitor the external environment and control devices.
 
* **Module Support Board** - This is a custom board containing sensors and output devices. You plug your Target Board into this in order to perform the various lab exercises.

 > There is another term you might encounter - the _host_ computer. This is referring to your PC. It is the machine you are writing code on. We write code on the _host_ and run it on the _target_

### Target Board
The target computer you will be programming is a small low-cost microcontroller based on the [Arm Cortex M4](https://www.arm.com/products/silicon-ip-cpu/cortex-m/cortex-m4)

* The microcontroller is a [STM32F429ZI](https://www.st.com/en/microcontrollers-microprocessors/stm32f429zi.html) made by [ST Microelectronics](www.st.com)
* The board which hosts this device (and a few peripheral devices) is a [ST-Nucleo-F429ZI](https://os.mbed.com/platforms/ST-Nucleo-F429ZI/)

An image of the Nucleo board is shown below:

<img src="img/nucleo/nucleo_top.jpg" width="300px">

This board is connected to your host PC using a USB connector. **Do not connect this yet**

   > It might be worth noting that Arm Ltd. design the core of Cortex M [microcontroller](/glossary/microcontroller.md), but do not actually manufacture any silicon. The devices are made by other organisations who license the design from Arm.

You will use this board throughout your course. It is surprisingly capable for such a low-power device.

### University of Plymouth Module Support Board
The [Nucleo Target Board](#Target-Board) contains a few _peripherals_, including a push switch, three [Light Emitting Diodes (LEDs)](/glossary/led.md). 

> Peripherals refer to external devices connected (interfaced) to the microcontroller chip. These are either input devices (such as a switch, or a temperature sensor) or output devices (such as an LED or motor controller). Some devices, such as storage cards and memory chips, are both input and output devices.

The Module Support Board contains a **lot** more peripherals you can communicate with. This will help you gain valuable experience interfacing to electronic devices as you go through the course. 

<img src="img/msb/msb.jpg" width="600px">

Your Nucleo board connects directly onto this board. Check the alignment using the following image and carefully connect your Nucleo to the module support board.

 > Never force! The connectors need to be aligned carfully, and gentle pressure should be enough to get the Nucleo pins to seat into the sockets.

 It is suggested that you do not remove the Nucleo from the module support board until instructed to do so.

<img src="img/msb/msb+nucleo.jpg" width="600px">

## Software

* All the software we use in this course is free
* Where possible, software is supported cross platform

1. [Microsoft Teams](#Microsoft-Teams)
1. [Mbed Studio](#Mbed-Studio)
1. [Installing Optional ST Software](#Installing-Optional-ST-Software)
1. [Visual Studio Code](#Visual-Studio-Code)
1. [GitHub Desktop](#GitHub-Desktop)
1. [Connecting and Updating your Development Board](#Connecting-and-Updating-your-Development-Board)
1. [Testing-Your-Board](Testing-Your-Board)

We will now install each package in turn. Should any of the following steps fail, you can contact the module leader or technician (via instant message) and they should be able to help you.

<img src="img/icons/teams.png" width="80px" align="right" >

### Microsoft Teams

For University of Plymouth students, this is essential!

> [Click this link to download and install Microsoft Teams](https://www.microsoft.com/microsoft-365/microsoft-teams/download-app)

Teams allows us to collaborate in many ways, including screen sharing and remote control. This has proven highly effective for supporting students with technical questions.

When you run Teams for the first time, sign in with your university credentials. Then check your audio and video settings are set to your preferred devices.

<img src="img/icons/mbed-studio.png" width="80px" align="right" >

### Mbed Studio

[Mbed](https://os.mbed.com/) is a framework for rapidly and easiy programming microcontrollers. It is used in most of our modules where microcontrollers are used. 

> You may have heard of the [Arduino](https://www.arduino.cc/) system? It is similar in many ways. In fact, for the latest versions, Arduino is built on top of Mbed-os.

#### Creating an Account on mbed.com
You cannot use Mbed without first creating an account on mbed.com. This is a requirement for many of our embedded modules.

* Go to https://os.mbed.com/ and click "Sign Up For Free"

Once you have created your account, please tell us what your username is:

[CLICK HERE TO REGISTER YOUR MBED.COM USERNAME](https://forms.office.com/Pages/ResponsePage.aspx?id=6-c3VPuDGk2_07skfgYb8XOZulv_kVlCjUXVUJQ1RZVUMVFNWjFOWkhPTE84OVBHT0lTMzI5QVVMVy4u)

This will help us better support you. Never disclose your password!

#### Installing the Developer Tools
The first step is to download and install the version of Mbed Studio for your computer.

> [Click this link to download Mbed-Studio](https://os.mbed.com/studio/)

Run the installer and you will probably find it is mostly self-explanatory. You can choose default options. Since version `1.0`, many of the additional tools needed for this software come included.

### Connecting your Target Board
The software that allows your PC to recognise your target board comes with Mbed Studio. The most important of these is the ST Link Driver.

To test this, you should now connect your Nucleo Board to your host PC using the supplied USB cable

<img src="img/nucleo/connect_usb.jpg" width="300px">

For the Mac and Linux, there is nothing to do. For Microsoft Windows, you can run Device Manager and check to see if the drivers are correctly installed:

<img src="img/DeviceManager.png" width="300px">

If there are no exclaimation marks next to any of the ST devices, you can [skip the next section](#Visual-Studio-Code)

### ST Link Drivers and Utilities
If there are exclamation marks against any of the ST devices, you may need to install the driver manually.  There are also some additional tools that you may need from time to time.

* ST Link Drivers ([STSW-LINK007](https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-utilities/stsw-link009.html)) - the latest version of the ST Drivers for Windows
* ST Link Update ([STSW-LINK007](https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-programmers/stsw-link007.html)) - used to upgrade the firmware on your Nucleo Board (all host platforms)
* STM32 ST-LINK utility ([STSW-LINK004](https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-programmers/stsw-link004.html)) - a useful tool for resetting and wiping boards. Rarely needed but sometimes useful

To obtain these packages, you need to create an account on st.com first. Please speak with one of the staff members if you have trouble doing this.

<img src="img/icons/vscode.png" width="80px" align="right" >

## Visual Studio Code
This is a really useful piece of software. It can be obtained using the following address:

https://code.visualstudio.com/

This is one of the preferred methods for editing text files and programming source files outside of Mbed Studio. It can even be used as a complete developer environment (with the right plugins).

<img src="img/icons/github.png" width="80px" align="right" >

## GitHub Desktop
These notes and all the source code are hosted on a site known as [GitHub](https://github.com/), which is a web repository that leverages the powerful [git version control system](https://git-scm.com/).

> Do not worry what a version control system is yet. You will use one simply to obtain the sample code for this course. The complex topic of software version control will be discussed later, and falls under the topic of _Software Engineering_.

For this course, you will need to do two things:

1. Create an account on GitHub
1. Install GitHub Desktop and Sign In

### Create an Account on GitHub
First of all, you can simply create an account using https://github.com/

You might want to change your account to a student account in order to get additional benefits - https://education.github.com/pack

Once you have done this, you must register this using the following form:

[CLICK HERE TO REGISTER YOUR GITHUB USERNAME](https://forms.office.com/Pages/ResponsePage.aspx?id=6-c3VPuDGk2_07skfgYb8XOZulv_kVlCjUXVUJQ1RZVUM0dBMUxWREE1RVlHUFVBSTJTTUtHWlg5RS4u)

We need this information in order to share code with you. Never disclose your password!

### Install GitHub Desktop on your Computer
You can download the very useful GitHub Desktop software on your own computer using the following link:

https://desktop.github.com/

When you run this the first time, you make be asked for your GitHub username and password. Once this is entered for a particular computer account, it should remember it for you. If you change computer or user account, it will need to be reentered.

### Clone the Notes
At some point, the tutor will email you a link to obtain a copy of various projects on GitHub. This link should launch use GitHub desktop automatically.

1. [Navigate to this page](https://github.com/UniversityOfPlymouth-Electronics/Embedded-Systems)
1. Click the `Code` button and select `Open with GitHub Desktop`

## Testing Your Board
Now you have all the key software tools, it's time to start testing the hardware.

1. [Download the test image here](https://github.com/UniversityOfPlymouth-Electronics/Embedded-Systems/raw/master/Hardware/ModuleSupportBoard/board-test.bin)
1. Drag and Drop this onto your target board

[Click here to watch a video explaining how to do this](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=fca139f3-1931-4bb6-a22d-abfb00fa99a8)


## Trouble Shooting

If any of the steps above fail, it is best to contact a member of staff, either in person, or via Teams.

* When you connect your ST Board, it should appear as an external storage device on your computer. Browsing this drive you should see two files. If not, inform the module staff and maybe use Teams to screenshare so they can diagnose the problem.

* One of the most common issues is the "firmware" on the Nucleo Boards. This firmware is partly responsible to maintaining the connection between the host PC and the Target. You can update to the latest version using the [ST Link Update Tool](#ST-Link-Drivers-and-Utilities).

* On the ST Link, check the power light is GREEN and not red. If Red, this suggests the USB port may not be able to supply sufficient power.



---

