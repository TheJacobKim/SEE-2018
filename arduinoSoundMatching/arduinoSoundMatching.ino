#include <ArduinoJson.h>

//This is the pin where the cord is connected to
#define MAX 0                    // Upper potentiometer
#define MIN 1                    // Lower potentiometer


// Pin nums
const int buttonPin0 = 0;
const int buttonPin1 = 1;
const int buttonPin2 = 2;
const int buttonPin3 = 3;
const int buttonPin4 = 4;

const int LEDPin0 = 5;
const int LEDPin1 = 6;
const int LEDPin2 = 7;
const int LEDPin3 = 8;
const int LEDPin4 = 9;

const int GreenLEDPin = 10;
const int RedLEDPin = 11;

// Button states
int buttonReading0;               // the current reading from the input pin0
int buttonReading1;               // the current reading from the input pin1
int buttonReading2;               // the current reading from the input pin2
int buttonReading3;               // the current reading from the input pin3

// LED states
int LEDState0 = LOW;
int LEDState1 = LOW;
int LEDState2 = LOW;
int LEDState3 = LOW;

// Time vars
const long interval = 12000;      // interval for a round
unsigned long previousMillis = 0; // will store last a new round started

// Random freq
int randFreq = 350;

// Which button is selected
int buttonNum;

void setup(void) {
  Serial.begin(9600);

  // Buttons
  pinMode(buttonPin0, INPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);

  // LED
  pinMode(LEDPin0, OUTPUT);
  pinMode(LEDPin1, OUTPUT);
  pinMode(LEDPin2, OUTPUT);
  pinMode(LEDPin3, OUTPUT);
  pinMode(LEDPin4, OUTPUT);

  pinMode(GreenLEDPin, OUTPUT);
  pinMode(RedLEDPin, OUTPUT);

  randomSeed(analogRead(0));
}

void loop(void) {
  unsigned long currentMillis = millis();

  // Potentiometer readings
  int minVal = analogRead(MIN);             //Read upper potentiometer value
  int maxVal = analogRead(MAX);             //Read lower potentiometer value

  // Button readings  EDGE CASE: people pressing multiple button together
  if (digitalRead(buttonPin0) == HIGH)
    buttonNum = 16;
  else if (digitalRead(buttonPin1) == HIGH)
    buttonNum = 8;
  else if (digitalRead(buttonPin2) == HIGH)
    buttonNum = 4;
  else if (digitalRead(buttonPin3) == HIGH)
    buttonNum = 2;
  else if (digitalRead(buttonPin3) == HIGH)
    buttonNum = 1;

  // LED states
  digitalWrite(LEDPin0, LEDState0);
  digitalWrite(LEDPin1, LEDState1);
  digitalWrite(LEDPin2, LEDState2);
  digitalWrite(LEDPin3, LEDState3);

  // Start game THIS DOES NOT WORK WELL
  switch (buttonNum) {
    case 16:
      digitalWrite(LEDPin0, HIGH);
      break;
    case 8:
      digitalWrite(LEDPin1, HIGH);
      break;
    case 4:
      digitalWrite(LEDPin2, HIGH);
      break;
    case 2:
      digitalWrite(LEDPin3, HIGH);
      break;
    case 1:
      digitalWrite(LEDPin4, HIGH);
      break;
    default:
      // Button is not pressed
      for (int thisPin = 0; thisPin < 4; thisPin++) {
        digitalWrite(thisPin, LOW);
      }
  }

  // Which sounds to play
  int soundByte = 0;
  if (minVal < maxVal) {
    // Check if the min and max are in range
    if (minVal < 205)
      soundByte += 1;
    if (minVal <= 410 && maxVal >= 410)
      soundByte += 2;
    if (minVal <= 615 && maxVal >= 615)
      soundByte += 4;
    if (minVal <= 820 && maxVal >= 820)
      soundByte += 8;
    if (maxVal > 820)
      soundByte += 16;
  }

  // Play the sound with Processing
  Serial.println(soundByte);

  // Check if the user got it right
  /*int soundInt = soundByte;
  if (soundByte == buttonNum) {
    digitalWrite(GreenLEDPin, HIGH);
    delay(4000);
  }*/
}
