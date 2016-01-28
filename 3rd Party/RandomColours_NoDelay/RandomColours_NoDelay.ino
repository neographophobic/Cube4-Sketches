/*
   File:      RandomColours_NoDelay.ino
   Purpose:   Random Colour patterns for the Freetronics 4x4x4 Cube (non blocking)

   Original Author:   Jonathan Oxer (jon@freetronics.com)
   License:           GPLv3
   These examples are part of the Cube4 Library from Freetronics
   https://github.com/freetronics/Cube4.

   Modified by:       Adam Reed (adam@secretcode.ninja)
*/

// Include required libraries
#include "Cube.h"
#include "RandomColours.h"

/*
   User editable variables
*/
// theDelay tracks how long to pause between colour changes
int theDelay = 2;

// Create an instance of the cube class
Cube cube;

// Create an instance of the RandomColours class
RandomColours randomcolours(cube, theDelay);

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
    serial->println("Random Colours v1.0 (non-blocking)");
  }
}

void loop(void) {
  // Only use one of the following options at a time
  // as due to the non blocking nature of the code
  // if they are all allowed to run, the results of
  // the three will blend into one

  // Random Colours
  randomcolours.allColours();

  // Random Pastels
  //randomcolours.pastels();

  // Random Primaries
  //randomcolours.primary();
}

