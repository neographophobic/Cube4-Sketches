
/*
 * File:    RandomPull.ino
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
  int points[16];
  int x0Points[16] = {1, 2, 3, 4, 17, 18, 19, 20, 33, 34, 35, 36, 49, 50, 51, 52};
  int x3Points[16] = {13, 14, 15, 16, 29, 30, 31, 32, 45, 46, 47, 48, 61, 62, 63, 64};
  int y0Points[16] = {1, 5, 9, 13, 17, 21, 25, 29, 33, 37, 41, 45, 49, 53, 57, 61};
  int y3Points[16] = {4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64};
  int z0Points[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  int z3Points[16] = {49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64};

  buildLEDsArray();

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

  delay(theDelay);

  // Shuffle the array, so that we can illumante all LEDs in
  // a random order
  shuffle(points, 16);

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

  // Loop through the shuffled array, turning the LEDs on
  for (byte j = 0; j < 19; j++) {
    for (byte i = 0; i < 16; i++) {
      if (offset == 0) {
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


