/*
   File:      RandomPull.ino
   Purpose:   pattern for the Freetronics 4x4x4 Cube
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
    serial->println("Random Pull v1.0");
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

  startPlane('X', 0, theColour, theDelay);
  delay(theDelay);
  cube.all(BLACK);

  startPlane('X', 3, theColour, theDelay);
  delay(theDelay);
  cube.all(BLACK);

  startPlane('Y', 0, theColour, theDelay);
  delay(theDelay);
  cube.all(BLACK);

  startPlane('Y', 3, theColour, theDelay);
  delay(theDelay);
  cube.all(BLACK);

  startPlane('Z', 0, theColour, theDelay);
  delay(theDelay);
  cube.all(BLACK);

  startPlane('Z', 3, theColour, theDelay);
  delay(theDelay);
  cube.all(BLACK);
}

void startPlane(byte axis, byte offset, rgb_t theColour, int theDelay)
{
  // Array to hold the locations that we need to work with
  int points[16];

  // Arrays identifying the 16 LEDs that make up the starting grid for the animation
  int x0Points[16] = {1, 2, 3, 4, 17, 18, 19, 20, 33, 34, 35, 36, 49, 50, 51, 52};
  int x3Points[16] = {13, 14, 15, 16, 29, 30, 31, 32, 45, 46, 47, 48, 61, 62, 63, 64};
  int y0Points[16] = {1, 5, 9, 13, 17, 21, 25, 29, 33, 37, 41, 45, 49, 53, 57, 61};
  int y3Points[16] = {4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64};
  int z0Points[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  int z3Points[16] = {49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64};

  // Build the full array of LEDs so that we have coordinates to match the above points
  buildLEDsArray();

  // Copy the starting grid for the given axis and offset into the points array, and then
  // illuminate that axis / offset combo to start the animation
  if (axis == 'X' && offset == 0) {
    for (byte i = 0; i < 16; i++) {
      points[i] = x0Points[i];
    }
    cube.setplane(X, 0, theColour);
  }
  if (axis == 'X' && offset == 3) {
    for (byte i = 0; i < 16; i++) {
      points[i] = x3Points[i];
    }
    cube.setplane(X, 3, theColour);
  }
  if (axis == 'Y' && offset == 0) {
    for (byte i = 0; i < 16; i++) {
      points[i] = y0Points[i];
    }
    cube.setplane(Y, 0, theColour);
  }
  if (axis == 'Y' && offset == 3) {
    for (byte i = 0; i < 16; i++) {
      points[i] = y3Points[i];
    }
    cube.setplane(Y, 3, theColour);
  }
  if (axis == 'Z' && offset == 0) {
    for (byte i = 0; i < 16; i++) {
      points[i] = z0Points[i];
    }
    cube.setplane(Z, 0, theColour);
  }
  if (axis == 'Z' && offset == 3) {
    for (byte i = 0; i < 16; i++) {
      points[i] = z3Points[i];
    }
    cube.setplane(Z, 3, theColour);
  }

  // Pause to ensure the starting position is shown before the animation
  // starts
  delay(theDelay);

  // Shuffle the array, so that we can move the LEDs in the starting grid
  // in a random order
  shuffle(points, 16);

  // Offset the starting position of the given axis so that we can more easily
  // move multiple LEDs at the same time
  int startPosition = offset;
  for (byte i = 0; i < 16; i++) {
    if (axis == 'X') {
      leds[points[i]].X = startPosition;
    }
    if (axis == 'Y') {
      leds[points[i]].Y = startPosition;
    }
    if (axis == 'Z') {
      leds[points[i]].Z = startPosition;
    }
    if (offset == 0) {
      startPosition--;
    } else {
      startPosition++;
    }
  }

  // There are 19 moves in the animation, so loop 19 times to draw each frame
  for (byte j = 0; j < 19; j++) {
    // For each frame, look at each of the possible 16 LEDs, and determine if it should
    // be on or off
    for (byte i = 0; i < 16; i++) {
      if (offset == 0) {
        // Moving in a positive direction, so turn the LED "behind" the given spot off, and
        // the new one on if the axis' position is within the expected range.
        // Regardless of whether it was in range or not, increment it's axis position at the end
        // of processing. This is what allows multiple LEDs to appear to move at once.
        if (axis == 'X') {
          if (leds[points[i]].X >= 1 && leds[points[i]].X <= 3) {
            cube.set(leds[points[i]].X - 1, leds[points[i]].Y, leds[points[i]].Z, BLACK);
            cube.set(leds[points[i]].X, leds[points[i]].Y, leds[points[i]].Z, theColour);
          }
          leds[points[i]].X++;
        }
        if (axis == 'Y') {
          if (leds[points[i]].Y >= 1 && leds[points[i]].Y <= 3) {
            cube.set(leds[points[i]].X, leds[points[i]].Y - 1, leds[points[i]].Z, BLACK);
            cube.set(leds[points[i]].X, leds[points[i]].Y, leds[points[i]].Z, theColour);
          }
          leds[points[i]].Y++;
        }
        if (axis == 'Z') {
          if (leds[points[i]].Z >= 1 && leds[points[i]].Z <= 3) {
            cube.set(leds[points[i]].X, leds[points[i]].Y, leds[points[i]].Z - 1, BLACK);
            cube.set(leds[points[i]].X, leds[points[i]].Y, leds[points[i]].Z, theColour);
          }
          leds[points[i]].Z++;
        }
      } else {
        // Moving in a negative direction, so turn the LED "in front" of the given spot off, and
        // the new one on if the axis' position is within the expected range.
        // Regardless of whether it was in range or not, decrement it's axis position at the end
        // of processing. This is what allows multiple LEDs to appear to move at once.
        if (axis == 'X') {
          if (leds[points[i]].X >= 0 && leds[points[i]].X <= 2) {
            cube.set(leds[points[i]].X + 1, leds[points[i]].Y, leds[points[i]].Z, BLACK);
            cube.set(leds[points[i]].X, leds[points[i]].Y, leds[points[i]].Z, theColour);
          }
          leds[points[i]].X--;
        }
        if (axis == 'Y') {
          if (leds[points[i]].Y >= 0 && leds[points[i]].Y <= 2) {
            cube.set(leds[points[i]].X, leds[points[i]].Y + 1, leds[points[i]].Z, BLACK);
            cube.set(leds[points[i]].X, leds[points[i]].Y, leds[points[i]].Z, theColour);
          }
          leds[points[i]].Y--;
        }
        if (axis == 'Z') {
          if (leds[points[i]].Z >= 0 && leds[points[i]].Z <= 2) {
            cube.set(leds[points[i]].X, leds[points[i]].Y, leds[points[i]].Z + 1, BLACK);
            cube.set(leds[points[i]].X, leds[points[i]].Y, leds[points[i]].Z, theColour);
          }
          leds[points[i]].Z--;
        }
      }
    }
    // Processed each of the 16 LEDs so pause for the given period before trying again
    delay(theDelay);
  }
}

/*
 *  Arrange the N elements of ARRAY in random order.
 *  Only effective if N is much smaller than RAND_MAX;
 *  if this may not be the case, use a better random
 *  number generator.
 *
 *  Code from: http://benpfaff.org/writings/clc/shuffle.html
 *
*/
void shuffle(int *array, size_t n)
{
  if (n > 1) {
    size_t i;
    for (i = 0; i < n - 1; i++) {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}


