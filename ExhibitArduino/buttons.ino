/*
   Filename: buttons.ino
   Author: Jacob Kim
   Description: This file checks buttons from interrupts() and toggles correct LED.
   Date: Sept 12, 2018
*/


/*
   Function Name: buttonPressed()
   Function Prototype: void buttonPressed();
   Description: This function is part of interrupts() in Arduino.
                If any buttons' state change, this function gets called.
   Parameters: None
   Side Effects: None
   Error Conditions: None
   Return Value: None
*/
void buttonPressed() {
  // Figure out button states
  for (int i = 0; i < 5; i++) {
    if (testButtonState(buttonPins[i], i, digitalRead(buttonPins[i]))) {
      lightLED(i);
      buttonNum = pow(2, i); // This is used to determine if the user isolated to the correct sound.
    }
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
  for (int n = 0; n < 5; n++) {
    LEDstates[n] = LOW;
  }
  LEDstates[ledPin] = HIGH;

  for (int i = 0; i < 5; i++) {
    digitalWrite(LEDpins[i], LEDstates[i]);
  }
}
