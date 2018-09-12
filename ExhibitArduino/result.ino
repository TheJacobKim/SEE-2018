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
  Serial.print("Sound Byte: ");
  Serial.println(soundByte);
  Serial.print("Button Number: ");
  Serial.println(buttonNum);
  if (soundByte == buttonNum) {
    if(!LEDon)
    {
      Serial.println("LED to Green");
      for ( int i = 0; i < NUM_LEDS; i++ ) {
        leds[i] = CRGB::Green;
      }    
      FastLED.show();
      delay(500);
      LEDon = true;
    }
  } else {
    if(LEDon)
    {
      Serial.print("LED to Red");
      for ( int i = 0; i < NUM_LEDS; i++ ) {
        leds[i] = CRGB::Red;
      }  
      FastLED.show();
      LEDon = false;  
    }
  }
}
