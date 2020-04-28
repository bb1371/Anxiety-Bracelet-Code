/*  
    LED Anxiety Bracelet with Heart Rate Monitor

    When a person is feeling anxious and wants stress relief, they press a button on this bracelet to begin this code.
    
    First, the code collects the subject's initial heart rate using a PulseSensor and displays it through four individual NeoPixels that are in  a line.
    Based on what heart rate is detected, a certain series of LEDs/colors will be displayed. For instance. If the heart rate is 76, there
    will be 3 NeoPixels that are lit up in Blue. These colors/thresholds are given to the subject via a sticker on the bracelet so that they
    know what their heart rate is at. 

    Then, after the heart rate is detected, it goes through an anxiety exercise which aids in deep, slow inhaling and exhaling. At the beginning of this
    exercise, all four LEDs are green. As the exercise goes on, the LEDs turn blue one by one which scorrespond to when the subject should be inhaling. 
    After all four LEDs are lit, the subject is to hold their breath, and as the LEDs turn back to green they can slowly exhale.

    After the anxiety exercise is performed, the code will detect and display the persons heart rate to determine if they were able to calm down.

    Created 28 April 2020
    By Bryson Boettger and Emma Vogan

    ENGR 375 Biomedical Instrumentation and Measurement
    Biosensor Project
    Messiah College department of Engineering
 */


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
int lastButtonState = 0; // Previous state of the button
int buttonCount = 0; // Counter for how many times the button has been pressed

// Initialize the NeoPixels
const int LED_Pin = 6; // Initialize the pin that the NeoPixels are connected to
const int LED_Count = 4; // We are using 4 LEDs

// Now, delcare the Neopixel strip object
// Argument 1 = Number of Pixels in the strip
// Argument 2 = Arduino pin number
// Argument 3 = Pixel type flags, add together as needed:
    // NEO_GRB Pixels are wired for GRB bitstream (MIGHT BE RGB!!!!)
    // NEO_KHZ800 800KHz bitstream

Adafruit_NeoPixel strip (LED_Count, LED_Pin, NEO_GRB + NEO_KHZ800);


void setup() {
  
  Serial.begin(115200); // Set the Serial Monitor to the right baud rate (115200 is chosen because that is what the Processing Sketch expects to read, at about 11 bytes per millisecond)

  pinMode(buttonPin, INPUT); // Set the Button as the digital input
  pinMode(PulsePin, OUTPUT); // Set the PulseSensor as the digital output
                

  // Next, configure the PulseSensor Variables that were created
  pulseSensor.analogInput(PulsePin);
  pulseSensor.setThreshold(Threshold);

  strip.begin(); // Initialize the NeoPixel strip object
  strip.show(); // initialize all pixels to (off)
  strip.setBrightness(50); // Initialize the brightness setting

  
  if (pulseSensor.begin()){ // Start reading the pulseSensor signal
  }
}

