
/*
 * File:    RandomPull.ino
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
    serial->println("Random Pull v1.0");
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

  if(axis == 'X' && offset == 0) {
    for (byte i = 0; i < 16; i++) {
      points[i] = x0Points[i]; 
    }
    cube.setplane(X, 0, theColour);
  }
  if(axis == 'X' && offset == 3) {
    for (byte i = 0; i < 16; i++) {
      points[i] = x3Points[i]; 
    }
    cube.setplane(X, 3, theColour);    
  }
  if(axis == 'Y' && offset == 0) {
    for (byte i = 0; i < 16; i++) {
      points[i] = y0Points[i]; 
    }
    cube.setplane(Y, 0, theColour);
  }
  if(axis == 'Y' && offset == 3) {
    for (byte i = 0; i < 16; i++) {
      points[i] = y3Points[i]; 
    }    
    cube.setplane(Y, 3, theColour);
  }
  if(axis == 'Z' && offset == 0) {
    for (byte i = 0; i < 16; i++) {
      points[i] = z0Points[i]; 
    }    
    cube.setplane(Z, 0, theColour);
  }
  if(axis == 'Z' && offset == 3) {
    for (byte i = 0; i < 16; i++) {
      points[i] = z3Points[i]; 
    }    
    cube.setplane(Z, 3, theColour);
  }
  
  delay(theDelay);
  
  // Shuffle the array, so that we can illumante all LEDs in
  // a random order
  shuffle(points, 16);

  // Loop through the shuffled array, turning the LEDs on
  for (int i = 0; i < 16; i++) {
    if (offset == 0) {
      moveLED(points[i], axis, '+', theColour, theDelay); 
    } else {
      moveLED(points[i], axis, '-', theColour, theDelay); 
    }
  }

}

void moveLED(int ledPosition, byte axis, byte moveDirection, rgb_t theColour, int theDelay)
{
  byte X;
  byte Y;
  byte Z;
  
  // Based on the position, set the LED that matches to theColour
  switch (ledPosition)
  {
    case 1:
      X = 0;
      Y = 0;
      Z = 0;
      break;
    case 2:
      X = 0;
      Y = 1;
      Z = 0;
      break;
    case 3:
      X = 0;
      Y = 2;
      Z = 0;
      break;
    case 4:
      X = 0;
      Y = 3;
      Z = 0;
      break;
    case 5:
      X = 1;
      Y = 0;
      Z = 0;
      break;
    case 6:
      X = 1;
      Y = 1;
      Z = 0;
      break;
    case 7:
      X = 1;
      Y = 2;
      Z = 0;
      break;
    case 8:
      X = 1;
      Y = 3;
      Z = 0;
      break;
    case 9:
      X = 2;
      Y = 0;
      Z = 0;
      break;
    case 10:
      X = 2;
      Y = 1;
      Z = 0;
      break;
    case 11:
      X = 2;
      Y = 2;
      Z = 0;
      break;
    case 12:
      X = 2;
      Y = 3;
      Z = 0;
      break;
    case 13:
      X = 3;
      Y = 0;
      Z = 0;
      break;
    case 14:
      X = 3;
      Y = 1;
      Z = 0;
      break;
    case 15:
      X = 3;
      Y = 2;
      Z = 0;
      break;
    case 16:
      X = 3;
      Y = 3;
      Z = 0;
      break;
    case 17:
      X = 0;
      Y = 0;
      Z = 1;
      break;
    case 18:
      X = 0;
      Y = 1;
      Z = 1;
      break;
    case 19:
      X = 0;
      Y = 2;
      Z = 1;
      break;
    case 20:
      X = 0;
      Y = 3;
      Z = 1;
      break;
    case 21:
      X = 1;
      Y = 0;
      Z = 1;
      break;
    case 22:
      X = 1;
      Y = 1;
      Z = 1;
      break;
    case 23:
      X = 1;
      Y = 2;
      Z = 1;
      break;
    case 24:
      X = 1;
      Y = 3;
      Z = 1;
      break;
    case 25:
      X = 2;
      Y = 0;
      Z = 1;
      break;
    case 26:
      X = 2;
      Y = 1;
      Z = 1;
      break;
    case 27:
      X = 2;
      Y = 2;
      Z = 1;
      break;
    case 28:
      X = 2;
      Y = 3;
      Z = 1;
      break;
    case 29:
      X = 3;
      Y = 0;
      Z = 1;
      break;
    case 30:
      X = 3;
      Y = 1;
      Z = 1;
      break;
    case 31:
      X = 3;
      Y = 2;
      Z = 1;
      break;
    case 32:
      X = 3;
      Y = 3;
      Z = 1;
      break;
    case 33:
      X = 0;
      Y = 0;
      Z = 2;
      break;
    case 34:
      X = 0;
      Y = 1;
      Z = 2;
      break;
    case 35:
      X = 0;
      Y = 2;
      Z = 2;
      break;
    case 36:
      X = 0;
      Y = 3;
      Z = 2;
      break;
    case 37:
      X = 1;
      Y = 0;
      Z = 2;
      break;
    case 38:
      X = 1;
      Y = 1;
      Z = 2;
      break;
    case 39:
      X = 1;
      Y = 2;
      Z = 2;
      break;
    case 40:
      X = 1;
      Y = 3;
      Z = 2;
      break;
    case 41:
      X = 2;
      Y = 0;
      Z = 2;
      break;
    case 42:
      X = 2;
      Y = 1;
      Z = 2;
      break;
    case 43:
      X = 2;
      Y = 2;
      Z = 2;
      break;
    case 44:
      X = 2;
      Y = 3;
      Z = 2;
      break;
    case 45:
      X = 3;
      Y = 0;
      Z = 2;
      break;
    case 46:
      X = 3;
      Y = 1;
      Z = 2;
      break;
    case 47:
      X = 3;
      Y = 2;
      Z = 2;
      break;
    case 48:
      X = 3;
      Y = 3;
      Z = 2;
      break;
    case 49:
      X = 0;
      Y = 0;
      Z = 3;
      break;
    case 50:
      X = 0;
      Y = 1;
      Z = 3;
      break;
    case 51:
      X = 0;
      Y = 2;
      Z = 3;
      break;
    case 52:
      X = 0;
      Y = 3;
      Z = 3;
      break;
    case 53:
      X = 1;
      Y = 0;
      Z = 3;
      break;
    case 54:
      X = 1;
      Y = 1;
      Z = 3;
      break;
    case 55:
      X = 1;
      Y = 2;
      Z = 3;
      break;
    case 56:
      X = 1;
      Y = 3;
      Z = 3;
      break;
    case 57:
      X = 2;
      Y = 0;
      Z = 3;
      break;
    case 58:
      X = 2;
      Y = 1;
      Z = 3;
      break;
    case 59:
      X = 2;
      Y = 2;
      Z = 3;
      break;
    case 60:
      X = 2;
      Y = 3;
      Z = 3;
      break;
    case 61:
      X = 3;
      Y = 0;
      Z = 3;
      break;
    case 62:
      X = 3;
      Y = 1;
      Z = 3;
      break;
    case 63:
      X = 3;
      Y = 2;
      Z = 3;
      break;
    case 64:
      X = 3;
      Y = 3;
      Z = 3;
      break;
  }

  if (moveDirection == '+') {
    for (int i = 1; i <= 3; i++) {
      if (axis == 'X') {
        cube.set(i-1, Y, Z, BLACK);
        cube.set(i, Y, Z, theColour);
      }
      if (axis == 'Y') {
        cube.set(X, i-1, Z, BLACK);
        cube.set(X, i, Z, theColour);
      }
      if (axis == 'Z') {
        cube.set(X, Y, i-1, BLACK);
        cube.set(X, Y, i, theColour);
      }
      delay(theDelay);
    }
  } else {
    for (int i = 2; i >= 0; i--) {
      if (axis == 'X') {
        cube.set(i+1, Y, Z, BLACK);
        cube.set(i, Y, Z, theColour);
      }
      if (axis == 'Y') {
        cube.set(X, i+1, Z, BLACK);
        cube.set(X, i, Z, theColour);
      }
      if (axis == 'Z') {
        cube.set(X, Y, i+1, BLACK);
        cube.set(X, Y, i, theColour);
      }
      delay(theDelay);
    }    
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


