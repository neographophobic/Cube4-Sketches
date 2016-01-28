/*
   File:      RandomPull.ino
   Purpose:   RandomPull pattern for the Freetronics 4x4x4 Cube
   Author:    Adam Reed (adam@secretcode.ninja)
   Licence:   BSD 3-Clause Licence
*/

// Include required libraries
#include "Cube.h"
#include "Cube4_ARUtils.h"

/*
   User editable variables
*/
// The colour to use for the animation
rgb_t theColour = BLUE;

// The delay between each step of an animation
int theDelay = 100;

/*
   Don't edit these variables
*/
// Create an instance of the cube class
Cube cube;

struct coordinate leds[TOTAL_LEDS];

// The number of LEDs that make up a face
const byte numOfLEDsOnAFace = 16;

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

void loop(void) {
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
  int points[numOfLEDsOnAFace];

  // Arrays identifying the 16 LEDs that make up the starting grid for the animation
  int x0Points[numOfLEDsOnAFace] = {1, 5, 9, 13, 17, 21, 25, 29, 33, 37, 41, 45, 49, 53, 57, 61};
  int x3Points[numOfLEDsOnAFace] = {4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64};
  int y0Points[numOfLEDsOnAFace] = {1, 2, 3, 4, 17, 18, 19, 20, 33, 34, 35, 36, 49, 50, 51, 52};
  int y3Points[numOfLEDsOnAFace] = {13, 14, 15, 16, 29, 30, 31, 32, 45, 46, 47, 48, 61, 62, 63, 64};
  int z0Points[numOfLEDsOnAFace] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  int z3Points[numOfLEDsOnAFace] = {49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64};

  // Rebuild the full array of LEDs so that we have coordinates to match the above points
  buildLEDsArray(leds);

  // Copy the starting grid for the given axis and offset into the points array, and then
  // illuminate that axis / offset combo to start the animation
  if (axis == 'X' && offset == 0) {
    for (byte i = 0; i < numOfLEDsOnAFace; i++) {
      points[i] = x0Points[i];
    }
    cube.setplane(X, 0, theColour);
  }
  if (axis == 'X' && offset == 3) {
    for (byte i = 0; i < numOfLEDsOnAFace; i++) {
      points[i] = x3Points[i];
    }
    cube.setplane(X, 3, theColour);
  }
  if (axis == 'Y' && offset == 0) {
    for (byte i = 0; i < numOfLEDsOnAFace; i++) {
      points[i] = y0Points[i];
    }
    cube.setplane(Y, 0, theColour);
  }
  if (axis == 'Y' && offset == 3) {
    for (byte i = 0; i < numOfLEDsOnAFace; i++) {
      points[i] = y3Points[i];
    }
    cube.setplane(Y, 3, theColour);
  }
  if (axis == 'Z' && offset == 0) {
    for (byte i = 0; i < numOfLEDsOnAFace; i++) {
      points[i] = z0Points[i];
    }
    cube.setplane(Z, 0, theColour);
  }
  if (axis == 'Z' && offset == 3) {
    for (byte i = 0; i < numOfLEDsOnAFace; i++) {
      points[i] = z3Points[i];
    }
    cube.setplane(Z, 3, theColour);
  }

  // Pause to ensure the starting position is shown before the animation
  // starts
  delay(theDelay);

  // Shuffle the array, so that we can move the LEDs in the starting grid
  // in a random order
  shuffle(points, numOfLEDsOnAFace);

  // Offset the starting position of the given axis so that we can more easily
  // move multiple LEDs at the same time
  int startPosition = offset;
  for (byte i = 0; i < numOfLEDsOnAFace; i++) {
    if (axis == 'X') {
      leds[points[i]].x = startPosition;
    }
    if (axis == 'Y') {
      leds[points[i]].y = startPosition;
    }
    if (axis == 'Z') {
      leds[points[i]].z = startPosition;
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
    for (byte i = 0; i < numOfLEDsOnAFace; i++) {
      if (offset == 0) {
        // Moving in a positive direction, so turn the LED "behind" the given spot off, and
        // the new one on if the axis' position is within the expected range.
        // Regardless of whether it was in range or not, increment it's axis position at the end
        // of processing. This is what allows multiple LEDs to appear to move at once.
        if (axis == 'X') {
          if (leds[points[i]].x >= 1 && leds[points[i]].x <= 3) {
            cube.set(leds[points[i]].x - 1, leds[points[i]].y, leds[points[i]].z, BLACK);
            cube.set(leds[points[i]].x, leds[points[i]].y, leds[points[i]].z, theColour);
          }
          leds[points[i]].x++;
        }
        if (axis == 'Y') {
          if (leds[points[i]].y >= 1 && leds[points[i]].y <= 3) {
            cube.set(leds[points[i]].x, leds[points[i]].y - 1, leds[points[i]].z, BLACK);
            cube.set(leds[points[i]].x, leds[points[i]].y, leds[points[i]].z, theColour);
          }
          leds[points[i]].y++;
        }
        if (axis == 'Z') {
          if (leds[points[i]].z >= 1 && leds[points[i]].z <= 3) {
            cube.set(leds[points[i]].x, leds[points[i]].y, leds[points[i]].z - 1, BLACK);
            cube.set(leds[points[i]].x, leds[points[i]].y, leds[points[i]].z, theColour);
          }
          leds[points[i]].z++;
        }
      } else {
        // Moving in a negative direction, so turn the LED "in front" of the given spot off, and
        // the new one on if the axis' position is within the expected range.
        // Regardless of whether it was in range or not, decrement it's axis position at the end
        // of processing. This is what allows multiple LEDs to appear to move at once.
        if (axis == 'X') {
          if (leds[points[i]].x >= 0 && leds[points[i]].x <= 2) {
            cube.set(leds[points[i]].x + 1, leds[points[i]].y, leds[points[i]].z, BLACK);
            cube.set(leds[points[i]].x, leds[points[i]].y, leds[points[i]].z, theColour);
          }
          leds[points[i]].x--;
        }
        if (axis == 'Y') {
          if (leds[points[i]].y >= 0 && leds[points[i]].y <= 2) {
            cube.set(leds[points[i]].x, leds[points[i]].y + 1, leds[points[i]].z, BLACK);
            cube.set(leds[points[i]].x, leds[points[i]].y, leds[points[i]].z, theColour);
          }
          leds[points[i]].y--;
        }
        if (axis == 'Z') {
          if (leds[points[i]].z >= 0 && leds[points[i]].z <= 2) {
            cube.set(leds[points[i]].x, leds[points[i]].y, leds[points[i]].z + 1, BLACK);
            cube.set(leds[points[i]].x, leds[points[i]].y, leds[points[i]].z, theColour);
          }
          leds[points[i]].z--;
        }
      }
    }
    // Processed each of the 16 LEDs so pause for the given period before trying again
    delay(theDelay);
  }
}

