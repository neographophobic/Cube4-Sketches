/*
    File:     ColourPulse.ino
    Purpose:  ColourPulse pattern for the Freetronics 4x4x4 Cube (non blocking)
    Author:   Adam Reed (adam@secretcode.ninja)
    Licence:  BSD 3-Clause Licence
*/

// Include required libraries
#include "Cube.h"
#include "Cube4_ARUtils.h"

// Define global variables
// brightnessIncrement - is the change in brightness that is applied at each
//                       colour change. Larger values are more "visable",
//                       where smaller values make the animation run longer
//                       but ensures that the colour change is more subtle
byte brightnessIncrement = 5;

// theDelay tracks how long to pause between colour changes
byte theDelay = 50;

// theColour sets the colour that is used as the basis of the effect
rgb_t theColour = RGB(0x4B, 0x00, 0x82); // Violet
//rgb_t theColour = GREEN;

// Create an instance of the cube class
Cube cube;

void setup(void) {
  // Serial port options for control of the Cube using serial commands are:
  // 0: Control via the USB connector (most common).
  // 1: Control via the RXD and TXD pins on the main board.
  // -1: Don't attach any serial port to interact with the Cube.
  cube.begin(0, 115200); // Start on serial port 0 (USB) at 115200 baud

  // Wait for the serial interface, to be established, or for a maximum of
  // 3 seconds.
  byte waitCounter = 0;
  while (waitCounter < 30 && !Serial) {
    delay(100);
    waitCounter++;
  }

  // Print Debug Info if a serial interface is present
  if (Serial)
  {
    serial->println("Colour Pulse v1.0");
  }
}

void loop(void) {
  // Convert the provided colour to the HSV
  struct hsv theColourInHSV = rgb2hsv(theColour);

  // In HSV color, "V" stands for value which is the "brightness"
  // of the colour. By increasing or decreasing this we can keep the
  // colour, but make it appear brighter or darker

  // Get the brightness value from the HSV colour as an int
  int initialBrightness = (int) theColourInHSV.v;

  // Fade from "black" to the given colour's default brightness
  for (int i = 1; i <= initialBrightness; i = i + brightnessIncrement) {
    updateCubeColour(theColourInHSV, i);
  }

  // Fade from the colour's default brightness to "black"
  for (int i = initialBrightness; i >= 1; i = i - brightnessIncrement) {
    updateCubeColour(theColourInHSV, i);
  }
}

// updateCubeColour:  Taking the colour in HSV, and a new brightness value
//                    then convert it to RGB and set the cube to that colour
void updateCubeColour(struct hsv theColourInHSV, int brightness) {
  // Update the brightness value
  theColourInHSV.v = brightness;

  // Convert the newly updated HSV value into RGB
  rgb_t theNewColour = hsv2rgb(theColourInHSV);

  // Update the cube with the new colour
  cube.all(theNewColour);

  // Pause for the period the user has specified
  delay(theDelay);
}

