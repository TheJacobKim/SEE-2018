#include <FatReader.h>
#include <SdReader.h>
#include <avr/pgmspace.h>
#include "WaveUtil.h"
#include "WaveHC.h"
#include <FastLED.h>

//This is the pin where the cord is connected to
#define MAX 0     // Upper potentiometer
#define MIN 1     // Lower potentiometer

SdReader card;    // This object holds the information for the card
FatVolume vol;    // This holds the information for the partition on the card
FatReader root;   // This holds the information for the filesystem on the card
FatReader f;      // This holds the information for the file we're play

// This is the wave (audio) object
WaveHC wave0;
WaveHC wave1;
WaveHC wave2;
WaveHC wave3;
WaveHC wave4;
WaveHC wave5;
WaveHC wave6;
WaveHC wave7;

#define DEBOUNCE 5  // button debouncer

// LED Strip
#define LED_PIN 7   //LED strip Pin
#define NUM_LEDS 25 //# of pixels

// audioFiles to play
const char * files[] = {
  "Garibaldi",
  "MantisShrimp",
  "SeaUrchin",
  "FalseKillerWhale",
  "HumpbackWhale",
  "CargoVessel",
  "Slowdown",
  "Whistle"
};
#define fileNum (sizeof (files) / sizeof (const char *))

// here is where we define the buttons that we'll use. button "1" is the first, button "6" is the 6th, etc
byte buttons[] = {14, 15, 16, 17, 18, 19};
byte leds[] = {20, 21, 22, 23, 24, 25};
int ledStates[] = {LOW, LOW, LOW, LOW, LOW};

// This handy macro lets us determine how big the array up above is, by checking the size
#define NUMBUTTONS sizeof(buttons)

// we will track if a button is just pressed, just released, or 'pressed' (the current state
volatile byte pressed[NUMBUTTONS], justpressed[NUMBUTTONS], justreleased[NUMBUTTONS];

uint8_t dirLevel; // indent level for file/dir names (for prettyprinting)
dir_t dirBuf;     // buffer for directory reads

const int GreenLEDPin = 12;
const int RedLEDPin = 13;

// Which button is selected
int buttonNum;

// this handy function will return the number of bytes currently free in RAM, great for debugging!
int freeRam(void) {
  extern int  __bss_end;
  extern int  *__brkval;
  int free_memory;
  if ((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__bss_end);
  }
  else {
    free_memory = ((int)&free_memory) - ((int)__brkval);
  }
  return free_memory;
}

