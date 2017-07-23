# IEEE_Workshops_2017_2018

Code base for the IEEE 2017 to 2018 Workshop year.

# Android + Bluetooth Workshop (Android_Bluetooth folder)

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

