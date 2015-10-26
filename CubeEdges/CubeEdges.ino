
/*
 * File:    CubeEdges.ino
 * Version: 1.0
 * Author:  Adam Reed (adam@secretcode.ninja)
 * License: BSD 3-Clause Licence
 */

#include "SPI.h"
#include "Cube.h"

Cube cube;

/*
 * User editable variables
 */

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
    serial->println("Cube Edges v1.0");
  }
}

void loop(void) {
  rgb_t theColour = BLUE;
  int theDelay = 250;

  cube.all(BLACK);
  delay(theDelay * 2);

  // 030 out
  lightUp(0,3,0, theColour, theDelay);
}

void lightUp(byte startX, byte startY, byte startZ, rgb_t theColour, int theDelay)
{
  cube.set(startX, startY, startZ, theColour);
  delay(theDelay);

  cube.set(startX + 1, startY, startZ, theColour);
  cube.set(startX, startY - 1, startZ, theColour);
  cube.set(startX, startY, startZ + 1, theColour);
  delay(theDelay);
  
}

