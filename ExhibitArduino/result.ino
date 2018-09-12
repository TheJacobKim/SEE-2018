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
  if (soundByte == buttonNum) {
    for ( int i = 0; i < NUM_LEDS; i++ ) {
      leds[i] = CRGB::Green;
      FastLED.show();
      delay(500);
    }
  } else {
    for ( int i = 0; i < NUM_LEDS; i++ ) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
  }
}
