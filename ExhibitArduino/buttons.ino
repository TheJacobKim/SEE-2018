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
  if (this_time - last_time0 > 100) {
    buttonFlag = 0;
  }
  last_time0 = this_time;
}
void button1Pressed() {
  //software debounce
  static unsigned long last_time1 = 0;
  unsigned long this_time = millis();
  if (this_time - last_time1 > 100) {
    buttonFlag = 1;
  }
  last_time1 = this_time;
}
void button2Pressed() {
  //software debounce
  static unsigned long last_time2 = 0;
  unsigned long this_time = millis();
  if (this_time - last_time2 > 100) {
    buttonFlag = 2;
  }
  last_time2 = this_time;
}
void button3Pressed() {
  //software debounce
  static unsigned long last_time3 = 0;
  unsigned long this_time = millis();
  if (this_time - last_time3 > 100) {
    buttonFlag = 3;
  }
  last_time3 = this_time;
}
void button4Pressed() {
  //software debounce
  static unsigned long last_time4 = 0;
  unsigned long this_time = millis();
  if (this_time - last_time4 > 100) {
    buttonFlag = 4;
  }
  last_time4 = this_time;
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
  if (idle) {
    for (int i = 0; i < 5; i++) {
      digitalWrite(LEDpins[i], LOW);
      delay(1);
    }
  } 
  
  else {
    Serial.print("LIGHT UP ");
    Serial.println(ledPin);

    for (int n = 0; n < 5; n++) {
      LEDstates[n] = LOW;
    }
    LEDstates[ledPin] = HIGH;

    for (int i = 0; i < 5; i++) {
      digitalWrite(LEDpins[i], LEDstates[i]);
      delay(1);
    }
  }
}
