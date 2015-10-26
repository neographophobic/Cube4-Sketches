
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
  byte startX = 0;
  byte startY = 3;
  byte startZ = 0;

  // From first point
  cube.set(startX, startY, startZ, theColour);
  delay(theDelay);

  cube.set(startX + 1, startY, startZ, theColour);
  cube.set(startX, startY - 1, startZ, theColour);
  cube.set(startX, startY, startZ + 1, theColour);
  delay(theDelay);

  cube.set(startX + 2, startY, startZ, theColour);
  cube.set(startX, startY - 2, startZ, theColour);
  cube.set(startX, startY, startZ + 2, theColour);
  delay(theDelay);

  cube.set(startX + 3, startY, startZ, theColour);
  cube.set(startX, startY - 3, startZ, theColour);
  cube.set(startX, startY, startZ + 3, theColour);
  delay(theDelay);

  // Second Part - from the three new points
  byte point2X = 0;
  byte point2Y = 0;
  byte point2Z = 0;

  byte point3X = 0;
  byte point3Y = 3;
  byte point3Z = 3;

  byte point4X = 3;
  byte point4Y = 3;
  byte point4Z = 0;

  cube.set(point2X + 1, point2Y, point2Z, theColour);
  cube.set(point2X, point2Y + 1, point2Z, theColour);
  cube.set(point2X, point2Y, point2Z + 1, theColour);
  cube.set(point3X + 1, point3Y, point3Z, theColour);
  cube.set(point3X, point3Y - 1, point3Z, theColour);
  cube.set(point3X, point3Y, point3Z - 1, theColour);
  cube.set(point4X - 1, point4Y, point4Z, theColour);
  cube.set(point4X, point4Y - 1, point4Z, theColour);
  cube.set(point4X, point4Y, point4Z + 1, theColour);
  delay(theDelay);

  cube.set(point2X + 2, point2Y, point2Z, theColour);
  cube.set(point2X, point2Y + 2, point2Z, theColour);
  cube.set(point2X, point2Y, point2Z + 2, theColour);
  cube.set(point3X + 2, point3Y, point3Z, theColour);
  cube.set(point3X, point3Y - 2, point3Z, theColour);
  cube.set(point3X, point3Y, point3Z - 2, theColour);
  cube.set(point4X - 2, point4Y, point4Z, theColour);
  cube.set(point4X, point4Y - 2, point4Z, theColour);
  cube.set(point4X, point4Y, point4Z + 2, theColour);
  delay(theDelay);

  cube.set(point2X + 3, point2Y, point2Z, theColour);
  cube.set(point2X, point2Y + 3, point2Z, theColour);
  cube.set(point2X, point2Y, point2Z + 3, theColour);
  cube.set(point3X + 3, point3Y, point3Z, theColour);
  cube.set(point3X, point3Y - 3, point3Z, theColour);
  cube.set(point3X, point3Y, point3Z - 3, theColour);
  cube.set(point4X - 3, point4Y, point4Z, theColour);
  cube.set(point4X, point4Y - 3, point4Z, theColour);
  cube.set(point4X, point4Y, point4Z + 3, theColour);
  delay(theDelay * 3);
}

