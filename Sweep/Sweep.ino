/*
    File:     Sweep.ino
    Purpose:  Sweep pattern for the Freetronics 4x4x4 Cube (non blocking)
    Author:   Adam Reed (adam@secretcode.ninja)
    Licence:  BSD 3-Clause Licence
*/

// Include required libraries
#include <SPI.h>
#include "Cube.h"

/*
   User editable variables
*/


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
}

void loop(void) {
  /*
     User editable variables
  */
  rgb_t theColour = BLUE;
  int theDelay = 75;

  // Frame 1
  drawSweepAnimationFrame(0, 0, 1, 1, 2, 2, 3, 3, theColour, theDelay);

  // Frame 2
  drawSweepAnimationFrame(0, 1, 1, 1, 2, 2, 3, 2, theColour, theDelay);

  // Frame 3
  drawSweepAnimationFrame(0, 2, 1, 2, 2, 1, 3, 1, theColour, theDelay);

  // Frame 4
  drawSweepAnimationFrame(0, 3, 1, 2, 2, 1, 3, 0, theColour, theDelay);

  // Frame 5
  drawSweepAnimationFrame(1, 2, 1, 3, 2, 0, 2, 1, theColour, theDelay);

  // Frame 6
  drawSweepAnimationFrame(1, 0, 1, 1, 2, 2, 2, 3, theColour, theDelay);
}

void drawSweepAnimationFrame(byte x1, byte y1, byte x2, byte y2, byte x3, byte y3, byte x4, byte y4, rgb_t theColour, int theDelay) {
  cube.all(BLACK);
  cube.line(x1, y1, 0, x1, y1, 3, theColour);
  cube.line(x2, y2, 0, x2, y2, 3, theColour);
  cube.line(x3, y3, 0, x3, y3, 3, theColour);
  cube.line(x4, y4, 0, x4, y4, 3, theColour);
  delay(theDelay);
}

