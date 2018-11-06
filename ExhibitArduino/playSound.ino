/*
   Filename: playSound.ino
   Author: Jacob Kim
   Description: This file is used to play correct sounds according to its param.
   Date: Sept 11, 2018
*/

/*
   Function Name: playSound()
   Function Prototype: void playSound( int soundByte );
   Description: Once function recieves soundByte, it checks which sound to play. Uses bitwise AND function to
                determine if certain sound should be played or not. Then it checks if the user isolated to only
                one sound. If the user isolated to only one sound, mute all the background noises.
   Parameters: soundByte - integer that represents which sound should be played.
   Side Effects: Tracks' gain(dB) will change.
   Error Conditions: None
   Return Value: None
*/
void playSound(int soundByte) {
  /*
      The range for gain is -70 to +10. A value of 0 (no gain) plays the track at the nominal value in the wav file.
      This is the default gain for every track until changed. A value of -70 is completely muted.
  */

  // Don't play anything if idle
  if (idle) {
    wTrig.trackGain(1, -70);
    wTrig.trackGain(2, -70);
    wTrig.trackGain(3, -70);
    wTrig.trackGain(4, -70);
    wTrig.trackGain(5, -70);
    wTrig.trackGain(6, -70);
    wTrig.trackGain(7, -70);
    wTrig.trackGain(8, -70);
  } 

  // Play sound if it is not idle
  else {
    for ( int i = 1; i <= 5; i++ ) {
      if ( ( soundByte & (int)ceil(pow(2, i - 1)) ) == (int)ceil(pow(2, i - 1)) ) {
        wTrig.trackGain(i, MAXVOLUMEFISH);
        /*
          Serial.print("soundByte: ");
          Serial.println(soundByte);
          Serial.print("buttonNumPow: ");
          Serial.println(buttonNumPow);
          Serial.print("Track Playing: ");
          Serial.println(i);
        */
      }
      else {
        wTrig.trackGain(i, -70);
      }
    }

    // If a specific section is selected, mute background noises
    if (soundByte == 0 || soundByte == 1 || soundByte == 2 || soundByte == 4 || soundByte == 8 || soundByte == 16) {
      wTrig.trackGain(6, -70);
      wTrig.trackGain(7, -70);
      wTrig.trackGain(8, -70);
    } else {
      wTrig.trackGain(6, MAXVOLUMEBG);
      wTrig.trackGain(7, MAXVOLUMEBG);
      wTrig.trackGain(8, MAXVOLUMEBG);
    }
  }
}
