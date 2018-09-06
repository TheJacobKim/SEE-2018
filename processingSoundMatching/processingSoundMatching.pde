import processing.serial.*;
import processing.sound.*;
import ddf.minim.*;


// Global variables
Serial myPort;  // Create object from Serial class
String binary;
int val;

Minim minim;
AudioPlayer RightWhale;
AudioPlayer KillerWhale;
AudioPlayer HumpbackWhale;
AudioPlayer Narwhals;
AudioPlayer Dolphin;
AudioPlayer CargoVessel;
AudioPlayer Slowdown;
AudioPlayer Train;
AudioPlayer Whistle;


void setup() {
  // Connect Processing with Arduino

  String portName = Serial.list()[4]; //For my mac it is 0, windows might me 1 or 2
  myPort = new Serial(this, portName, 9600);
  minim = new Minim(this);

  RightWhale = minim.loadFile("3,200-5,300Hz North Atlantic Right Whale.mp3");
  KillerWhale = minim.loadFile("5,301-9,000Hz False Killer Whale.mp3");
  HumpbackWhale = minim.loadFile("9,001-11,000Hz Humpback Whale Song.mp3");
  Narwhals = minim.loadFile("18,000-20,000Hz Narwhals.mp3");
  Dolphin = minim.loadFile("18,000-20,000Hz Pantropical Spotted Dolphin.mp3");
  CargoVessel = minim.loadFile("Propeller Sound of a Cargo Vessel.mp3");
  Slowdown = minim.loadFile("Slowdown.mp3");
  Train = minim.loadFile("Train.mp3");
  Whistle = minim.loadFile("Whistle.mp3");

  RightWhale.loop();
 // KillerWhale.loop();
  HumpbackWhale.loop();
  //Narwhals.loop();
  Dolphin.loop();
  CargoVessel.loop();
  Slowdown.loop();
  Train.loop();
  Whistle.loop();
}      

void draw() {

  if ((val & 1) == 1 && RightWhale.isMuted())         RightWhale.unmute();
  else if ((val & 1) != 1 && !RightWhale.isMuted())   RightWhale.mute();

  
  if ((val & 2) == 2 && KillerWhale.isMuted())        KillerWhale.unmute();
   else if ((val & 2) != 2 && !KillerWhale.isMuted())  KillerWhale.mute();
  
  if ((val & 4) == 4  && HumpbackWhale.isMuted())      HumpbackWhale.unmute();
  else if ((val & 4) != 4 && !HumpbackWhale.isMuted()) HumpbackWhale.mute();
  
  if ((val & 8) == 8 && Narwhals.isMuted())           Narwhals.unmute();
   else if ((val & 8) != 8 && !Narwhals.isMuted())     Narwhals.mute();
  
  if ((val & 16) == 16 && Dolphin.isMuted())          Dolphin.unmute();
  else if ((val & 16) != 16 && !Dolphin.isMuted())    Dolphin.mute();

  // If a specific section is selected, mute other noise
  if (val == 0 || val == 1 || val == 2 || val == 4 || val == 8 || val == 16) {
    CargoVessel.mute();
    Slowdown.mute();
    Train.mute();
    Whistle.mute();
  } else {
    CargoVessel.unmute();
    Slowdown.unmute();
    Train.unmute();
    Whistle.unmute();
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
