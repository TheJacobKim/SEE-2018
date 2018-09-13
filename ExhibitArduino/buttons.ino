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
  if ((long)(millis() - last_millis) >= debouncing_time) {
    last_millis = millis();
    Serial.println("Button 0 is changed");
    lightLED(LEDpins[0]);
  }
}
void button1Pressed() {
  if ((long)(millis() - last_millis) >= debouncing_time) {
    last_millis = millis();
    Serial.println("Button 1 is changed");
    lightLED(LEDpins[1]);
  }
}
void button2Pressed() {
  if ((long)(millis() - last_millis) >= debouncing_time) {
    last_millis = millis();
    Serial.println("Button 2 is changed");
    lightLED(LEDpins[2]);
  }
}
void button3Pressed() {
  if ((long)(millis() - last_millis) >= debouncing_time) {
    last_millis = millis();
    Serial.println("millis 3 is changed");
    lightLED(LEDpins[3]);
  }
}
void button4Pressed() {
  if ((long)(millis() - last_millis) >= debouncing_time) {
    last_millis = millis();
    Serial.println("Button 4 is changed");
    lightLED(LEDpins[4]);
  }
}


/*
   Function Name: testButtonState()
   Function Prototype: boolean testButtonState(int buttonPin, int buttonStateN, byte buttonNewState);
   Description: Check button states and lights up correct LED.
   Parameters: buttonPin - button pin to check
               buttonStateN -
               buttonNewState -
   Side Effects: buttonStates[] array value changes accordingly
   Error Conditions: None
   Return Value: boolean value to determine if a button's state has been changed.
*/
boolean testButtonState(int buttonPin, int buttonStateN, byte buttonNewState) {
  if (buttonStates[buttonStateN] != buttonNewState) {
    Serial.print(buttonPin);
    Serial.println(" is changed");
    buttonStates[buttonStateN] = buttonNewState;
    if (buttonNewState == LOW) {
      Serial.print(buttonPin);
      Serial.println(" is up");
      return true;
    }
  }
  return false;
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
    LEDstates[n] = LOW;
  }
  LEDstates[ledPin] = HIGH;

  for (int i = 0; i < 5; i++) {
    digitalWrite(LEDpins[i], LEDstates[i]);
  }
}
