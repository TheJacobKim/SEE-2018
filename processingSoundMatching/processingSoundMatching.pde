import processing.serial.*;
import processing.sound.*;
import ddf.minim.*;


// Global variables
Serial myPort;  // Create object from Serial class
int val = 31;     // Data received from the serial port

// Sound files state
float RainState = 1;
float DolphinState = 1;
float KillerWhaleState = 1;
float ScubaState = 1;
float WalrusState = 1;

Minim minim;
AudioPlayer RightWhale;
AudioPlayer KillerWhale;
AudioPlayer HumpbackWhale;
AudioPlayer Beluga;
AudioPlayer Narwhals;
AudioPlayer CargoVessel;
AudioPlayer Slowdown;
AudioPlayer Train;
AudioPlayer Whistle;


void setup() {
  // Connect Processing with Arduino

  String portName = Serial.list()[4]; //For my mac it is 0, windows might me 1 or 2
  myPort = new Serial(this, portName, 9600);
  minim = new Minim(this);

  RightWhale = minim.loadFile("44khz_NORM__3,200-5,300Hz North Atlantic Right Whale.wav");
  KillerWhale = minim.loadFile("44khz_NORM__5,301-9,000Hz False Killer Whale.wav");
  HumpbackWhale = minim.loadFile("44khz_NORM__9,001-11,000Hz Humpback Whale Song.wav");
  Beluga = minim.loadFile("11,001-1800Hz Beluga Whale.mp3");
  Narwhals = minim.loadFile("18,000-20,000Hz Narwhals.mp3");
  CargoVessel = minim.loadFile("NORM__Propeller Sound of a Cargo Vessel.wav");
  Slowdown = minim.loadFile("NORM__Slowdown.wav");
  Train = minim.loadFile("NORM__Train.wav");
  Whistle = minim.loadFile("NORM__Whistle.wav");

  RightWhale.loop();
  KillerWhale.loop();
  HumpbackWhale.loop();
  Beluga.loop();
  Narwhals.loop();
  CargoVessel.loop();
  Slowdown.loop();
  Train.loop();
  Whistle.loop();
}      

void draw() {
  if (val >= 1 && RightWhale.isMuted())         RightWhale.unmute();
  else if (val < 1 && !RightWhale.isMuted())    RightWhale.mute();

  if (val >= 2 && KillerWhale.isMuted())        KillerWhale.unmute();
  else if (val < 2 && !KillerWhale.isMuted())   KillerWhale.mute();

  if (val >= 4 && HumpbackWhale.isMuted())      HumpbackWhale.unmute();
  else if (val < 4 && !HumpbackWhale.isMuted()) HumpbackWhale.mute();

  if (val >= 8 && Beluga.isMuted())             Beluga.unmute();
  else if (val < 8 && !Beluga.isMuted())        Beluga.mute();

  if (val >= 16 && Narwhals.isMuted())          Narwhals.unmute();
  else if (val < 16 && !Narwhals.isMuted())     Narwhals.mute();
  
  // If a specific section is selected, mute other noise
  if (val == 1 || val == 2 || val == 4 || val == 8 || val == 16) {
      CargoVessel.mute();
      Slowdown.mute();
      Train.mute();
      Whistle.mute();
  }
}

void serialEvent(Serial myPort) {
  // get the byte:
  String inByte = myPort.readStringUntil(10);
  println("Current val: " + val);

  if (inByte != null) {
    String valStr = inByte.substring( 0, inByte.length() - 2 );
    val = int(valStr);
  }
}
