#include <FastLED.h>

// LED strip
#define NUM_LEDS 23
#define LEDSTRIP_PIN 6

CRGB leds[NUM_LEDS];

//This is the pin where the cord is connected to
#define MAX 0                    // Upper potentiometer
#define MIN 1                    // Lower potentiometer


// Pin nums
int buttonPins[] = {2, 3, 4, 5, 6};
byte buttonStates[] = {LOW, LOW, LOW, LOW, LOW};
byte LEDstates[] = {LOW, LOW, LOW, LOW, LOW};
int LEDpins[] = {7, 8, 9, 10, 11};

const int GreenLEDPin = 12;
const int RedLEDPin = 13;

// Which button is selected
int buttonNum;

void setup(void) {

  Serial.begin(9600);

  // Buttons and LEDs
  for (int i = 0; i < 5; i++) {
    pinMode(buttonPins[i], INPUT);
    pinMode(LEDpins[i], OUTPUT);
  }

  FastLED.addLeds<NEOPIXEL, LEDSTRIP_PIN>(leds, NUM_LEDS);
}

void loop(void) {
  unsigned long currentMillis = millis();
  int i;

  // Potentiometer readings
  int minVal = analogRead(MIN);           //Read upper potentiometer value
  int maxVal = analogRead(MAX);             //Read lower potentiometer value


  for (int i = 0; i < 5; i++) {
    if (testButtonState(buttonPins[i], i, digitalRead(buttonPins[i]))) {
      lightLED(i);
      buttonNum = pow(2,i); // This is used to determine if the user isolated to the correct sound.
    }
  }

  /*
    Serial.print("buttonNum: ");
    Serial.println(buttonNum);
    delay(2000);
  */

  // Which sounds to play
  int soundByte = 0;
  if (minVal < maxVal) { // This does not represent current proportions
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

  // Play the sound with Processing
  Serial.println(soundByte);

  // Check if the user got it right by LED strip
  if (soundByte == buttonNum) {
    for ( i = 0; i < NUM_LEDS; i++ ) {
      leds[i] = CRGB::Green;
      FastLED.show();
      delay(300);
    }
  } else {
    for ( i = 0; i < NUM_LEDS; i++ ) {
      leds[i] = CRGB::Red;
      FastLED.show();
      delay(10);
    }
  }
}

// Test which button is pressed
boolean testButtonState(int buttonPin, int buttonStateN, byte buttonNewState) {
  if (buttonStates[buttonStateN] != buttonNewState) {
    buttonStates[buttonStateN] = buttonNewState;
    Serial.print(buttonPin);
    Serial.println(" pressed.");
    if (buttonNewState == LOW) {
      Serial.print(buttonPin);
      Serial.println(" up.");
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


