
//This is the pin where the cord is connected to
#define MAX 0                    // Upper potentiometer
#define MIN 1                    // Lower potentiometer


// Pin nums
const int buttonPin0 = 2;
const int buttonPin1 = 3;
const int buttonPin2 = 4;
const int buttonPin3 = 5;
const int buttonPin4 = 6;

const int LEDPin0 = 7;
const int LEDPin1 = 8;
const int LEDPin2 = 9;
const int LEDPin3 = 10;
const int LEDPin4 = 11;

const int GreenLEDPin = 12;
const int RedLEDPin = 13;

// LED states
byte LEDState0 = LOW;
byte LEDState1 = LOW;
byte LEDState2 = LOW;
byte LEDState3 = LOW;
byte LEDState4 = LOW;

// Time vars
unsigned long previousMillis = 0; // will store last a new round started

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
  /*
    Serial.print("Min: ");
    Serial.println(minVal);
    Serial.print("Max: ");
    Serial.println(maxVal);
    delay(500);
  */
  // Button readings  EDGE CASE: people pressing multiple button together
  if (digitalRead(buttonPin0) == HIGH)
    buttonNum = 16;
  if (digitalRead(buttonPin1) == HIGH)
    buttonNum = 8;
  if (digitalRead(buttonPin2) == HIGH)
    buttonNum = 4;
  if (digitalRead(buttonPin3) == HIGH)
    buttonNum = 2;
  if (digitalRead(buttonPin4) == HIGH)
    buttonNum = 1;

  /*
    Serial.print("buttonNum: ");
    Serial.println(buttonNum);
    delay(2000);
  */

  LEDState0 = LOW;
  LEDState1 = LOW;
  LEDState2 = LOW;
  LEDState3 = LOW;
  LEDState4 = LOW;

  // Start game THIS DOES NOT WORK WELL
  switch (buttonNum) {
    case 16:
      LEDState0 = HIGH;
      break;
    case 8:
      LEDState1 = HIGH;
      break;
    case 4:
      LEDState2 = HIGH;
      break;
    case 2:
      LEDState3 = HIGH;
      break;
    case 1:
      LEDState4 = HIGH;
      break;
    default:
      break;
      // Button is not pressed
  }

  // LED states
  digitalWrite(LEDPin0, LEDState0);
  digitalWrite(LEDPin1, LEDState1);
  digitalWrite(LEDPin2, LEDState2);
  digitalWrite(LEDPin3, LEDState3);
  digitalWrite(LEDPin4, LEDState4);

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

  // Check if the user got it right
  if (soundByte == buttonNum) {
    digitalWrite(GreenLEDPin, HIGH);
    digitalWrite(RedLEDPin, LOW);
  } else {
    digitalWrite(GreenLEDPin, LOW);
    digitalWrite(RedLEDPin, HIGH);
  }
}
