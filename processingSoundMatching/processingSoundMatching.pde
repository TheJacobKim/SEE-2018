import processing.serial.*;
import processing.sound.*;
import ddf.minim.*;


// Global variables
Serial myPort;  // Create object from Serial class
int val;     // Data received from the serial port

// Sound files state
float RainState = 1;
float DolphinState = 1;
float KillerWhaleState = 1;
float ScubaState = 1;
float WalrusState = 1;

Minim minim;
AudioPlayer Rain;
AudioPlayer Dolphin;
AudioPlayer KillerWhale;
AudioPlayer Scuba;
AudioPlayer Walrus;


void setup() {
  // Connect Processing with Arduino
  String portName = Serial.list()[0]; //For my mac it is 0, windows might me 1 or 2
  myPort = new Serial(this, portName, 9600);
  minim = new Minim(this);

  Rain = minim.loadFile("Rain.mp3");
  Dolphin = minim.loadFile("Dolphin.mp3");
  KillerWhale = minim.loadFile("KillerWhale.mp3");
  Scuba = minim.loadFile("Scuba.mp3");
  Walrus = minim.loadFile("Walrus.mp3");

  Rain.loop();
  Dolphin.loop();
  KillerWhale.loop();
  Scuba.loop();
  Walrus.loop();
}      

void draw () {

  if (val >= 1 && Rain.isMuted())         Rain.unmute();
  else if (val < 1 && !Rain.isMuted())    Rain.mute();

  if (val >= 2 && Dolphin.isMuted())      Dolphin.unmute();
  else if (val < 2 && !Dolphin.isMuted()) Dolphin.mute();

  if (val >= 4 && KillerWhale.isMuted())  KillerWhale.unmute();
  else if (val < 4 && !KillerWhale.isMuted())        KillerWhale.mute();

  if (val >= 8 && Scuba.isMuted())        Scuba.unmute();
  else if (val < 8 && !Scuba.isMuted())              Scuba.mute();

  if (val >= 16 && Walrus.isMuted())      Walrus.unmute();
  else if (val < 16 && !Walrus.isMuted())             Walrus.mute();
}

void serialEvent (Serial myPort) {
  // get the byte:
  String inByte = myPort.readStringUntil(10);
  println("Current val: " + val);

  if (inByte != null) {
    String valStr = inByte.substring( 0, inByte.length() - 2 );
    val = int(valStr);
  }

  /*
  Rain.setVolume(RainState);
   Rain.setVolume(DolphinState);
   Rain.setVolume(KillerWhaleState);
   Rain.setVolume(ScubaState);
   Rain.setVolume(WalrusState); */
}