void sdErrorCheck(void) {
  if (!card.errorCode()) return;
  putstring("\n\rSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  putstring(", ");
  Serial.println(card.errorData(), HEX);
  while (1);
}

void setup(void) {
  byte i;

  // set up serial port
  Serial.begin(9600);
  putstring_nl("WaveHC with ");
  Serial.print(NUMBUTTONS, DEC);
  putstring_nl("buttons");

  putstring("Free RAM: ");       // This can help with debugging, running out of RAM is bad
  Serial.println(freeRam());      // if this is under 150 bytes it may spell trouble!

  // Set the output pins for the DAC control. This pins are defined in the library
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  // pin13 LED strip
  pinMode(13, OUTPUT);

  // Make input & enable pull-up resistors on switch pins and leds
  for (i = 0; i < NUMBUTTONS; i++) {
    pinMode(buttons[i], INPUT);
    digitalWrite(buttons[i], HIGH);

    pinMode(leds[i + NUMBUTTONS], OUTPUT);
    digitalWrite(leds[i + NUMBUTTONS], HIGH);
  }

  if (!card.init()) {         //play with 8 MHz spi (default faster!)
    putstring_nl("Card init. failed!");  // Something went wrong, lets print out why
    sdErrorCheck();
    while (1);                           // then 'halt' - do nothing!
  }
  // enable optimize read - some cards may timeout. Disable if you're having problems
  card.partialBlockRead(true);

  // Now we will look for a FAT partition!
  uint8_t part;
  for (part = 0; part < 5; part++) {     // we have up to 5 slots to look in
    if (vol.init(card, part))
      break;                             // we found one, lets bail
  }
  if (part == 5) {                       // if we ended up not finding one  :(
    putstring_nl("No valid FAT partition!");
    sdErrorCheck();      // Something went wrong, lets print out why
    while (1);                           // then 'halt' - do nothing!
  }

  // Lets tell the user about what we found
  putstring("Using partition ");
  Serial.print(part, DEC);
  putstring(", type is FAT");
  Serial.println(vol.fatType(), DEC);    // FAT16 or FAT32?

  // Try to open the root directory
  if (!root.openRoot(vol)) {
    putstring_nl("Can't open root dir!"); // Something went wrong,
    while (1);                            // then 'halt' - do nothing!
  }

  /* Load all files
      I am ashamed of this piece of code, but I could not create an array of WaveHC object.
      Actually WaveHC object does not make sense sicne C is not object oriented.
      How it works? Magic!
  */
  if (!f.open(root, *files[0])) {       // Open FILENAME in root dir to FAT reader
    putstring("Couldn't open file ");
    Serial.print(*files[0]);
    return;
  }
  if (!wave0.create(f)) {               // Create WAVE object with FAT reader opened above
    putstring_nl("Not a valid WAV");
    return;
  }

  if (!f.open(root, *files[1])) {
    putstring("Couldn't open file ");
    Serial.print(*files[1]);
    return;
  }
  if (!wave1.create(f)) {
    putstring_nl("Not a valid WAV");
    return;
  }

  if (!f.open(root, *files[2])) {
    putstring("Couldn't open file ");
    Serial.print(*files[2]);
    return;
  }
  if (!wave2.create(f)) {
    putstring_nl("Not a valid WAV");
    return;
  }

  if (!f.open(root, *files[3])) {
    putstring("Couldn't open file ");
    Serial.print(*files[3]);
    return;
  }
  if (!wave3.create(f)) {
    putstring_nl("Not a valid WAV");
    return;
  }

  if (!f.open(root, *files[4])) {
    putstring("Couldn't open file ");
    Serial.print(*files[4]);
    return;
  }
  if (!wave4.create(f)) {
    putstring_nl("Not a valid WAV");
    return;
  }

  if (!f.open(root, *files[5])) {
    putstring("Couldn't open file ");
    Serial.print(*files[5]);
    return;
  }
  if (!wave5.create(f)) {
    putstring_nl("Not a valid WAV");
    return;
  }

  if (!f.open(root, *files[6])) {
    putstring("Couldn't open file ");
    Serial.print(*files[i]);
    return;
  }
  if (!wave6.create(f)) {
    putstring_nl("Not a valid WAV");
    return;
  }

  if (!f.open(root, *files[7])) {
    putstring("Couldn't open file ");
    Serial.print(*files[7]);
    return;
  }
  if (!wave7.create(f)) {
    putstring_nl("Not a valid WAV");
    return;
  }
  /* Finshied Loading files */

  // Whew! We got past the tough parts.
  putstring_nl("Ready!");

  TCCR2A = 0;
  TCCR2B = 1 << CS22 | 1 << CS21 | 1 << CS20;

  //Timer2 Overflow Interrupt Enable
  TIMSK2 |= 1 << TOIE2;
}


SIGNAL(TIMER2_OVF_vect) {
  check_switches();
}

void check_switches()
{
  static byte previousstate[NUMBUTTONS];
  static byte currentstate[NUMBUTTONS];
  byte index;

  for (index = 0; index < NUMBUTTONS; index++) {
    currentstate[index] = digitalRead(buttons[index]);   // read the button

    /*
       For debugging
      Serial.print(index, DEC);
      Serial.print(": cstate=");
      Serial.print(currentstate[index], DEC);
      Serial.print(", pstate=");
      Serial.print(previousstate[index], DEC);
      Serial.print(", press=");
    */

    if (currentstate[index] == previousstate[index]) {
      if ((pressed[index] == LOW) && (currentstate[index] == LOW)) {
        // just pressed
        justpressed[index] = 1;
      }
      else if ((pressed[index] == HIGH) && (currentstate[index] == HIGH)) {
        // just released
        justreleased[index] = 1;
      }
      pressed[index] = !currentstate[index];  // remember, digital HIGH means NOT pressed
    }
    //Serial.println(pressed[index], DEC);
    previousstate[index] = currentstate[index];   // keep a running tally of the buttons
  }
}

// Main part of the code
void loop(void) {
  byte i;
  unsigned long currentMillis = millis();

  // Potentiometer readings
  int minVal = analogRead(MIN);             //Read upper potentiometer value
  int maxVal = analogRead(MAX);             //Read lower potentiometer value

  Serial.println();
  Serial.print("Min: ");
  Serial.println(minVal);
  Serial.print("Max: ");
  Serial.println(maxVal);
  delay(500);


  // Make all ledStates low
  for (i = 0; i < NUMBUTTONS; i++) {
    ledStates[i] = LOW;
  }

  // Check buttons
  if (pressed[0]) {
    buttonNum = 16;
    ledStates[0] = HIGH;
  }
  else if (pressed[1]) {
    buttonNum = 8;
    ledStates[1] = HIGH;
  }
  else if (pressed[2]) {
    buttonNum = 4;
    ledStates[2] = HIGH;
  }
  else if (pressed[3]) {
    buttonNum = 2;
    ledStates[3] = HIGH;
  }
  else if (pressed[4]) {
    buttonNum = 1;
    ledStates[4] = HIGH;
  }

  /*
    Serial.print("buttonNum: ");
    Serial.println(buttonNum);
    delay(2000);
  */

  // Apply all ledStates
  byte j = 0;
  for (j = 0; j < NUMBUTTONS; j++) {
    digitalWrite(leds[j], ledStates[j]);
  }

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

  // Play the sound according to soundByte
  if ((soundByte & 1) == 1 && !wave0.isplaying)        wave0.play();
  else if ((soundByte & 1) != 1 && wave0.isplaying)    wave0.stop();

  if ((soundByte & 2) == 2 && !wave1.isplaying)        wave1.play();
  else if ((soundByte & 2) != 2 && wave1.isplaying)    wave1.stop();

  if ((soundByte & 4) == 4  && !wave2.isplaying)       wave2.play();
  else if ((soundByte & 4) != 4 && wave2.isplaying)    wave2.stop();

  if ((soundByte & 8) == 8 && !wave3.isplaying)        wave3.play();
  else if ((soundByte & 8) != 8 && wave3.isplaying)    wave3.stop();

  if ((soundByte & 16) == 16 && !wave4.isplaying)      wave4.play();
  else if ((soundByte & 16) != 16 && wave4.isplaying)  wave4.stop();

  // If a specific section is selected, mute other noise
  if (soundByte == 0 || soundByte == 1 || soundByte == 2 || soundByte == 4 || soundByte == 8 || soundByte == 16) {
    wave5.stop();
    wave6.stop();
    wave7.stop();
  } else {
    wave5.play();
    wave6.play();
    wave7.play();
  }

  // Check if the user got it right
  if (soundByte == buttonNum) {
    digitalWrite(GreenLEDPin, HIGH);
    digitalWrite(RedLEDPin, LOW);
  } else {
    digitalWrite(GreenLEDPin, LOW);
    digitalWrite(RedLEDPin, HIGH);
  }
}

