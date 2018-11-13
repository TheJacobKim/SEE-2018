
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
  /*
     If both both potentiometer and buttons were not touched for
     certain amount of time, it is idle
  */
  if ( abs(lastMaxReading - maxReading) < 10 && abs(lastMinReading - minReading) < 10 ) {
    if ( millis() - lastTime > idleTime ) {
      Serial.println("Idle");
      idle = true;
    }
  }

  else {
    Serial.println("Not Idle");
    lastTime = millis();
    lastbuttonNumPow = buttonNumPow;
    lastMaxReading = maxReading;
    lastMinReading = minReading;
    idle = false;
  }
}
