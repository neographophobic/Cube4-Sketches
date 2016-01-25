/*
   File:      ZigZag.ino
   Purpose:   ZigZag pattern for the Freetronics 4x4x4 Cube
   Author:    Adam Reed (adam@secretcode.ninja)
   Licence:   BSD 3-Clause Licence
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
    serial->println("ZigZag v1.0");
  }
}

void loop(void) {
  rgb_t theColour = BLUE;
  int theDelay = 300;

  // The Zig
  cube.all(BLACK);
  cube.set(0, 3, 0, theColour);
  cube.line(0, 1, 0, 2, 3, 0, theColour);
  cube.line(1, 0, 0, 3, 2, 0, theColour);
  cube.set(3, 0, 0, theColour);
  cube.copyplane(Z, 0, 2);
  cube.line(0, 2, 1, 1, 3, 1, theColour);
  cube.line(0, 0, 1, 3, 3, 1, theColour);
  cube.line(2, 0, 1, 3, 1, 1, theColour);
  cube.copyplane(Z, 1, 3);
  delay(theDelay);

  // The Zag
  cube.all(BLACK);
  cube.line(0, 2, 0, 1, 3, 0, theColour);
  cube.line(0, 0, 0, 3, 3, 0, theColour);
  cube.line(2, 0, 0, 3, 1, 0, theColour);
  cube.copyplane(Z, 0, 2);
  cube.set(0, 3, 1, theColour);
  cube.line(0, 1, 1, 2, 3, 1, theColour);
  cube.line(1, 0, 1, 3, 2, 1, theColour);
  cube.set(3, 0, 1, theColour);
  cube.copyplane(Z, 1, 3);
  delay(theDelay);
}

