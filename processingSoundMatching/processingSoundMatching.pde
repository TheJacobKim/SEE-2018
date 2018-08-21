import processing.serial.*;
import processing.sound.*;
import java.util.Random;
import java.util.Timer;
import ddf.minim.*;
import ddf.minim.ugens.*;

// Global variables
Serial myPort;  // Create object from Serial class
int val = 0;     // Data received from the serial port
Random rand = new Random();
int freq = 300;

// Wave library variables
Minim minim;
AudioOutput out;
Oscil wave;

void setup() {
  // Connect Processing with Arduino
  String portName = Serial.list()[2]; //For my mac it is 0, windows might me 1 or 2
  myPort = new Serial(this, portName, 9600);

  // Set sine wave
  minim = new Minim(this);
  out = minim.getLineOut();
  wave = new Oscil( freq, 0.5f, Waves.SINE );
  wave.patch( out );
  //smooth(20);
}      

void draw () {
  wave.setFrequency(val + freq);

  println("Current freq: " + (freq + val));
}


void serialEvent (Serial myPort) {
  // get the byte
  String inByte = myPort.readStringUntil(10);
  if (inByte != null) {
    String valStr = inByte.substring( 0, inByte.length() - 2 );
    val = int(valStr);
  }
  
  if(val == 0)
    val = -freq;
}
