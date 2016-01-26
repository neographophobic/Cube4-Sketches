/*
   File:      Wave.ino
   Purpose:   Wave pattern for the Freetronics 4x4x4 Cube
   Author:    Adam Reed (adam@secretcode.ninja)
   Licence:   BSD 3-Clause Licence
*/

// Include required libraries
#include <SPI.h>
#include "Cube.h"

/*
   User editable variables
*/
// The colour to use for the animation
rgb_t theColour = BLUE;

// The delay between each step of an animation
int theDelay = 100;

/*
   Don't edit these variables
*/
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
    serial->println("Wave v1.0");
  }
}

void loop(void) {
  // Create the wave animation

  // Frame 1
  drawWaveAnimationFrame(0, 0, 1, 1, 2, 2, 3, 3, theColour, theDelay);

  // Frame 2
  drawWaveAnimationFrame(0, 1, 1, 0, 2, 1, 3, 2, theColour, theDelay);

  // Frame 3
  drawWaveAnimationFrame(0, 2, 1, 1, 2, 0, 3, 1, theColour, theDelay);

  // Frame 4
  drawWaveAnimationFrame(0, 3, 1, 2, 2, 1, 3, 0, theColour, theDelay);

  // Frame 5
  drawWaveAnimationFrame(0, 2, 1, 3, 2, 2, 3, 1, theColour, theDelay);

  // Frame 6
  drawWaveAnimationFrame(0, 1, 1, 2, 2, 3, 3, 2, theColour, theDelay);
}

void drawWaveAnimationFrame(byte y1, byte z1, byte y2, byte z2, byte y3, byte z3, byte y4, byte z4, rgb_t theColour, int theDelay)
{
  cube.all(BLACK);
  cube.line(0, y1, z1, 3, y1, z1, theColour);
  cube.line(0, y2, z2, 3, y2, z2, theColour);
  cube.line(0, y3, z3, 3, y3, z3, theColour);
  cube.line(0, y4, z4, 3, y4, z4, theColour);
  delay(theDelay);
}

