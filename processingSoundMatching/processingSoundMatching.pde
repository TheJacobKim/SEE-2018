import processing.serial.*;
import processing.sound.*;
import ddf.minim.*;
import ddf.minim.spi.*; // for AudioRecordingStream
import ddf.minim.ugens.*;


// Global variables
Serial myPort;  // Create object from Serial class
String binary;
int val;

// declare everything we need to play our file
Minim minim;
AudioOutput out;
FilePlayer RightWhale;
FilePlayer KillerWhale;
FilePlayer HumpbackWhale;
FilePlayer Narwhals;
FilePlayer Dolphin;
FilePlayer CargoVessel;
FilePlayer Slowdown;
FilePlayer Train;
FilePlayer Whistle;


void setup() {
  // Connect Processing with Arduino
  String portName = Serial.list()[4]; //For my mac it is 0, windows might me 1 or 2
  myPort = new Serial(this, portName, 9600);

  // create our Minim object for loading audio
  minim = new Minim(this);

  RightWhale = new FilePlayer( minim.loadFileStream("NORM__3,200-5,300Hz North Atlantic Right Whale.mp3"));
  KillerWhale = new FilePlayer( minim.loadFileStream("NORM__5,301-9,000Hz False Killer Whale.mp3"));
  HumpbackWhale = new FilePlayer( minim.loadFileStream("NORM__9,001-11,000Hz Humpback Whale Song.mp3"));
  Narwhals = new FilePlayer( minim.loadFileStream("NORM__18,000-20,000Hz Narwhals.mp3"));
  Dolphin = new FilePlayer( minim.loadFileStream("18,000-20,000Hz Pantropical Spotted Dolphin.mp3"));
  CargoVessel = new FilePlayer( minim.loadFileStream("NORM__Propeller Sound of a Cargo Vessel.mp3"));
  Slowdown = new FilePlayer( minim.loadFileStream("NORM__Slowdown.mp3"));
  Train = new FilePlayer( minim.loadFileStream("NORM__Train.mp3"));
  Whistle = new FilePlayer( minim.loadFileStream("NORM__Whistle.mp3"));

  RightWhale.loop();
  KillerWhale.loop();
  HumpbackWhale.loop();
  Narwhals.loop();
  Dolphin.loop();
  CargoVessel.loop();
  Slowdown.loop();
  Train.loop();
  Whistle.loop();

  // get a line out from Minim. It's important that the file is the same audio format 
  // as our output (i.e. same sample rate, number of channels, etc).
  out = minim.getLineOut();

  // patch the file player to the output
  RightWhale.patch(out);
  KillerWhale.patch(out);
  HumpbackWhale.patch(out);
  Narwhals.patch(out);
  Dolphin.patch(out);
  CargoVessel.patch(out);
  Slowdown.patch(out);
  Whistle.patch(out);
}      

void draw() {

  if ((val & 1) == 1 && !RightWhale.isPlaying())        RightWhale.play();
  else if ((val & 1) != 1 && !RightWhale.isPlaying())   RightWhale.pause();

  if ((val & 2) == 2 && !KillerWhale.isPlaying())       KillerWhale.play();
  else if ((val & 2) != 2 && !KillerWhale.isPlaying())  KillerWhale.pause();

  if ((val & 4) == 4  && !HumpbackWhale.isPlaying())    HumpbackWhale.play();
  else if ((val & 4) != 4 && !HumpbackWhale.isPlaying())HumpbackWhale.pause();

  if ((val & 8) == 8 && !Narwhals.isPlaying())          Narwhals.play();
  else if ((val & 8) != 8 && !Narwhals.isPlaying())     Narwhals.pause();

  if ((val & 16) == 16 && !Dolphin.isPlaying())         Dolphin.play();
  else if ((val & 16) != 16 && !Dolphin.isPlaying())    Dolphin.pause();

  // If a specific section is selected, mute other noise
  if (val == 1 || val == 2 || val == 4 || val == 8 || val == 16) {
    CargoVessel.pause();
    Slowdown.pause();
    Train.pause();
    Whistle.pause();
  } else if (!CargoVessel.isPlaying()) {
    CargoVessel.play();
    Slowdown.play();
    Train.play();
    Whistle.play();
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
