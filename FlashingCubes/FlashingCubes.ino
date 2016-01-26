/*
   File:      FlashingCubes.ino
   Purpose:   Flashing Cubes pattern for the Freetronics 4x4x4 Cube
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
int theDelay = 500;

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
    serial->println("Flashing Cubes v1.0");
  }
}

void loop(void) {
  cube.all(BLACK);
  cube.box(1, 1, 1, 2, 2, 2, theColour);
  delay(theDelay);
  cube.box(0, 0, 0, 3, 3, 3, theColour);
  delay(theDelay);
  cube.box(1, 1, 1, 2, 2, 2, BLACK);
  delay(theDelay);
  cube.box(0, 0, 0, 3, 3, 3, theColour);
  delay(theDelay);
}

