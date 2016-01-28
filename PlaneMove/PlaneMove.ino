/*
   File:      PlaneMove.ino
   Purpose:   Plane Move pattern for the Freetronics 4x4x4 Cube
   Author:    Adam Reed (adam@secretcode.ninja)
   Licence:   BSD 3-Clause Licence
*/

// Include required libraries
#include "Cube.h"

/*
   User editable variables
*/
// The colour to use for the animation
rgb_t theColour = GREEN;

// The delay between each step of an animation
int theDelay = 150;

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
    serial->println("Plane Move v1.0");
  }
}

void loop(void) {
  // Move the X plane left to right then right to left
  cube.all(BLACK);
  planeMove(X, 0, theColour, theDelay);
  planeMove(X, 3, theColour, theDelay);

  // Move the Y plane front to back then back to front
  cube.all(BLACK);
  planeMove(Y, 0, theColour, theDelay);
  planeMove(Y, 3, theColour, theDelay);

  // Move the Z plane bottom to top then top to bottom
  cube.all(BLACK);
  planeMove(Z, 0, theColour, theDelay);
  planeMove(Z, 3, theColour, theDelay);
}

void planeMove(byte axis, byte position, rgb_t theColour, int theDelay) {
  // Illuminate the plane we start on and pause
  cube.setplane(axis, position, theColour);
  delay(theDelay);

  // Loop for the additional 3 "stops" along the plane move
  for (byte i = 1; i <= 3; i++) {
    if (position == 0) {
      // Move the plane in a positive direction
      // (left to right, front to back, bottom to top)
      cube.shift(axis, '+');
    } else {
      // Move the plane in a negative direction
      // (right to left, back to front, top to bottom)
      cube.shift(axis, '-');
    }
    delay(theDelay);
  }
}

