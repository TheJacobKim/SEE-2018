#include <Metro.h>
#include <wavTrigger.h>
#include <FastLED.h>

// LED strip
#define NUM_LEDS 23
#define LEDSTRIP_PIN 6
CRGB leds[NUM_LEDS];

//This is the pin where the cord is connected to
#define MAX A0                    // Upper potentiometer
#define MIN A1                    // Lower potentiometer

wavTrigger wTrig;                 // Our WAV Trigger object

// Pin nums
int buttonPins[] = {2, 3, 4, 5, 6};
byte buttonStates[] = {LOW, LOW, LOW, LOW, LOW};
byte LEDstates[] = {LOW, LOW, LOW, LOW, LOW};
int LEDpins[] = {7, 8, 9, 10, 11};

// Which button is selected
int buttonNum;

void setup() {
  
  // Serial monitor
  Serial.begin(9600);

  // If the Arduino is powering the WAV Trigger, we should wait for the WAV
  //  Trigger to finish reset before trying to send commands.
  delay(1000);

  // WAV Trigger startup at 57600
  wTrig.start();
  delay(10);

  // Send a stop-all command and reset the sample-rate offset, in case we have
  //  reset while the WAV Trigger was already playing.
  wTrig.stopAllTracks();
  wTrig.samplerateOffset(0);

  // Make sure sound files loop without pause
  for (int i = 1; i <= 8; i++) {
    wTrig.tackLoop(i, true);
  }

  // Buttons and LEDs
  for (int i = 0; i < 5; i++) {
    pinMode(buttonPins[i], INPUT);
    pinMode(LEDpins[i], OUTPUT);
  }

  FastLED.addLeds<NEOPIXEL, LEDSTRIP_PIN>(leds, NUM_LEDS);
}

void loop() {
  // Which sounds to play
  int soundByte = checkPotentiometer(analogRead(MIN), analogRead(MAX));

  // Call update on the WAV Trigger to keep the track playing status current.
  wTrig.update();

  // Figure out button states
  for (int i = 0; i < 5; i++) {
    if (testButtonState(buttonPins[i], i, digitalRead(buttonPins[i]))) {
      lightLED(i);
      buttonNum = pow(2, i); // This is used to determine if the user isolated to the correct sound.
    }
  }

  // Play sounds accordingly
  playSound(soundByte);


}


// Test which button is pressed
boolean testButtonState(int buttonPin, int buttonStateN, byte buttonNewState) {
  if (buttonStates[buttonStateN] != buttonNewState) {
    Serial.print(buttonPin);
    Serial.println(" is changed");
    buttonStates[buttonStateN] = buttonNewState;
    if (buttonNewState == LOW) {
      Serial.print(buttonPin);
      Serial.println(" is up");
      return true;
    }
  }
  return false;
}

// Light up LEDs according to that
void lightLED(int ledPin) {
  for (int n = 0; n < 5; n++) {
    LEDstates[n] = LOW;
  }
  LEDstates[ledPin] = HIGH;

  for (int i = 0; i < 5; i++) {
    digitalWrite(LEDpins[i], LEDstates[i]);
  }
}


