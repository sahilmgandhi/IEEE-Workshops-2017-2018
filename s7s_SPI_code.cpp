#include <SPI.h> // Include the Arduino SPI library

// Define the SS pin. This is the only pin we can move around to any available digital pin.
const int ssPin = 8;

unsigned int counter = 0;  // This variable will count up to 65k
char tempString[10];  // Will be used with sprintf to create strings

void setup()
{
    // -------- SPI initialization
    pinMode(ssPin, OUTPUT);  // Set the SS pin as an output
    digitalWrite(ssPin, HIGH);  // Set the SS pin HIGH
    SPI.begin();  // Begin SPI hardware
    SPI.setClockDivider(SPI_CLOCK_DIV64);  // Slow down SPI clock
    // --------
    
    // Clear the display, and then turn on all segments and decimals
    clearDisplaySPI();  // Clears display, resets cursor
    
    // Custom function to send four bytes via SPI
    //  The SPI.transfer function only allows sending of a single
    //  byte at a time.
    s7sSendStringSPI("-HI-");
    setDecimalsSPI(0b111111);  // Turn on all decimals, colon, apos
    
    // Flash brightness values at the beginning
    setBrightnessSPI(0);  // Lowest brightness
    delay(1500);
    setBrightnessSPI(255);  // High brightness
    delay(1500);
    
    // Clear the display before jumping into loop
    clearDisplaySPI();
}

void loop()
{
    // Magical sprintf creates a string for us to send to the s7s.
    //  The %4d option creates a 4-digit integer.
    sprintf(tempString, "%4d", counter);
    
    // This will output the tempString to the S7S
    s7sSendStringSPI(tempString);
    
    // Print the decimal at the proper spot
    if (counter < 10000)
        setDecimalsSPI(0b00000010);  // Sets digit 3 decimal on
    else
        setDecimalsSPI(0b00000100);
    
    counter++;  // Increment the counter
    delay(10);  // This will make the display update at 100Hz.*/
}

// This custom function works somewhat like a serial.print.
//  You can send it an array of chars (string) and it'll print
//  the first 4 characters in the array.
void s7sSendStringSPI(String toSend)
{
    digitalWrite(ssPin, LOW);
    for (int i=0; i<4; i++)
    {
        SPI.transfer(toSend[i]);
    }
    digitalWrite(ssPin, HIGH);
}

// Send the clear display command (0x76)
//  This will clear the display and reset the cursor to left-most digit
void clearDisplaySPI()
{
    digitalWrite(ssPin, LOW);
    SPI.transfer(0x76);  // Clear display command
    digitalWrite(ssPin, HIGH);
}

// Set the displays brightness. Should receive byte with the value
//  to set the brightness to
//  dimmest------------->brightest
//     0--------127--------255
void setBrightnessSPI(byte value)
{
    digitalWrite(ssPin, LOW);
    SPI.transfer(0x7A);  // Set brightness command byte
    SPI.transfer(value);  // brightness data byte
    digitalWrite(ssPin, HIGH);
}

// Turn on any, none, or all of the decimals.
//  The six lowest bits in the decimals parameter sets a decimal
//  (or colon, or apostrophe) on or off. A 1 indicates on, 0 off.
//  [MSB] (X)(X)(Apos)(Colon)(Digit 4)(Digit 3)(Digit2)(Digit1)
void setDecimalsSPI(byte decimals)
{
    digitalWrite(ssPin, LOW);
    SPI.transfer(0x77);
    SPI.transfer(decimals);
    digitalWrite(ssPin, HIGH);
}
