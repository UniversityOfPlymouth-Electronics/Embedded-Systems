[Table of Contents](README.md) 

---

# Testing the Software
Once you are confident the hardware is working, we can turn our attention to programming.

For this, we will use Mbed Studio to perform the following steps:

1. Open the sample code (written in the language C++)
1. **Build** the code into something the target computer can understand
1. **Deploy** and **execute** the code on the target board
1. **Edit** the code in Mbed Studio to make a small change
1. Finally, we will **debug** the code, stepping through line by line

## Task101 - Blinky!
When learning to program an embedded computer, the tradition is to run "Blinky", a program that simply flashes an LED on and off. This is very simple to do in Mbed.

[Click this link](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=1cdd2263-5644-4322-841d-abfe0101c82a) to watch a video on how to program your board with Mbed Studio.

Now repeat the steps yourself.

## Debugging
A powerful tool in Mbed Studio is the "debugger". Although this tool is primarily designed to help find errors (bugs) in your code, it is also a powerful educational tool.

> The debugger allows you to run your code, line by line, observing how it works through cause and effect. 

[Click this link](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=e151c5c8-980d-42d6-ab32-abfe010d3a67) to watch a video on how to **debug** your code.

Now repeat the steps yourself.

## Clean up the files (Option 1)
With version 1.0 of Mbed studio, once built,each project consumes over 1Gb data on the local disk. Most of this is in the `mbed-os` folder within _each_ project. As we will be opening multiple projects and building them, this can quickly become problematic.

> This is one reason why you should not set your `git` root folder inside the folder tree of OneDrive or any other cloud service.

To clear some disk space, there is a work-around.

Using Explorer (Windows) or Finder (Mac), you can delete the `BUILD` and `mbed-os` folders. Do NOT delete the `mbed-os.lib` file

<img src="../img/delete-BUILD.png" width="400">

It is suggested you do not do this from within Mbed Studio itself.

## Shared Libraries (Option 2 - preferred)
If you have a lot of projects, each will consume in excess of 1Gb of disk space. Since Mbed Studio v1.2, there is an option to share library files between projects.

[Click Here](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=328ab29c-8301-4423-b905-ac33010f1f2a) to watch a video showing how this is done.

It is suggested you use shared library files for your own work.

---

[Contents](README.md) 

[NEXT - Troubleshooting](troubleshooting.md)