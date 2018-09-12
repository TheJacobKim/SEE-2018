/*
 * Filename: ExhibitArduino.ino
 * Author: Jacob Kim
 * Description: The main file for Wave Exhibit from SEE-2018.
 * Date: Sept 11, 2018
 */

#include <Metro.h>
#include <wavTrigger.h>
#include <FastLED.h>

// LED strip
#define NUM_LEDS 23
#define LEDSTRIP_PIN 6
CRGB leds[NUM_LEDS];

// Potentiometers
#define MAX A0
#define MIN A1

// Our WAV Trigger object
wavTrigger wTrig;      
           
// Pin nums
int buttonPins[] = {2, 3, 4, 5, 6};
int LEDpins[] = {7, 8, 9, 10, 11};

// variable for reading the pushbutton & LED status
volatile byte buttonStates[] = {LOW, LOW, LOW, LOW, LOW};
volatile byte LEDstates[] = {LOW, LOW, LOW, LOW, LOW};

// Keeps track of which button is selected
int buttonNum;

/*
 * Function Name: setup()
 * Function Prototype: void setup();
 * Description: Default function required to initialize Arduino.
 *              1. Setup Serial connection (9600)
 *              2. Start WAV Trigger
 *              3. Set all the tracks to loop forever
 *              4. Setup button and LED pins
 *              5. Setup LED strip
 * Parameters: None
 * Side Effects: None
 * Error Conditions: None
 * Return Value: None
 */
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
    wTrig.trackLoop(i, true);
    wTrig.trackPlayPoly(i);
  }
  
  // Buttons and LEDs
  for (int i = 0; i < 5; i++) {
    pinMode(buttonPins[i], INPUT);

    // Attach interrupts() for the button pins' accuracy.
    attachInterrupt(digitalPinToInterrupt(buttonPins[i]), buttonPressed, CHANGE);
    
    pinMode(LEDpins[i], OUTPUT);
  }

  FastLED.addLeds<NEOPIXEL, LEDSTRIP_PIN>(leds, NUM_LEDS);
}

/*
 * Function Name: loop()
 * Function Prototype: void loop();
 * Description: The main driver of this program
 * Parameters: None
 * Side Effects: 
 * Error Conditions: None
 * Return Value: None
 */
void loop() {
  // Which sounds to play
  int soundByte = checkPotentiometer(analogRead(MIN), analogRead(MAX));

  // Call update on the WAV Trigger to keep the track playing status current.
  wTrig.update();

  // Play sounds accordingly
  playSound(soundByte);
}



