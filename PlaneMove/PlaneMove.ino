
/*
 * File:    PlaneMove.ino
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
    serial->println("Plane Move v1.0");
  }
}

void loop(void) {
  rgb_t theColour = GREEN;
  int theDelay = 150;

  planeMove(X, 0, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);
  planeMove(X, 3, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);
  planeMove(Y, 0, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);
  planeMove(Y, 3, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);
  planeMove(Z, 0, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);
  planeMove(Z, 3, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);
}

void planeMove(byte axis, byte position, rgb_t theColour, int theDelay) {
  cube.setplane(axis, position, theColour);
  delay(theDelay);

  for (byte i = 1; i <= 3; i++) {
    if (position == 0) {
      cube.shift(axis, '+');
    } else {
      cube.shift(axis, '-');
    }
    delay(theDelay);
  }
}

