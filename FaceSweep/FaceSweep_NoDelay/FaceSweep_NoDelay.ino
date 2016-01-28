/*
   File:      FaceSweep_NoDelay.ino
   Purpose:   FaceSweep pattern for the Freetronics 4x4x4 Cube (non blocking)
   Author:    Adam Reed (adam@secretcode.ninja)
   Licence:   BSD 3-Clause Licence
*/

// Include required libraries
#include "Cube.h"
#include "FaceSweep.h"

/*
   User editable variables
*/
// Define the delay between each step of an animation
int moveDelay = 75;

// Define the delay between the end of one animation, and the
// start of the next one
int sweepPause = 75;

// theColour sets the colour that is used as the basis of the effect
rgb_t theColour = BLUE;

// Create an instance of the cube class
Cube cube;

// Create an instance of the FaceSweep class
FaceSweep facesweep(cube, moveDelay, sweepPause);

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
    serial->println("FaceSweep v1.0 (non-blocking)");
  }
}

void loop(void) {
  facesweep.update(theColour);
}

