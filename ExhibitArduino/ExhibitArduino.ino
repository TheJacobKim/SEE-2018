/*
   Filename: ExhibitArduino.ino
   Author: Jacob Kim
   Description: The main file for Wave Exhibit from SEE-2018.
   Date: Sept 11, 2018
*/

#include <wavTrigger.h>
#include <FastLED.h>

// LED strip
#define NUM_LEDS 40
#define LEDSTRIP_PIN 6
CRGB leds[NUM_LEDS];

// Potentiometers
#define MAX A0
#define MIN A1

// Our WAV Trigger object
wavTrigger wTrig;

// Pin nums
int buttonPins[] = {2, 3, 18, 19, 20};
int LEDpins[] = {43, 41, 39, 37, 35};

boolean LEDon = true;

// variable for reading the pushbutton & LED status
volatile byte buttonStates[] = {LOW, LOW, LOW, LOW, LOW};
volatile byte LEDstates[] = {LOW, LOW, LOW, LOW, LOW};

// Keeps track of which button is selected
int buttonNum = -1;
int lastButtonNum = buttonNum;
long debounceDelay = 15;            //Debouncing Time in Milliseconds
volatile unsigned long lastDebounceTime;
int buttonFlag = -1;

// Calculate idle time
long lastTime = millis();
long idleTime = 120000;  // Two minutes in milliseconds
boolean idle = false;

// Potentiometer reading
volatile int minReading;
volatile int maxReading;
volatile int lastMaxReading;
volatile int lastMinReading;

/*
   Function Name: setup()
   Function Prototype: void setup();
   Description: Default function required to initialize Arduino.
                1. Setup Serial connection (9600)
                2. Start WAV Trigger
                3. Set all the tracks to loop forever
                4. Setup button and LED pins
                5. Setup LED strip
                6. Check IDLE
   Parameters: None
   Side Effects: None
   Error Conditions: None
   Return Value: None
*/
void setup() {
  // Serial monitor
  Serial.begin(9600);
  Serial.println("Beginning Exhibit Arduino v1.0");
  Serial.println("------------------------------");
  Serial.println("");


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

  Serial.print("Number of tracks available: ");
  Serial.println(wTrig.getNumTracks());

  // Make sure sound files loop without pause
  for (int i = 1; i <= wTrig.getNumTracks(); i++) {
    wTrig.trackLoop(i, true);
    wTrig.trackPlayPoly(i);
  }

  // Buttons and LEDs
  for (int i = 0; i < 5; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    pinMode(LEDpins[i], OUTPUT);
  }

  // Button interrupt
  attachInterrupt(digitalPinToInterrupt(buttonPins[0]), button0Pressed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buttonPins[1]), button1Pressed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buttonPins[2]), button2Pressed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buttonPins[3]), button3Pressed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buttonPins[4]), button4Pressed, CHANGE);


  digitalWrite(LEDpins[0], HIGH);
  FastLED.addLeds<NEOPIXEL, LEDSTRIP_PIN>(leds, NUM_LEDS);
}

/*
   Function Name: loop()
   Function Prototype: void loop();
   Description: The main driver of this program
   Parameters: None
   Side Effects:
   Error Conditions: None
   Return Value: None
*/
void loop() {
  // Which sounds to play
  minReading = analogRead(MIN);
  maxReading = analogRead(MAX);
  int soundByte = checkPotentiometer(minReading, maxReading); //CHANGE THIS ONCE YOU HAVE THE SECOND POT

  // Call update on the WAV Trigger to keep the track playing status current.
  wTrig.update();

  switch (buttonFlag) {
    case 0:
      Serial.println("button 0 pushed");
      lightLED(0);
      buttonFlag = -1;
      break;
    case 1:
      Serial.println("button 1 pushed");
      lightLED(1);
      buttonFlag = -1;
      break;
    case 2:
      Serial.println("button 2 pushed");
      lightLED(2);
      buttonFlag = -1;
      break;
    case 3:
      Serial.println("button 3 pushed");
      lightLED(3);
      buttonFlag = -1;
      break;
    case 4:
      Serial.println("button 4 pushed");
      lightLED(4);
      buttonFlag = -1;
      break;
  }

  // Play sounds accordingly
  playSound(soundByte);
/*  Serial.print("soundByte: ");
  Serial.println(soundByte);
  Serial.print("buttonNum: ");
  Serial.println(buttonNum);
*/
  // Check result and turn led strip green or red
  checkResult(soundByte);

  //checkIdle();
}
