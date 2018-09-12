#include <Metro.h>
#include <wavTrigger.h>
#include <FastLED.h>


void playSound(int soundByte) {
  if ((soundByte & 1) == 1 && wave0.volume == 0)           wave0.volume = 50; // I could not find default volume level, so I set it to this arbitrary number 50.
  else if ((soundByte & 1) == 1 && wave0.volume == 50)     wave0.volume = 0;

  if ((soundByte & 2) == 2 && wave1.volume == 0)           wave1.volume = 50;
  else if ((soundByte & 2) == 2 && wave1.volume == 50)     wave1.volume = 0;

  if ((soundByte & 4) == 4 && wave2.volume == 0)          wave2.volume = 50;
  else if ((soundByte & 4) == 4 && wave2.volume == 50)     wave2.volume = 0;

  if ((soundByte & 8) == 8 && wave3.volume == 0)           wave3.volume = 50;
  else if ((soundByte & 8) == 8 && wave3.volume == 50)     wave3.volume = 0;

  if ((soundByte & 16) == 16 && wave4.volume == 0)          wave4.volume = 50;
  else if ((soundByte & 16) == 16 && wave4.volume == 50)    wave4.volume = 0;

  // If a specific section is selected, mute other noise
  if (soundByte == 0 || soundByte == 1 || soundByte == 2 || soundByte == 4 || soundByte == 8 || soundByte == 16) {
    wave5.volume = 50;
    wave6.volume = 50;
    wave7.volume = 50;
  } else {
    wave5.volume = 0;
    wave6.volume = 0;
    wave7.volume = 0;
  }

}

