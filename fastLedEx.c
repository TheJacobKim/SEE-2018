#include <FastLED.h>


#define LED_PIN 7        //LED strip Pin 
#define NUM_LEDS   25  //# of pixels 
CRGB leds[NUM_LEDS];


void setup(void) {

  Serial.begin(9600);
  FastLED.addLeds<WS2812 , LED_PIN, GRB>(leds, NUM_LEDS);


}    

void loop (){

for (int i=0; i<=25;i++){
 leds[i]=CRGB(255,0,0);
 FastLED.show();
delay(10);
}

for (int i=0; i<=25;i++){
 leds[i]=CRGB(0,255,0);
 FastLED.show();
delay(10);
}
  
}