# LED Anxiety Bracelet with Heart Rate Monitor

This project was created on April 28, 2020 by Bryson Boettger and Emma Vogan for the 
ENGR 375 Biomedical Instrumentation and Measurement Biosensor Project in the Messiah College department of Engineering
    
When a person is feeling anxious and wants stress relief, they press a button on this bracelet to begin this code.
    
First, the code collects the subject's initial heart rate using a PulseSensor and displays it through four individual NeoPixels that are in  a line.
Based on what heart rate is detected, a certain series of LEDs/colors will be displayed. For instance. If the heart rate is 76, there will be 3 NeoPixels that are lit up in Blue. These colors/thresholds are given to the subject via a sticker on the bracelet so that they know what their heart rate is at. 
   
Then, after the heart rate is detected, it goes through an anxiety exercise which aids in deep, slow inhaling and exhaling. At the beginning of this exercise, all four LEDs are green. As the exercise goes on, the LEDs turn blue one by one which scorrespond to when the subject should be inhaling. After all four LEDs are lit, the subject is to hold their breath, and as the LEDs turn back to green they can slowly exhale.
 
After the anxiety exercise is performed, the code will again detect and display the persons heart rate to determine if they were able to calm down.
    
    
