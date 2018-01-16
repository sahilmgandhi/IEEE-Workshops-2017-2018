/*
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN, PB_5 as an output.
  DDRB = DDRB | B00100000;
}

// the loop function runs over and over again forever
void loop() {
  PORTB = B00100000;                 // Turn the LED on
  delay(1000);                       // wait for a second
  PORTB = B00000000;                 // Turn the LED off
  delay(1000);                       // wait for a second
}
*/

// 3 different timers (OC0, OC1, OC2), These must have same frequency, but 2 outputs per
// timer can have different duty cycles. 

void setup(){
//  pinMode(9, OUTPUT);
  DDRB = DDRB | B00000010;
}

void loop(){
  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11) | _BV(WGM10) | _BV(CS12);
  for (int i = 0; i < 255; i++){
    OCR1A = i;  
    delay(5);
  }
  delay(1000);
}

