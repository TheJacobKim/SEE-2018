#include <ArduinoJson.h>

//This is the pin where the cord is connected to
#define MAX A0                    // Upper potentiometer
#define MIN A1                    // Lower potentiometer


// Pin nums
const int buttonPin0 = 0;
const int buttonPin1 = 1;
const int buttonPin2 = 2;
const int buttonPin3 = 3;
const int LEDPin0 = 4;
const int LEDPin1 = 5;
const int LEDPin2 = 6;
const int LEDPin3 = 7;
const int GreenLEDPin = 8;
const int RedLEDPin = 9;

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

// Input from potentiometer
int maxVal;
int minVal;

// Which button is selected
int buttonNum;

void setup(void) {
  Serial.begin(9600);

  // Buttons
  pinMode(buttonPin0, INPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);

  // LED
  pinMode(LEDPin0, OUTPUT);
  pinMode(LEDPin1, OUTPUT);
  pinMode(LEDPin2, OUTPUT);
  pinMode(LEDPin3, OUTPUT);
  pinMode(GreenLEDPin, OUTPUT);
  pinMode(RedLEDPin, OUTPUT);

  randomSeed(analogRead(0));
}

void loop(void) {
  unsigned long currentMillis = millis();

  // Potentiometer readings
  minVal = analogRead(MIN);             //Read upper potentiometer value
  maxVal = analogRead(MAX);             //Read lower potentiometer value

  // Button readings  EDGE CASE: people pressing multiple button together
  if (digitalRead(buttonPin0) == HIGH)
    buttonNum = 0;
  else if (digitalRead(buttonPin1) == HIGH)
    buttonNum = 1;
  else if (digitalRead(buttonPin2) == HIGH)
    buttonNum = 2;
  else if (digitalRead(buttonPin3) == HIGH)
    buttonNum = 3;

  // LED states
  digitalWrite(LEDPin0, LEDState0);
  digitalWrite(LEDPin1, LEDState1);
  digitalWrite(LEDPin2, LEDState2);
  digitalWrite(LEDPin3, LEDState3);

  // Start game
  switch (buttonNum) {
    case 0:
      digitalWrite(LEDPin0, HIGH);
      break;
    case 1:
      digitalWrite(LEDPin1, HIGH);
      break;
    case 2:
      digitalWrite(LEDPin2, HIGH);
      break;
    case 3:
      digitalWrite(LEDPin3, HIGH);
      break;
    default:
      // Button is not pressed
      for (int thisPin = 0; thisPin < 4; thisPin++) {
        digitalWrite(thisPin, LOW);
      }
  }

  // Which sounds to play
  byte soundByte = B0000;
  if (minVal < maxVal) {
    // Check if the min and max are in range
    if (minVal < 5000)
      soundByte = soundByte | B1000;
    if (minVal <= 10000 && maxVal >= 10000)
      soundByte = soundByte | B0100;
    if (minVal <= 15000 && maxVal >= 15000)
      soundByte = soundByte | B0100;
    if (maxVal > 15000)
      soundByte = soundByte | B0001;
  }

  Serial.write(soundByte);
}









// During a round
if (currentMillis - previousMillis <= interval) {
  // If button is pressed play the reference tone
  if (buttonReading == HIGH)
    Serial.println(randFreq);
  else
    Serial.println(value);
}

// After a round is done
else {
  // Stop making a noise when a round is done
  Serial.println(0);

  // Update previous time
  previousMillis = currentMillis;

  // After the time interval, check if the player got it right.
  if ((value > randFreq - 40) && (value < randFreq + 40)) {
    // Green light when the user get it right
    for (int i = 0; i < 5; i++) {
      digitalWrite(GreenLEDPin, HIGH);
      delay(200);
      digitalWrite(GreenLEDPin, LOW);
      delay(200);
    }
  } else {
    // Red light when the user get it right
    for (int i = 0; i < 5; i++) {
      digitalWrite(RedLEDPin, HIGH);
      delay(200);
      digitalWrite(RedLEDPin, LOW);
      delay(200);
    }
  }

  // New round starts with a random freq
  randFreq = (int)random(100, 600);
}
}

