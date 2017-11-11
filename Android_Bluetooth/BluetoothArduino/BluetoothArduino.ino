#include <SoftwareSerial.h>
String message;                 //string that stores the incoming message

SoftwareSerial btSerial(2, 3);      // rx, tx 

void setup()
{
  // use 38400 for programming the AT mode!
  btSerial.begin(9600);
  Serial.begin(9600);
  while (!Serial){
    ;
  }

  String name = "AT+NAME=SahilBT\r\n";            // using AT commands to set name
  btSerial.print("AT\r\n");
  Serial.print("AT\r\n");                         // EN Pin MUST be set to 3.3V and also button pressed until turned on!
  delay(500);                                     // delay between 20ms and 1s required for AT commands

  while(btSerial.available())
    Serial.write(btSerial.read());                // clearing BT buffer

  Serial.print(name);
  btSerial.print(name);
  delay(500);

  while(btSerial.available())
    Serial.write(btSerial.read());

  Serial.print("AT+ADDR\r\n");
  btSerial.print("AT+ADDR\r\n");    // used to see MacAddress of module
  delay(500);
  while(btSerial.available())
    Serial.write(btSerial.read());  //  print address to com port
}

void loop()
{
  delay(10);                                    // delay to let bt buffer fill up a bit
  while(btSerial.available())                   //while there is data available on the serial monitor
  {
    message+=char(btSerial.read());               //store string from serial command
  }
  while(Serial.available()){
    message+=char(Serial.read());
  }
  
  if(message!="")
  {//if data is available
    String s = "This is Bluetooth SahilBT!\r\n";
    btSerial.println(s);                        // send data back to Android device
    Serial.println(s);
    message="";                                 //clear the data
  }
  delay(200); 
}
    
