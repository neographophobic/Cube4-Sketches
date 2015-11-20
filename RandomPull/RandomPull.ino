
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

void buildLEDsArray() {
  // Record what each point is
  leds[1].X = 0;  leds[1].Y = 0;  leds[1].Z = 0;
  leds[2].X = 0;  leds[2].Y = 1;  leds[2].Z = 0;
  leds[3].X = 0;  leds[3].Y = 2;  leds[3].Z = 0;
  leds[4].X = 0;  leds[4].Y = 3;  leds[4].Z = 0;
  leds[5].X = 1;  leds[5].Y = 0;  leds[5].Z = 0;
  leds[6].X = 1;  leds[6].Y = 1;  leds[6].Z = 0;
  leds[7].X = 1;  leds[7].Y = 2;  leds[7].Z = 0;
  leds[8].X = 1;  leds[8].Y = 3;  leds[8].Z = 0;
  leds[9].X = 2;  leds[9].Y = 0;  leds[9].Z = 0;
  leds[10].X = 2;  leds[10].Y = 1;  leds[10].Z = 0;
  leds[11].X = 2;  leds[11].Y = 2;  leds[11].Z = 0;
  leds[12].X = 2;  leds[12].Y = 3;  leds[12].Z = 0;
  leds[13].X = 3;  leds[13].Y = 0;  leds[13].Z = 0;
  leds[14].X = 3;  leds[14].Y = 1;  leds[14].Z = 0;
  leds[15].X = 3;  leds[15].Y = 2;  leds[15].Z = 0;
  leds[16].X = 3;  leds[16].Y = 3;  leds[16].Z = 0;
  leds[17].X = 0;  leds[17].Y = 0;  leds[17].Z = 1;
  leds[18].X = 0;  leds[18].Y = 1;  leds[18].Z = 1;
  leds[19].X = 0;  leds[19].Y = 2;  leds[19].Z = 1;
  leds[20].X = 0;  leds[20].Y = 3;  leds[20].Z = 1;
  leds[21].X = 1;  leds[21].Y = 0;  leds[21].Z = 1;
  leds[22].X = 1;  leds[22].Y = 1;  leds[22].Z = 1;
  leds[23].X = 1;  leds[23].Y = 2;  leds[23].Z = 1;
  leds[24].X = 1;  leds[24].Y = 3;  leds[24].Z = 1;
  leds[25].X = 2;  leds[25].Y = 0;  leds[25].Z = 1;
  leds[26].X = 2;  leds[26].Y = 1;  leds[26].Z = 1;
  leds[27].X = 2;  leds[27].Y = 2;  leds[27].Z = 1;
  leds[28].X = 2;  leds[28].Y = 3;  leds[28].Z = 1;
  leds[29].X = 3;  leds[29].Y = 0;  leds[29].Z = 1;
  leds[30].X = 3;  leds[30].Y = 1;  leds[30].Z = 1;
  leds[31].X = 3;  leds[31].Y = 2;  leds[31].Z = 1;
  leds[32].X = 3;  leds[32].Y = 3;  leds[32].Z = 1;
  leds[33].X = 0;  leds[33].Y = 0;  leds[33].Z = 2;
  leds[34].X = 0;  leds[34].Y = 1;  leds[34].Z = 2;
  leds[35].X = 0;  leds[35].Y = 2;  leds[35].Z = 2;
  leds[36].X = 0;  leds[36].Y = 3;  leds[36].Z = 2;
  leds[37].X = 1;  leds[37].Y = 0;  leds[37].Z = 2;
  leds[38].X = 1;  leds[38].Y = 1;  leds[38].Z = 2;
  leds[39].X = 1;  leds[39].Y = 2;  leds[39].Z = 2;
  leds[40].X = 1;  leds[40].Y = 3;  leds[40].Z = 2;
  leds[41].X = 2;  leds[41].Y = 0;  leds[41].Z = 2;
  leds[42].X = 2;  leds[42].Y = 1;  leds[42].Z = 2;
  leds[43].X = 2;  leds[43].Y = 2;  leds[43].Z = 2;
  leds[44].X = 2;  leds[44].Y = 3;  leds[44].Z = 2;
  leds[45].X = 3;  leds[45].Y = 0;  leds[45].Z = 2;
  leds[46].X = 3;  leds[46].Y = 1;  leds[46].Z = 2;
  leds[47].X = 3;  leds[47].Y = 2;  leds[47].Z = 2;
  leds[48].X = 3;  leds[48].Y = 3;  leds[48].Z = 2;
  leds[49].X = 0;  leds[49].Y = 0;  leds[49].Z = 3;
  leds[50].X = 0;  leds[50].Y = 1;  leds[50].Z = 3;
  leds[51].X = 0;  leds[51].Y = 2;  leds[51].Z = 3;
  leds[52].X = 0;  leds[52].Y = 3;  leds[52].Z = 3;
  leds[53].X = 1;  leds[53].Y = 0;  leds[53].Z = 3;
  leds[54].X = 1;  leds[54].Y = 1;  leds[54].Z = 3;
  leds[55].X = 1;  leds[55].Y = 2;  leds[55].Z = 3;
  leds[56].X = 1;  leds[56].Y = 3;  leds[56].Z = 3;
  leds[57].X = 2;  leds[57].Y = 0;  leds[57].Z = 3;
  leds[58].X = 2;  leds[58].Y = 1;  leds[58].Z = 3;
  leds[59].X = 2;  leds[59].Y = 2;  leds[59].Z = 3;
  leds[60].X = 2;  leds[60].Y = 3;  leds[60].Z = 3;
  leds[61].X = 3;  leds[61].Y = 0;  leds[61].Z = 3;
  leds[62].X = 3;  leds[62].Y = 1;  leds[62].Z = 3;
  leds[63].X = 3;  leds[63].Y = 2;  leds[63].Z = 3;
  leds[64].X = 3;  leds[64].Y = 3;  leds[64].Z = 3;  
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


