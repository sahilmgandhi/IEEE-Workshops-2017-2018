# IEEE_Workshops_2017_2018

Code base, powerpoints, and other materials for the IEEE 2017 to 2018 Workshop year.


# Lab Tools and Debugging Workshop

The powerpoint for the workshop is available in the folder.

# Through-Hole Soldering Workshop

The powerpoint as well as the .elf and .hex files are avaiable in the folder to program the MCU.

To program the ATMEGA-328, you can use a program like avrdude or even the Arduino IDE with an appropriate
programmer. You can also use another Arduino (like an Uno or a Nano) as a programmer for the ATMEGA-328.

# Eagle Workshop

The schematic that we used and the PCB that we created from it are available in this folder.

# Android + Bluetooth Workshop

### Instructions to Use:

    Bluetooth -> Arduino

For the AT-commands for the HC-05 Bluetooth Module, start both the BluetoothSerial and regular
Serial Monitor at a baud rate of 38400. Additionally, the EN pin must be set to HIGH (attach it
to the 3.3V line for the Arduino Nano), and the button on the HC-05 must be pressed as well while 
powering the device. Once the device is on, the button can be released, and the AT-commands will go through. 

After the AT-commands of choice have been coded, change the Baud rate of both Serial modes to 9600
for normal interaction with your Android application.

For other bluetooth modules, the Baud rate for the AT-mode and regular use mode might be different, 
and there may be other modes (not AT) to program the bluetooth module.

    Bluetooth -> Android

Turn on bluetooth on your Android device. Find the Bluetooth device with the name that you set up with 
the AT-commands. Connect to the device, and then open up the application. Remember to make sure the Baud rate
on the Arduino is set to 9600 (if you are using the HC-05) in order to properly send and receive data from your
Android device.


# 3D_Printing 

The powerpoint as well as the 3D printing guide to making objects for the lab's Dreammaker printer are available in this folder.

# Advanced MCU Workshop

The powerpoint and the code that we went over is available in this folder.

# SMD Soldering

The schematic and board that we used for this workshop are available in this folder.

# SPI Communication Workshop

The code we went over along with the powerpoint presentation are available in this folder. 

# TI Microcontroller

In this workshop, we use the MSP432P401R Launchpad from Texas Instruments. In our presentation, we included a simple project that allows you to use the launchpad to control the ultrasonic distance sensor. The serial port will print the sensor's distance to the object it is directly facing. You can find the original code in the DistanceSensor_code file.
