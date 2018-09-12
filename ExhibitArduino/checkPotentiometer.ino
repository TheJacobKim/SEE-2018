/*
 * Filename: checkPotentiometer.ino
 * Author: Jacob Kim
 * Description: This file checks potentiometer values and returns soundByte which 
 *              determines which sound to play.
 * Date: Sept 11, 2018
 */
 
/*
 * Function Name: checkPotentiometer()
 * Function Prototype: int checkPotentiometer(int minVal, int maxVal);
 * Description: This function recieves min and max. Then creates soundByte accordingly.
 *              If min is larger than max, soundByte is always zero.
 *              0 0 0 0 0
 *              If min and max is in the range of first section (lowest frequency), 
 *              add one to soundByte
 *              0 0 0 0 1
 *              If min and max is in the range of secoond section (2nd lowest frequency), 
 *              add one to soundByte
 *              0 0 0 1 1
 *              and so on...
 *              
 * Parameters: minVal - minimum value from potentiometer.
 *             maxVal - maximum value from potentiometer.
 * Side Effects: None
 * Error Conditions: None
 * Return Value: soundByte
 */
int checkPotentiometer(int minVal, int maxVal) {
  int soundByte = 0;
  if (minVal < maxVal) {
    // Check if the min and max are in range
    if (minVal < 128 && maxVal >= 128)
      soundByte += 1;
    if (minVal < 396 && maxVal >= 396)
      soundByte += 2;
    if (minVal < 518 && maxVal >= 518)
      soundByte += 4;
    if (minVal < 945 && maxVal >= 945)
      soundByte += 8;
    if (maxVal > 945)
      soundByte += 16;
  }
  return soundByte;
}


