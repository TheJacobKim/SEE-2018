/*
   Function Name: checkResult()
   Function Prototype: void checkResult(int soundByte);
   Description: Check if the user isolated a sound correctly
   Parameters: soundByte - tells which sound is being played
   Side Effects: LEDs arary status will change
   Error Conditions: None
   Return Value: None
*/

void checkResult(int soundByte) {

  // If idle turn off the LED
  if (idle) {
    if ( LEDon ) {
      Serial.println("LED Off");
      for ( int i = 0; i < NUM_LEDS; i++ ) {
        leds[i] = CRGB::Black;
      }
      LEDon = false;
    }
  }

  // If not idle turn on the LED accordingly
  else {
    // User narrowed down the frequency.
    if (soundByte == buttonNumPow) {
      if ( !LEDon || LEDRed ) {
        Serial.println("LED to Green");
        for ( int i = 0; i < NUM_LEDS; i++ )
          leds[i] = CRGB::Green;
        LEDon = true;
        LEDRed = false;
      }
      delay(500);
    }

    // User didn't narrow down frequency
    else {
      if (!LEDon || !LEDRed ) {
        Serial.println("LED to Red");
        for ( int i = 0; i < NUM_LEDS; i++ )
          leds[i] = CRGB::Red;
        LEDon = true;
        LEDRed = true;
      }
    }
  }
  FastLED.show();
}
