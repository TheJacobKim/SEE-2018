/*
   Filename: checkPotentiometer.ino
   Author: Jacob Kim
   Description: This file checks potentiometer values and returns soundByte which
                determines which sound to play.
   Date: Sept 11, 2018
*/

/*
   Function Name: checkPotentiometer()
   Function Prototype: int checkPotentiometer(int minVal, int maxVal);
   Description: This function recieves min and max. Then creates soundByte accordingly.
                If min is larger than max, soundByte is always zero.
                0 0 0 0 0
                If min and max is in the range of first section (lowest frequency),
                add one to soundByte
                0 0 0 0 1
                If min and max is in the range of secoond section (2nd lowest frequency),
                add one to soundByte
                0 0 0 1 1
                and so on...

   Parameters: minVal - minimum value from potentiometer.
               maxVal - maximum value from potentiometer.
   Side Effects: None
   Error Conditions: None
   Return Value: soundByte
*/
int checkPotentiometer(int minVal, int maxVal) {
  /*Serial.println("----PRE MAP-----");
  Serial.print("MIN POT: ");
  Serial.println(minVal);
  Serial.print("MAX POT: ");
  Serial.println(maxVal);*/
  minVal = map(minVal, minLowerBound, minUpperBound, 0, 1024);
  maxVal = map(maxVal, maxLowerBound, maxUpperBound, 0, 1024);
  int localSoundByte = 0;

  if (minVal < maxVal) {
    // Check if the min and max are in range
    if (minVal < 204)
      localSoundByte += 1;
    if (minVal < 409 && maxVal >= 204)
      localSoundByte += 2;
    if (minVal < 612 && maxVal >= 409)
      localSoundByte += 4;
    if (minVal < 816 && maxVal >= 612)
      localSoundByte += 8;
    if (maxVal > 816)
      localSoundByte += 16;
  }
  /*
  Serial.println("----Post MAP-----");
  Serial.print("MIN POT: ");
  Serial.println(minVal);
  Serial.print("MAX POT: ");
  Serial.println(maxVal);*/
  return localSoundByte;
}
