import processing.serial.*;
import processing.sound.*;
import java.util.Random;
import java.util.Timer;

// Global variables
Serial myPort;  // Create object from Serial class
int val = 0;     // Data received from the serial port

// Sound files
SoundFile file0;
SoundFile file1;
SoundFile file2;
SoundFile file3;
SoundFile file4;

void setup() {
  // Connect Processing with Arduino
  String portName = Serial.list()[2]; //For my mac it is 0, windows might me 1 or 2
  myPort = new Serial(this, portName, 9600);

  // Load a soundfile from the /data folder
  file0 = new SoundFile(this, "Rain.mp3");
  file1 = new SoundFile(this, "Dolphin.mp3");
  file2 = new SoundFile(this, "KillerWhale.mp3");
  file3 = new SoundFile(this, "Scuba.mp3");
  file4 = new SoundFile(this, "Walrus.mp3");
}      

void draw () {
  println("Current val: " + val);
  if (val >= 1)
    file0.loop();
  else
    file0.stop();

  if (val >= 2)
    file1.loop();
  else
    file1.stop();
    
  if (val >= 4)
    file2.loop();
  else
    file2.stop();
    
  if (val >= 8)
    file3.loop();
  else
    file3.stop();
    
  if (val >= 16)
    file4.loop();
  else
    file4.stop();
}

void serialEvent (Serial myPort) {
  // get the byte
  val = myPort.read();
}
