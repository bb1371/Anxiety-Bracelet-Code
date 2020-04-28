#define USE_ARDUINO_INTERRUPTS true  // Must include this to read and process PulseSensor data automatically
#include <PulseSensorPlayground.h>; // Include the PulseSensor Library
#include <Adafruit_NeoPixel.h>; // Include the NeoPixel Library


// Initialize the PulseSensor
const int PulsePin = 8; // Initialize the pin that the PulseSensor is connected to on the Flora
const int Threshold = 500; // Determine which signal from subject will count as a beat

PulseSensorPlayground pulseSensor; // Create an instance of the PulseSensorPlayground object called pulseSensor


// Initialize the Button
const int buttonPin = 10; // Initialize the pin that the button is connected to
int buttonState = 0; // Current state of the button
int lastButtonState = 0; // {revious state of the button
int buttonCount = 0; // Counter for how many times the button has been pressed

// Initialize the NeoPixels
const int LED_Pin = 6;
const int LED_Count = 4; // We are using 4 LEDs

// Now, delcare the Neopixel strip object
// Argument 1 = Number of Pixels in the strip
// Argument 2 = Arduino pin number
// Argument 3 = Pixel type flags, add together as needed:
    // NEO_GRB Pixels are wired for GRB bitstream (MIGHT BE RGB!!!!)
    // NEO_KHZ800 800KHz bitstream

Adafruit_NeoPixel strip (LED_Count, LED_Pin, NEO_GRB + NEO_KHZ800); // (MIGHT BE RGB!!!!!)


void setup() {
  
  Serial.begin(115200); // Set the Serial Monitor to the right baud rate (115200 is chosen because that is what the Processing Sketch expects to read, at about 11 bytes per millisecond.

  pinMode(buttonPin, INPUT); // Set the Button as the digital input
  pinMode(PulsePin, OUTPUT); // Set the PulseSensor as the digital output
                

  // Next, configure the PulseSensor Variables that were created
  pulseSensor.analogInput(PulsePin);
  pulseSensor.setThreshold(Threshold);

  strip.begin(); // Initializes the NeoPixel strip object
  strip.show(); // initialize all pixels to (off)
  strip.setBrightness(30); // Initialize the brightness setting

  
  if (pulseSensor.begin()){ // Start reading the pulseSensor signal
  }
}

void loop() {

  buttonState = digitalRead(buttonPin); // Read the state of the button


  if (buttonState != lastButtonState){ // If the state of the button has changed
    colorWipe(strip.Color(0, 50, 0, 0), 50); // Initializes a red colorwipe
    
    delay (3000); // Wait 3 ceconds

    anxietyExercise();

    delay (5000); // Wait 5 ceconds

    heartRateDisplay();
   
 
  lastButtonState = buttonState;
 
    }

}

// Initialize the colorWipe function, which fills each NeoPixel with a color, one after the other
void colorWipe(uint32_t color, int wait) { 
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip 
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(10);                           //  Pause for a moment
  }
}

// Initialize the anxietyExercise Function
void anxietyExercise() {

  // Set up the Inhaling Color Pattern. When the first LED lights up, begin to inhale, and when all 4 are lit up, stop inhaling. 
  strip.setPixelColor(0, 50, 0, 0);
  strip.show();
  delay (1000);
  
  strip.setPixelColor(1, 50, 0, 0);
  strip.show();
  delay (1000);
  
  strip.setPixelColor(2, 50, 0, 0);
  strip.show();
  delay (1000);
  
  strip.setPixelColor(3, 50, 0, 0);
  strip.show();
  
  delay (2000); // PAUSE for 2 seconds after inhaling

  // Begin Exhaling color pattern (LED's slowly turn off)
  
  strip.setPixelColor(3, 0, 0, 0);
  strip.show();
  delay (1000);
  
  strip.setPixelColor(2, 0, 0, 0);
  strip.show();
  delay(1000);

  strip.setPixelColor(1, 0, 0, 0);
  strip.show();
  delay(1000);

  strip.setPixelColor(0, 0, 0, 0);
  strip.show();
  delay(1000);
  
}


// Initialize the heartRateDisplay Function
void heartRateDisplay(){
  
  int BPM = pulseSensor.getBeatsPerMinute(); //Initializes the BPM function that is in the PulseSensorPlayground library
    if (pulseSensor.sawStartOfBeat()) { // Constantly tests to see if a beat happens
      Serial.println("Recording Heart Rate!"); // If the test is true (a beat was recorded), print a message to show that it is recrding the heart rate    
      Serial.println("BPM: "); // Print the phrase "BPM"
      Serial.println(BPM); // Print the value for BPM (the Heart Rate)
    }
  
  if (BPM <= 60){
    strip.setPixelColor(0, 50, 0, 0, 0); // (Pin, Green, Red, Blue, White)
    strip.setPixelColor(1, 0, 0, 0, 50); //
    strip.setPixelColor(2, 0, 0, 0, 50);
    strip.setPixelColor(3, 0, 0, 0, 50);
      strip.show(); // Show the Green light on LED 1
  }

  if (BPM > 60 && BPM <= 70){
    strip.setPixelColor(0, 0, 0, 0, 50);
    strip.setPixelColor(1, 50, 0, 0, 0); 
    strip.setPixelColor(2, 0, 0, 0, 50);
    strip.setPixelColor(3, 0, 0, 0, 50);
      strip.show(); // Show the Green Light on LED 2
  }

  if (BPM > 70 && BPM <= 80){
    strip.setPixelColor(0, 0, 0, 0, 50); 
    strip.setPixelColor(1, 0, 0, 0, 50);
    strip.setPixelColor(2, 50, 50, 0, 0);
    strip.setPixelColor(3, 0, 0, 0, 50);
      strip.show(); // Show the Yellow Light on LED 3
  }

  if (BPM > 80){
    strip.setPixelColor(0, 0, 0, 0, 50);
    strip.setPixelColor(1, 0, 0, 0, 50); 
    strip.setPixelColor(2, 0, 0, 0, 50);
    strip.setPixelColor(3, 0, 50, 0, 0);
      strip.show(); // Show the red light on LED 4
  }
}
