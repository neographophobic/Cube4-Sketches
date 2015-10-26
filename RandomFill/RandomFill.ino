
/*
 * File:    RandomFill.ino
 * Version: 1.0
 * Author:  Adam Reed (adam@secretcode.ninja)
 * License: BSD 3-Clause Licence
 * 
 * Inspired by Trilobyte Projects "4x4x4 Led cube demo"
 * at https://www.youtube.com/watch?v=adXXSitxPdo&t=111
 */

#include "SPI.h"
#include "Cube.h"

Cube cube;

/*
 * User editable variables
 */

// USER_DEFINED_COLOURS should be set to the total number
// of colours we can randomly select from
#define USER_DEFINED_COLOURS 8

// The colours to randomly select from
rgb_t colours[USER_DEFINED_COLOURS] = {BLUE, GREEN, ORANGE, PINK, PURPLE, RED, WHITE, YELLOW};

// How long to pause before moving to the next LED
int theDelay = 25;

// How long to pause before we start turning the LEDs off
int middleDelay = 200;
  
/*
 * Don't edit these variables
 */
#define TOTAL_LEDS 64     // Set the total number of LEDs in the cube
int points[TOTAL_LEDS];
  
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
    serial->println("RandomFill v1.0");
  }

  // Populate an array of points from 1 to 64, so that we
  // can later shuffle the order
  for (int i = 0; i < TOTAL_LEDS; i++) {
    points[i] = i + 1;
  }
}

void loop(void) {
  // Shuffle the array, so that we can illumante all LEDs in
  // a random order
  shuffle(points, TOTAL_LEDS);

  // Loop through the shuffled array, turning the LEDs on
  for (int i = 0; i < TOTAL_LEDS; i++) {
    byte randomColour = random(0, USER_DEFINED_COLOURS);

    setLED(points[i], colours[randomColour]);
    delay(theDelay);  
  }

  // Add an extended pause in the middle of the sequence
  delay(middleDelay);
  
  // Loop through the array (in the same order as before)
  // turning the LEDs off
  for (int i = 0; i < TOTAL_LEDS; i++) {
    setLED(points[i], BLACK);
    delay(theDelay);
  }

  // Add an extended pause at the end of the sequence
  delay(middleDelay);
}

void setLED(int position, rgb_t theColour)
{
  // Based on the position, set the LED that matches to theColour
  switch (position)
  {
    case 1:
      cube.set(0,0,0, theColour);
      break;
    case 2:
      cube.set(0, 1, 0, theColour);
      break;
    case 3:
      cube.set(0, 2, 0, theColour);
      break;
    case 4:
      cube.set(0, 3, 0, theColour);
      break;
    case 5:
      cube.set(1, 0, 0, theColour);
      break;
    case 6:
      cube.set(1, 1, 0, theColour);
      break;
    case 7:
      cube.set(1, 2, 0, theColour);
      break;
    case 8:
      cube.set(1, 3, 0, theColour);
      break;
    case 9:
      cube.set(2, 0, 0, theColour);
      break;
    case 10:
      cube.set(2, 1, 0, theColour);
      break;
    case 11:
      cube.set(2, 2, 0, theColour);
      break;
    case 12:
      cube.set(2, 3, 0, theColour);
      break;
    case 13:
      cube.set(3, 0, 0, theColour);
      break;
    case 14:
      cube.set(3, 1, 0, theColour);
      break;
    case 15:
      cube.set(3, 2, 0, theColour);
      break;
    case 16:
      cube.set(3, 3, 0, theColour);
      break;
    case 17:
      cube.set(0, 0, 1, theColour);
      break;
    case 18:
      cube.set(0, 1,1, theColour);
      break;
    case 19:
      cube.set(0, 2,1, theColour);
      break;
    case 20:
      cube.set(0, 3,1, theColour);
      break;
    case 21:
      cube.set(1,0,1, theColour);
      break;
    case 22:
      cube.set(1,1,1, theColour);
      break;
    case 23:
      cube.set(1,2,1, theColour);
      break;
    case 24:
      cube.set(1,3,1, theColour);
      break;
    case 25:
      cube.set(2,0,1, theColour);
      break;
    case 26:
      cube.set(2,1,1, theColour);
      break;
    case 27:
      cube.set(2,2,1, theColour);
      break;
    case 28:
      cube.set(2,3,1, theColour);
      break;
    case 29:
      cube.set(3,0,1, theColour);
      break;
    case 30:
      cube.set(3,1,1, theColour);
      break;
    case 31:
      cube.set(3,2,1, theColour);
      break;
    case 32:
      cube.set(3,3,1, theColour);
      break;
    case 33:
      cube.set(0,0,2, theColour);
      break;
    case 34:
      cube.set(0,1,2, theColour);
      break;
    case 35:
      cube.set(0,2,2, theColour);
      break;
    case 36:
      cube.set(0,3,2, theColour);
      break;
    case 37:
      cube.set(1,0,2, theColour);
      break;
    case 38:
      cube.set(1,1,2, theColour);
      break;
    case 39:
      cube.set(1,2,2, theColour);
      break;
    case 40:
      cube.set(1,3,2, theColour);
      break;
    case 41:
      cube.set(2,0,2, theColour);
      break;
    case 42:
      cube.set(2,1,2, theColour);
      break;
    case 43:
      cube.set(2,2,2, theColour);
      break;
    case 44:
      cube.set(2,3,2, theColour);
      break;
    case 45:
      cube.set(3,0,2, theColour);
      break;
    case 46:
      cube.set(3,1,2, theColour);
      break;
    case 47:
      cube.set(3,2,2, theColour);
      break;
    case 48:
      cube.set(3,3,2, theColour);
      break;
    case 49:
      cube.set(0,0,3, theColour);
      break;
    case 50:
      cube.set(0,1,3, theColour);
      break;
    case 51:
      cube.set(0,2,3, theColour);
      break;
    case 52:
      cube.set(0,3,3, theColour);
      break;
    case 53:
      cube.set(1,0,3, theColour);
      break;
    case 54:
      cube.set(1,1,3, theColour);
      break;
    case 55:
      cube.set(1,2,3, theColour);
      break;
    case 56:
      cube.set(1,3,3, theColour);
      break;
    case 57:
      cube.set(2,0,3, theColour);
      break;
    case 58:
      cube.set(2,1,3, theColour);
      break;
    case 59:
      cube.set(2,2,3, theColour);
      break;
    case 60:
      cube.set(2,3,3, theColour);
      break;
    case 61:
      cube.set(3,0,3, theColour);
      break;
    case 62:
      cube.set(3,1,3, theColour);
      break;
    case 63:
      cube.set(3,2,3, theColour);
      break;
    case 64:
      cube.set(3,3,3, theColour);
      break;
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

