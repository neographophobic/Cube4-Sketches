
/*
 * File:    Spiral.ino
 * Version: 1.0
 * Author:  Adam Reed (adam@secretcode.ninja)
 * License: BSD 3-Clause Licence
 */

#include "SPI.h"
#include "Cube.h"

Cube cube;

struct point
{
  int X;
  int Y;
  int Z;
};

struct point leds[65];

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
    serial->println("Spiral v1.0");
  }
}

/*
 * buildLEDsArray builds an array that holds the location of each LED.
 * It starts at 0,0,0 and works it's way backwards (Y axis), then
 * snaps to the front and starts again. Once the entire bottom plane is
 * done it moves up to the next one and starts again.
 */
void buildLEDsArray() {
  // Start at 0,0,0
  byte X = 0;
  byte Y = 0;
  byte Z = 0;

  for (byte i = 1; i <= 64; i++) {
    // Set the LED position to the current calculated X,Y,Z coordinate
    leds[i].X = X;
    leds[i].Y = Y;
    leds[i].Z = Z;

    // Increment the coordinate in the Y direction
    Y++;

    if (Y == 4) {
      // We have hit the end of the Y's, so snap back to the 0 position, and
      // move to the next X position.
      Y = 0;
      X++;
    }

    if (X == 4) {
      // We have hit the end of the X's, so snap back to the 0 X position
      X = 0;
    }

    switch (i)
    {
      // When we are at position 16, 32, and 48 it's time to move up one Z position
      case 16:
      case 32:
      case 48:
        Z++;
        break;
    }
  }
}

void loop(void) {
  int theDelay = 100;
  rgb_t theColour = BLUE;

  for (byte i = 1; i <= 6; i = i + 2) {
    spiral(i, theColour, theDelay);
    spiral(i, BLACK, theDelay);
  }

  for (byte i = 2; i <= 6; i = i + 2) {
    spiral(i, theColour, theDelay);
    spiral(i, BLACK, theDelay);
  }
}

void spiral(byte direction, rgb_t theColour, int theDelay)
{
  // How many items there are in the array of points to process
  const int itemsToProcess = 48;

  // Arrays identifying the 16 LEDs that make up the edge coordinates for the animation
  int rearToFront[itemsToProcess] = {64, 48, 32, 16, 12, 8, 4, 20, 36, 52, 56, 60, 63, 47, 31, 15, 11, 7, 3, 19, 35, 51, 55, 59, 62, 46, 30, 14, 10, 6, 2, 18, 34, 50, 54, 58, 61, 45, 29, 13, 9, 5, 1, 17, 33, 49, 53, 57};
  int frontToRear[itemsToProcess] = {61, 45, 29, 13, 9, 5, 1, 17, 33, 49, 53, 57, 62, 46, 30, 14, 10, 6, 2, 18, 34, 50, 54, 58, 63, 47, 31, 15, 11, 7, 3, 19, 35, 51, 55, 59, 64, 48, 32, 16, 12, 8, 4, 20, 36, 52, 56, 60};
  int leftToRight[itemsToProcess] = {49, 33, 17, 1, 2, 3, 4, 20, 36, 52, 51, 50, 53, 37, 21, 5, 6, 7, 8, 24, 40, 56, 55, 54, 57, 41, 25, 9, 10, 11, 12, 28, 44, 60, 59, 58, 61, 45, 29, 13, 14, 15, 16, 32, 48, 64, 63, 62};
  int rightToLeft[itemsToProcess] = {61, 45, 29, 13, 14, 15, 16, 32, 48, 64, 63, 62, 57, 41, 25, 9, 10, 11, 12, 28, 44, 60, 59, 58, 53, 37, 21, 5, 6, 7, 8, 24, 40, 56, 55, 54, 49, 33, 17, 1, 2, 3, 4, 20, 36, 52, 51, 50};
  int topToBottom[itemsToProcess] = {64, 63, 62, 61, 57, 53, 49, 50, 51, 52, 56, 60, 48, 47, 46, 45, 41, 37, 33, 34, 35, 36, 40, 44, 32, 31, 30, 29, 25, 21, 17, 18, 19, 20, 24, 28, 16, 15, 14, 13, 9, 5, 1, 2, 3, 4, 8, 12};
  int bottomToTop[itemsToProcess] = {16, 15, 14, 13, 9, 5, 1, 2, 3, 4, 8, 12, 32, 31, 30, 29, 25, 21, 17, 18, 19, 20, 24, 28, 48, 47, 46, 45, 41, 37, 33, 34, 35, 36, 40, 44, 64, 63, 62, 61, 57, 53, 49, 50, 51, 52, 56, 60};

  // Build the full array of LEDs so that we have coordinates to match the above points
  buildLEDsArray();

  // Copy the array of points to use
  for (byte i = 0; i < itemsToProcess; i++) {
    switch (direction)
    {
      case 1:
        cube.set(leds[rearToFront[i]].X, leds[rearToFront[i]].Y, leds[rearToFront[i]].Z, theColour);
        break;
      case 2:
        cube.set(leds[frontToRear[i]].X, leds[frontToRear[i]].Y, leds[frontToRear[i]].Z, theColour);
        break;
      case 3:
        cube.set(leds[leftToRight[i]].X, leds[leftToRight[i]].Y, leds[leftToRight[i]].Z, theColour);
        break;
      case 4:
        cube.set(leds[rightToLeft[i]].X, leds[rightToLeft[i]].Y, leds[rightToLeft[i]].Z, theColour);
        break;
      case 5:
        cube.set(leds[topToBottom[i]].X, leds[topToBottom[i]].Y, leds[topToBottom[i]].Z, theColour);
        break;
      case 6:
        cube.set(leds[bottomToTop[i]].X, leds[bottomToTop[i]].Y, leds[bottomToTop[i]].Z, theColour);
        break;
    }
    delay(theDelay);
  }
}


