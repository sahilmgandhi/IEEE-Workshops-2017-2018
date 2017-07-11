# IEE_Workshops_2017_2018

Code base for the IEEE 2017 to 2018 Workshop year.

# Instructions to Use:

1. Bluetooth -> Arduino

For the AT-commands for the HC-05 Bluetooth Module, start both the BluetoothSerial and regular
Serial Monitor at a baud rate of 38400. Additionally, the EN pin must be set to HIGH (attach it
to the 3.3V line for the Arduino Nano), and the button on the HC-05 must be pressed as well while 
powering the device. Once the device is on, the button can be released, and the AT-commands will go through. 

After the AT-commands of choice have been coded, change the Baud rate of both Serial modes to 9600
for normal interaction with your Android application.

For other bluetooth modules, the Baud rate for the AT-mode and regular use mode might be different, 
and there may be other modes (not AT) to program the bluetooth module.

2. 