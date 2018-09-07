import processing.serial.*;
import processing.sound.*;
import ddf.minim.*;


// Global variables
Serial myPort;  // Create object from Serial class
String binary;
int val;

Minim minim;
AudioPlayer FishA;
AudioPlayer FishB;
AudioPlayer FishC;
AudioPlayer FishD;
AudioPlayer FishE;
AudioPlayer NoiseA;
AudioPlayer NoiseB;
AudioPlayer NoiseC;


void setup() {
  // Connect Processing with Arduino
  String portName = Serial.list()[4]; //For my mac it is 0, windows might me 1 or 2
  myPort = new Serial(this, portName, 9600);
  minim = new Minim(this);

  // Set AudioPlayer objects
  FishA = minim.loadFile("A.mp3");
  FishB = minim.loadFile("B.mp3");
  FishC = minim.loadFile("C.mp3");
  FishD = minim.loadFile("D.mp3");
  FishE = minim.loadFile("E.mp3");
  NoiseA = minim.loadFile("F.mp3");
  NoiseB = minim.loadFile("G.mp3");
  NoiseC = minim.loadFile("H.mp3");

  FishA.loop();
  FishB.loop();
  FishC.loop();
  FishD.loop();
  FishE.loop();
  NoiseA.loop();
  NoiseB.loop();
  NoiseC.loop();
}      

void draw() {

  if ((val & 1) == 1 && FishA.isMuted())         FishA.unmute();
  else if ((val & 1) != 1 && !FishA.isMuted())   FishA.mute();


  if ((val & 2) == 2 && FishB.isMuted())         FishB.unmute();
  else if ((val & 2) != 2 && !FishB.isMuted())   FishB.mute();

  if ((val & 4) == 4  && FishC.isMuted())        FishD.unmute();
  else if ((val & 4) != 4 && !FishC.isMuted())   FishD.mute();

  if ((val & 8) == 8 && FishD.isMuted())         FishD.unmute();
  else if ((val & 8) != 8 && !FishD.isMuted())   FishD.mute();

  if ((val & 16) == 16 && FishE.isMuted())       FishE.unmute();
  else if ((val & 16) != 16 && !FishE.isMuted()) FishE.mute();

  // If a specific section is selected, mute other noise
  if (val == 0 || val == 1 || val == 2 || val == 4 || val == 8 || val == 16) {
    NoiseA.mute();
    NoiseB.mute();
    NoiseC.mute();
  } else {
    NoiseA.unmute();
    NoiseB.unmute();
    NoiseC.unmute();
  }
}

void serialEvent(Serial myPort) {
  // get the byte:
  String inByte = myPort.readStringUntil(10);

  if (inByte != null) {
    // Get the integer from arduino code and make that in to a binary string.
    String valStr = inByte.substring( 0, inByte.length() - 2 );
    binary = new String(Integer.toBinaryString(int(valStr)));
    println("Current val: " + binary);
    val = int(valStr);
  }
}
