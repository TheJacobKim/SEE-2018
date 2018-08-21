#include <ArduinoJson.h>

//This is the pin where the cord is connected to
#define LINEAR A0

// Pin nums
const int buttonPin = 2;
const int GreenLEDPin = 9;
const int RedLEDPin = 8;

// Button states
int buttonReading;                  // the current reading from the input pin

// Time vars
const long interval = 12000;         // interval for a round
unsigned long previousMillis = 0;   // will store last a new round started

// Random freq
int randFreq = 350;

// Input from potentiometer
int value;

void setup(void) {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(GreenLEDPin, OUTPUT);
  pinMode(RedLEDPin, OUTPUT);
  randomSeed(analogRead(0));
}

void loop(void) {
  unsigned long currentMillis = millis();
  value = analogRead(LINEAR);             //Read potentiometer value
  buttonReading = digitalRead(buttonPin); // Read button

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

