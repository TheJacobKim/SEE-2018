/*
   Filename: buttons.ino
   Author: Jacob Kim
   Description: This file checks buttons from interrupts() and toggles correct LED.
   Date: Sept 12, 2018
*/


/*
   Function Name: button#Pressed()
   Function Prototype: void button#Pressed();
   Description: This function is part of interrupts() in Arduino.
                If any buttons' state change, this function gets called.
   Parameters: None
   Side Effects: None
   Error Conditions: None
   Return Value: None
*/
void button0Pressed() {
  //software debounce
  static unsigned long last_time0 = 0;
  unsigned long this_time = millis();
  if (this_time - last_time0 > debounceDelay) {
    buttonFlag = 0;
  }
  last_time0 = this_time;
  idle = false;
  lastTime = millis();
}
void button1Pressed() {
  //software debounce
  static unsigned long last_time1 = 0;
  unsigned long this_time = millis();
  if (this_time - last_time1 > debounceDelay) {
    buttonFlag = 1;
  }
  last_time1 = this_time;
  idle = false;
  lastTime = millis();
}
void button2Pressed() {
  //software debounce
  static unsigned long last_time2 = 0;
  unsigned long this_time = millis();
  if (this_time - last_time2 > debounceDelay) {
    buttonFlag = 2;
  }
  last_time2 = this_time;
  idle = false;
  lastTime = millis();
}
void button3Pressed() {
  //software debounce
  static unsigned long last_time3 = 0;
  unsigned long this_time = millis();
  if (this_time - last_time3 > debounceDelay) {
    buttonFlag = 3;
  }
  last_time3 = this_time;
  idle = false;
  lastTime = millis();
}
void button4Pressed() {
  //software debounce
  static unsigned long last_time4 = 0;
  unsigned long this_time = millis();
  if (this_time - last_time4 > debounceDelay) {
    buttonFlag = 4;
  }
  last_time4 = this_time;
  idle = false;
  lastTime = millis();
}

/*
   Function Name: lightLED()
   Function Prototype: void lightLED(int ledPin);
   Description: Toggle LEDs according to its parameter.
   Parameters: ledPin - pin number to light up.
   Error Conditions: None
   Return Value: None
*/
void lightLED(int ledPin) {
  Serial.print("LIGHT UP ");
  Serial.println(ledPin + 1);

  for (int n = 0; n < 5; n++) {
    LEDstates[n] = HIGH;
  }
  LEDstates[ledPin] = LOW;

  for (int i = 0; i < 5; i++) {
    digitalWrite(LEDpins[i], LEDstates[i]);
    delay(1);
  }
}
