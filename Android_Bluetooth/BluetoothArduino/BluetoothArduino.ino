#include <SoftwareSerial.h>
#include <Math.h>

// String that stores the incoming message
String message;                 

// 2 (D2) will be used for rx, 3 (D3) will be used for tx 
SoftwareSerial btSerial(2, 3);      

/* 
 * MODIFY THIS VALUE IF YOU WANT TO PROGRAM, OR NOT  
 * 1 represents programming mode, 0 represents in regular connection mode. 
 */
int PROGRAMMING_MODE = 1;
/*
 * END MODIFICATION
 */

void setup()
{
  // Bluetooth Module needs 38400 for programming, 9600 for regular operation. 
  // When programming, you need to connect EN to 3.3V, and press the button on the HC-05

  if (PROGRAMMING_MODE){
    btSerial.begin(38400);
  }
  else{
    btSerial.begin(9600);
  }

  // This is the Arduino Serial Monitor's Baud Rate

  Serial.begin(9600);
  while (!Serial){
    ;
  }

  // using AT commands to set name
  String name = "AT+NAME=SahilBT\r\n";            
  btSerial.print("AT\r\n");
  Serial.print("AT\r\n");                         

  // Delay between 20ms and 1s required between AT commands
  delay(500);                                     

  // Clearing BT buffer
  while(btSerial.available())
    Serial.write(btSerial.read());                

  // Print out the name
  Serial.print(name);
  btSerial.print(name);
  delay(500);

  // Print out what the BlueTooth reads
  while(btSerial.available())
    Serial.write(btSerial.read());                

  // Read the MAC Address of the BlueTooth module if you want to use it in the Android Application
  Serial.print("AT+ADDR\r\n");
  btSerial.print("AT+ADDR\r\n");    
  delay(500);
  while(btSerial.available())
    Serial.print(btSerial.read());  
}

void loop()
{
  // Delay to let BlueTooth buffer fill up a bit
  delay(10);                             

  // While there is data available on the serial monitor read what it has
  while(btSerial.available())                   
  {
    // Store string from serial command
    message+=char(btSerial.read());               
  }
  while(Serial.available()){
    // If you want to add any message from the Arduino Serial Monitor
    message+=char(Serial.read());
  }

  // If data is available, then we want to write that back out
  if(message!="")
  {
    String s = message + " Received" + " Tranmitting back a number: 6";

    // Send data back to Android device
    btSerial.println(s);                        
    Serial.println(s);

    // Clear the data
    message="";                                 
  }

  delay(200); 
}

