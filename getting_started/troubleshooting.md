[Table of Contents](README.md) 

---

# Troubleshooting

If any of the previous steps fail, it is best to contact a member of staff, either in person, or via Teams.

* When you connect your ST Board, it should appear as an external storage device on your computer. Browsing this drive you should see two files. If not, inform the module staff and maybe use Teams to screenshare so they can diagnose the problem.

* One of the most common issues is the "firmware" on the Nucleo Boards. This firmware is partly responsible to maintaining the connection between the host PC and the Target. You can update to the latest version using the [ST Link Update Tool](#ST-Link-Drivers-and-Utilities).

* On the ST Link, check the power light is GREEN and not red. If Red, this suggests the USB port may not be able to supply sufficient power.

* If the debug fails, ensure there are no syntax errors in your code. If now, try unplugging your USB cable from your host PC and reconnecting it. In some cases, I have had to reboot the host PC to get debugging to work.

## Board Not Detected in MS Windows

For Microsoft Windows, run Device Manager and check to see if the drivers are correctly installed:

<img src="../img/DeviceManager.png" width="300px">

If there are exclaimation marks next to any of the ST devices, it probably means your ST Link drivers are not installed.

## ST Link Drivers and Utilities
If there are exclamation marks against any of the ST devices, you may need to install the driver manually.  There are also some additional tools that you may need from time to time.

* ST Link Drivers ([STSW-LINK007](https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-utilities/stsw-link009.html)) - the latest version of the ST Drivers for Windows
* ST Link Update ([STSW-LINK007](https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-programmers/stsw-link007.html)) - used to upgrade the firmware on your Nucleo Board (all host platforms)
* STM32 ST-LINK utility ([STSW-LINK004](https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-programmers/stsw-link004.html)) - a useful tool for resetting and wiping boards. Rarely needed but sometimes useful

To obtain these packages, you need to create an account on st.com first. Please speak with one of the staff members if you have trouble doing this.

## Cannot Start A Debug Session
If you are trying to start a debug session, and you are getting error messages about the debugger timing out, you might need to restart the debug service on your PC.

https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=54f0b0ff-eb0f-41d7-bc19-ac0600e5f949

---

[Table of Contents](README.md) 