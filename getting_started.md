[Table of Contents](/README.md) 

<img src="img/Icon-jpg-small.jpg" width="80px" align="right">

---

# Getting Started

In this section, we will look at how to setup your own development environment so that you can work on your own computer. 

## Hardware
There are two pieces of hardware provided with this course:

### Target Board
The computer you will be programming is a small low-cost microcontroller based on the [Arm Cortex M4](https://www.arm.com/products/silicon-ip-cpu/cortex-m/cortex-m4)

* The microcontroller is a [STM32F429ZI](https://www.st.com/en/microcontrollers-microprocessors/stm32f429zi.html) made by [ST Microelectronics](www.st.com)
* The board which hosts this device is a [ST-Nucleo-F429ZI](https://os.mbed.com/platforms/ST-Nucleo-F429ZI/)

An image of the Nucleo board is shown below:

<img src="img/nucleo/nucleo_top.jpg" width="300px">

This board is connected to your PC using a USB connector. Do not connect this yet.

   > It might be worth noting that Arm Ltd. design the core of Cortex M microcontroller, but you do not manufacture any silicon.


### University of Plymouth Module Support Board
The [Nucleo Target Board](#Target-Board) contains a few peripherals, including a push switch, three [Light Emitting Diodes (LEDs)](/glossary/led.md)

## Software

* All the software we use is free
* Where possible, software is supported cross platform

1. [Installing Mbed Studio](#Installing-Mbed-Studio)
1. [Installing Optional ST Software](#Installing-Optional-ST-Software)
1. [GitHub Desktop](#GitHub-Desktop)
1. [Connecting and Updating your Development Board](#Connecting-and-Updating-your-Development-Board)
1. [Testing-Your-Board](Testing-Your-Board)


### Installing Mbed Studio
The first step is to download and install the version of Mbed Studio for your computer.

https://os.mbed.com/studio/

The installer is mostly self-explanatory. Since version `1.0`, many of the additional tools needed for this software come included.

### Installing Optional ST Software
The software that allows your PC to recognise your target board comes with Mbed Studio. The most important of these is the ST Link Driver.

For the Mac and Linux, there is nothing to do. For Microsoft Windows, you can run Device Manager and check to see if the drivers are correctly installed:

<img src="img/DeviceManager.png" width="300px">

If there are exclamation marks against any of the ST devices, you may need to install the driver manually. There are also some additional tools that you may need from time to time.

* ST Link Drivers ([STSW-LINK007](https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-utilities/stsw-link009.html)) - the latest version of the ST Drivers for Windows
* ST Link Update ([STSW-LINK007](https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-programmers/stsw-link007.html)) - used to upgrade the firmware on your Nucleo Board (all host platforms)
* STM32 ST-LINK utility ([STSW-LINK004](https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-programmers/stsw-link004.html)) - a useful tool for resetting and wiping boards. Rarely needed but sometimes useful

To obtain these packages, you need to create an account on st.com first. Please speak with one of the staff members if you have trouble doing this.

## GitHub Desktop

## Connecting and Updating your Development Board 

## Testing Your Board


---

