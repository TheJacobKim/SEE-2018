
/*
   Function Name: checkIdle()
   Function Prototype: void checkIdle();
   Description: This function checks if there was any input for 2 minutes.
                If not, setup idle flag.
   Parameters: None
   Side Effects: None
   Error Conditions: None
   Return Value: None
*/

void checkIdle() {
  if ( abs(lastMaxReading - maxReading) < 5 && abs(lastMinReading - minReading) < 5 &&
       (lastbuttonNumPow == buttonNumPow) ) {
    if ( millis() - lastTime > idleTime ) {
      Serial.println("Now Idle");
      idle = true;
    }
  } else {
    lastTime = millis();
    lastbuttonNumPow = buttonNumPow;
    lastMaxReading = maxReading;
    lastMinReading = minReading;
    if (idle == true) {
      int myRand = random(0, 5);
      buttonNumPow = pow(2, myRand);
      lightLED(myRand);
    }
    idle = false;
  }
}
