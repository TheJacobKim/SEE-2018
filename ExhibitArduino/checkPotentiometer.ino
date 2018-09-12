//
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


