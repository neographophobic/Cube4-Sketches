/*
   File:      LoopingBoxes_NoDelay.ino
   Purpose:   pattern for the Freetronics 4x4x4 Cube (non blocking)
   Author:    Adam Reed (adam@secretcode.ninja)
   Licence:   BSD 3-Clause Licence
*/

// Include required libraries
#include <SPI.h>
#include "Cube.h"
#include "LoopingBoxes.h"

/*
   User editable variables
*/
// theDelay tracks how long to pause between colour changes
byte theDelay = 150;

// innerColour sets the colour that is used for the inner square
rgb_t innerColour = GREEN;

// outerColour sets the colour that is used for the outer square
rgb_t outerColour = RED;

// Create an instance of the cube class
Cube cube;

// Create an instance of the LoopingBoxes class
LoopingBoxes loopingboxes(cube, theDelay);

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
    serial->println("LoopingBoxes v1.0 (non-blocking)");
  }
}

void loop(void) {
  loopingboxes.update(innerColour, outerColour);
}

