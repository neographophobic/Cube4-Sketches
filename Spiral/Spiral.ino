
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

    // Increment the coordinate in the X direction
    X++;

    if (X == 4) {
      // We have hit the end of the X's, so snap back to the 0 position, and
      // move to the next Y position.
      X = 0;
      Y++;
    }

    if (Y == 4) {
      // We have hit the end of the Y's, so snap back to the 0 Y position
      Y = 0;
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
  int rearToFront[itemsToProcess] = {64, 48, 32, 16, 15, 14, 13, 29, 45, 61, 62, 63, 60, 44, 28, 12, 11, 10, 9, 25, 41, 57, 58, 59, 56, 40, 24, 8, 7, 6, 5, 21, 37, 53, 54, 55, 52, 36, 20, 4, 3, 2, 1, 17, 33, 49, 50, 51};
  int frontToRear[itemsToProcess] = {52, 36, 20, 4, 3, 2, 1, 17, 33, 49, 50, 51, 56, 40, 24, 8, 7, 6, 5, 21, 37, 53, 54, 55, 60, 44, 28, 12, 11, 10, 9, 25, 41, 57, 58, 59, 64, 48, 32, 16, 15, 14, 13, 29, 45, 61, 62, 63};
  int leftToRight[itemsToProcess] = {49, 33, 17, 1, 5, 9, 13, 29, 45, 61, 57, 53, 50, 34, 18, 2, 6, 10, 14, 30, 46, 62, 58, 54, 51, 35, 19, 3, 7, 11, 15, 31, 47, 63, 59, 55, 52, 36, 20, 4, 8, 12, 16, 32, 48, 64, 60, 56};
  int rightToLeft[itemsToProcess] = {52, 36, 20, 4, 8, 12, 16, 32, 48, 64 , 60 , 56, 51, 35, 19, 3, 7, 11, 15, 31, 47, 63, 59, 55, 50, 34, 18, 2, 6, 10, 14, 30, 46, 62, 58, 54, 49, 33, 17, 1,  5, 9, 13, 29, 45, 61, 57, 53};
  int topToBottom[itemsToProcess] = {64, 60, 56, 52, 51, 50, 49, 53, 57, 61, 62, 63, 48, 44, 40, 36, 35, 34, 33, 37, 41, 45, 46, 47, 32 , 28, 24, 20, 19, 18, 17, 21, 25, 29, 30, 31, 16, 12, 8, 4, 3, 2, 1, 5, 9, 13, 14, 15};
  int bottomToTop[itemsToProcess] = {16, 12, 8, 4, 3, 2, 1, 5, 9, 13, 14, 15, 32 , 28, 24, 20, 19, 18, 17, 21, 25, 29, 30, 31, 48, 44, 40, 36, 35, 34, 33, 37, 41, 45, 46, 47, 64, 60, 56, 52, 51, 50, 49, 53, 57, 61, 62, 63};

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


