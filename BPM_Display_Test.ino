// BPM Display Test RED (& Blue)
\
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
// Sets all of the LEDs to white to begin and to signify that heart rate is being detected
  strip.setPixelColor(0, 0, 0, 0, 50);
  strip.setPixelColor(1, 0, 0, 0, 50);
  strip.setPixelColor(2, 0, 0, 0, 50);
  strip.setPixelColor(3, 0, 0, 0, 50);
  strip.show();

  delay (5000); // wait 5 Seconds

// EMMA -- Change the second one in this strip to 0, & the fourth one to 50 for the BLUE Test
// (LED, Red, Green, Blue, White)
// Like this: strip.setPixelColor(0, 0, 0, 50, 0)


  strip.setPixelColor(0, 50, 0, 0, 0);
  strip.setPixelColor(1, 50, 0, 0, 0);
  strip.setPixelColor(2, 50, 0, 0, 0);
  strip.setPixelColor(3, 0, 0, 0, 0);
  strip.show();

  delay (10000); // Display Heart Rate for 10 Seconds

  
}
