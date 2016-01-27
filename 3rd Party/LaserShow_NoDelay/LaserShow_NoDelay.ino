/*
    File:     LaserShow_NoDelay.ino
    Purpose:  LaserShow pattern for the Freetronics 4x4x4 Cube (non blocking)

    Original Author:   Blake Kus (blakekus@gmail.com)
    License:           GPLv3
    This example is part of the Cube4 Library from Freetronics
    https://github.com/freetronics/Cube4.

    Modified by:       Adam Reed (adam@secretcode.ninja)
*/

// Include required libraries
#include <SPI.h>
#include "Cube.h"
#include "LaserShow.h"

/*
   User editable variables
*/
// theDelay tracks how long to pause between colour changes
int theDelay = 150;

// theColours sets the colours that are used for the lasers
rgb_t theColours[4] = {WHITE, BLUE, GREEN, RED};

// Create an instance of the cube class
Cube cube;

// Create an instance of the LaserShow class
LaserShow lasershow(cube, theDelay);

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
    serial->println("LaserShow v1.0 (non-blocking)");
  }
}

void loop(void) {
  lasershow.update(theColours);
}

