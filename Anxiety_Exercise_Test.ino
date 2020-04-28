// Test code

#define USE_ARDUINO_INTERRUPTS true  // Must include this to read and process PulseSensor data automatically
#include <PulseSensorPlayground.h>; // Include the PulseSensor Library
#include <Adafruit_NeoPixel.h>; // Include the NeoPixel Library

const int LED_Pin = 6;
const int LED_Count = 4;

Adafruit_NeoPixel strip (LED_Count, LED_Pin, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(115200);

  strip.begin();
  strip.show();
  strip.setBrightness(50);
}

void loop() {
  // Set up the Inhaling Color Pattern. When the first LED lights up, begin to inhale, and when all 4 are lit up, stop inhaling. 
  delay(5000); // wait 5 seconds
  
  strip.setPixelColor(0, 0, 50, 0);
  strip.setPixelColor(1, 0, 50, 0);
  strip.setPixelColor(2, 0, 50, 0);
  strip.setPixelColor(3, 0, 50, 0);
  strip.show();
  
  delay (3000);
  
  strip.setPixelColor(1, 0, 0, 50, 0);
  strip.show();
  delay (1000);
  
  strip.setPixelColor(2, 0, 0, 50, 0);
  strip.show();
  delay (1000);
  
  strip.setPixelColor(3, 0, 0, 50, 0);
  strip.show();
  
  delay (2000); // PAUSE for 2 seconds after inhaling

  // Begin Exhaling color pattern (LED's slowly turn off)
  
  strip.setPixelColor(3, 0, 50, 0, 0);
  strip.show();
  delay (1000);
  
  strip.setPixelColor(2, 0, 50, 0, 0);
  strip.show();
  delay(1000);

  strip.setPixelColor(1, 0, 50, 0, 0);
  strip.show();
  delay(1000);

  strip.setPixelColor(0, 0, 50, 0, 0);
  strip.show();
  delay(1000);

}