void loop() {

  buttonState = digitalRead(buttonPin); // Read the state of the button


  if (buttonState != lastButtonState){ // If the state of the button has changed
    colorWipe(strip.Color(0, 50, 0, 0), 50); // Initialize a red colorwipe

    delay(5000); // Wait 5 seconds

    heartRateDisplay(); // Call the heartRateDisplay function and display initial heart rate
    
    delay (5000); // Wait 5 seconds

    anxietyExercise(); // Call the anxietyExercise function

    delay (5000); // Wait 5 seconds

    heartRateDisplay(); // Call heartRateDisplay function and display final heart rate
   
 
  lastButtonState = buttonState; // Change the state of the variable lastButtonState
 
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

  strip.setPixelColor(0, 0, 50, 0, 0); // (Pin, Red, Green, Blue, White)
  strip.setPixelColor(1, 0, 50, 0, 0);
  strip.setPixelColor(2, 0, 50, 0, 0);
  strip.setPixelColor(3, 0, 50, 0, 0);
    strip.show(); // Show the Green Light
  
  delay (3000);

  // Change the LEDs to Blue light, one by one
  strip.setPixelColor(1, 0, 0, 50, 0);
  strip.show();
  delay (1000);
  
  strip.setPixelColor(2, 0, 0, 50, 0);
  strip.show();
  delay (1000);
  
  strip.setPixelColor(3, 0, 0, 50, 0);
  strip.show();
  
  delay (2000); // PAUSE for 2 seconds after inhaling


  // Begin Exhaling color pattern (Turn LED's slowly back to green)
  
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


// Initialize the heartRateDisplay Function
void heartRateDisplay(){

  // Set all LEDs to white to signify that Heart Rate is about to be taken
  strip.setPixelColor(0, 0, 0, 0, 50);
  strip.setPixelColor(1, 0, 0, 0, 50);
  strip.setPixelColor(2, 0, 0, 0, 50);
  strip.setPixelColor(3, 0, 0, 0, 50);
  
  int BPM = pulseSensor.getBeatsPerMinute(); // Initializes the BPM function that is in the PulseSensorPlayground library
    if (pulseSensor.sawStartOfBeat()) { // Constantly tests to see if a beat happens
      Serial.println("Recording Heart Rate!"); // If the test is true (a beat was recorded), print a message to show that it is recrding the heart rate    
      Serial.println("BPM: "); // Print the phrase "BPM"
      Serial.println(BPM); // Print the value for BPM (the Heart Rate)
    }

  delay (5000); // Wait 5 Seconds while the Heart Rate is being taken


  
 
  // Initialize good Heart Rate zone (0-70)

  if (BPM <= 62.5){
    strip.setPixelColor(0, 0, 50, 0, 0); // (Pin, Red, Green, Blue, White)
    strip.setPixelColor(1, 0, 0, 0, 0); 
    strip.setPixelColor(2, 0, 0, 0, 0);
    strip.setPixelColor(3, 0, 0, 0, 0);
      strip.show(); // Show green light on LED 1 
  }
  if (BPM > 62.5 && BPM <= 65) {
    strip.setPixelColor(0, 0, 50, 0, 0); // (Pin, Red, Green, Blue, White)
    strip.setPixelColor(1, 0, 50, 0, 0); 
    strip.setPixelColor(2, 0, 0, 0, 0);
    strip.setPixelColor(3, 0, 0, 0, 0);
      strip.show(); // Show green light on LEDs 1 & 2
  }

  if (BPM > 65 && BPM <= 67.5){
    strip.setPixelColor(0, 0, 50, 0, 0); // (Pin, Red, Green, Blue, White)
    strip.setPixelColor(1, 0, 50, 0, 0); //
    strip.setPixelColor(2, 0, 50, 0, 0);
    strip.setPixelColor(3, 0, 0, 0, 0);
      strip.show(); // Show green light on LEDs 1, 2, & 3
  }
  if (BPM > 67.5 && BPM <= 70){
    strip.setPixelColor(0, 0, 50, 0, 0); // (Pin, Red, Green, Blue, White)
    strip.setPixelColor(1, 0, 50, 0, 0); 
    strip.setPixelColor(2, 0, 50, 0, 0);
    strip.setPixelColor(3, 0, 50, 0, 0);
      strip.show(); // Show green light on all 4 LEDs
  }



  // Initialize the 70-80 Heart rate zone (Blue)

  if (BPM > 70 && BPM <= 72.5){
    strip.setPixelColor(0, 0, 0, 50, 0); // (Pin, Red, Green, Blue, White)
    strip.setPixelColor(1, 0, 0, 0, 0);  
    strip.setPixelColor(2, 0, 0, 0, 0);
    strip.setPixelColor(3, 0, 0, 0, 0);
      strip.show(); // Show blue light on LED 1
  }

   if (BPM > 72.5 && BPM <= 75){
    strip.setPixelColor(0, 0, 0, 50, 0); // (Pin, Red, Green, Blue, White)
    strip.setPixelColor(1, 0, 0, 50, 0); 
    strip.setPixelColor(2, 0, 0, 0, 0);
    strip.setPixelColor(3, 0, 0, 0, 0);
      strip.show(); // Show blue light on LEDs 1 & 2
  }

   if (BPM > 75 && BPM <= 77.5){
    strip.setPixelColor(0, 0, 0, 50, 0); // (Pin, Red, Green, Blue, White)
    strip.setPixelColor(1, 0, 0, 50, 0); 
    strip.setPixelColor(2, 0, 0, 50, 0);
    strip.setPixelColor(3, 0, 0, 0, 0);
      strip.show(); // Show blue light on LEDs 1, 2 & 3
  }

   if (BPM > 77.5 && BPM <= 80){
    strip.setPixelColor(0, 0, 0, 50, 0); // (Pin, Red, Green, Blue, White)
    strip.setPixelColor(1, 0, 0, 50, 0); 
    strip.setPixelColor(2, 0, 0, 50, 0);
    strip.setPixelColor(3, 0, 0, 50, 0);
      strip.show(); // Show blue light on all 4 LEDs 
  }



// Initialize the 80-90 heart rate zone (Yellow)
   if (BPM > 80 && BPM <= 82.5){
    strip.setPixelColor(0, 50, 50, 0, 0); // (Pin, Red, Green, Blue, White)
    strip.setPixelColor(1, 0, 0, 0, 0); 
    strip.setPixelColor(2, 0, 0, 0, 0);
    strip.setPixelColor(3, 0, 0, 0, 0);
      strip.show(); // Show yellow light on LED 1
  }
  
  if (BPM > 82.5 && BPM <= 85){
    strip.setPixelColor(0, 50, 50, 0, 0); // (Pin, Red, Green, Blue, White)
    strip.setPixelColor(1, 50, 50, 0, 0); 
    strip.setPixelColor(2, 0, 0, 0, 0);
    strip.setPixelColor(3, 0, 0, 0, 0);
      strip.show(); // Show yellow light on LEDs 1 & 2
  }

  if (BPM > 85 && BPM <= 87.5){
    strip.setPixelColor(0, 50, 50, 0, 0); // (Pin, Red, Green, Blue, White)
    strip.setPixelColor(1, 50, 50, 0, 0); 
    strip.setPixelColor(2, 50, 50, 0, 0);
    strip.setPixelColor(3, 0, 0, 0, 0);
      strip.show(); // Show yellow yight on LEDs 1, 2, & 3
  }

  if (BPM > 87.5 && BPM <= 90){
    strip.setPixelColor(0, 50, 50, 0, 0); // (Pin, Red, Green, Blue, White)
    strip.setPixelColor(1, 50, 50, 0, 0); 
    strip.setPixelColor(2, 50, 50, 0, 0);
    strip.setPixelColor(3, 50, 50, 0, 0);
      strip.show(); // Show yellow light on all 4LEDs
  }



// Initialize the > 90 Heart rate zone (Red)
  if (BPM > 90){
    strip.setPixelColor(0, 50, 0, 0, 0); // (Pin, Red, Green, Blue, White)
    strip.setPixelColor(1, 50, 0, 0, 0); 
    strip.setPixelColor(2, 50, 0, 0, 0);
    strip.setPixelColor(3, 50, 0, 0, 0);
      strip.show(); // Show red light on all 4 LEDs
  }
}
