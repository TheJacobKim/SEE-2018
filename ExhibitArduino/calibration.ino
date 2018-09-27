/*
   Filename: calibration.ino
   Author: J. DeWald
   Description: This file calibrates the upper and lower bounds of the potentiometers
   Date: Sept 26, 2018
*/


/*
   Function Name: calibratePots()
   Function Prototype: int calibratePots(int potIdentity);
   Description: This function calibrates potentiometer.
   Parameters: None
   Side Effects: None
   Error Conditions: None
   Return Value: potReading
*/

int calibratePots(int potIdentity) {
  int potReading;
  Serial.println("Waiting for Button Press");
  while (!calButtonFlag) {
    digitalWrite(LEDpins[0], HIGH);
    delay(250);
    digitalWrite(LEDpins[0], LOW);
    delay(250);
  }
  switch (potIdentity) {
    case 1:
      Serial.println("Setting Min Lower Bound");
      analogRead(MIN);
      delay(1);
      potReading = analogRead(MIN);
      break;
    case 2:
      Serial.println("Setting Min Upper Bound");
      analogRead(MIN);
      delay(1);
      potReading = analogRead(MIN);
      break;
    case 3:
      Serial.println("Setting Max Lower Bound");
      analogRead(MAX);
      delay(1);
      potReading = analogRead(MAX);
      break;
    case 4:
      Serial.println("Setting MAX Lower Bound");
      analogRead(MAX);
      delay(1);
      potReading = analogRead(MAX);
      break;
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(LEDpins[0], HIGH);
    delay(100);
    digitalWrite(LEDpins[0], LOW);
    delay(100);
  }
  calButtonFlag = false;
  return potReading;
}

void calButtonPressed() {
  //software debounce
  static unsigned long last_time0 = 0;
  unsigned long this_time = millis();
  if (this_time - last_time0 > debounceDelay) {
    calButtonFlag = true;
  }
  last_time0 = this_time;
}
