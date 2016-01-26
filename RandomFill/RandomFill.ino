/*
   File:      RandomFill.ino
   Purpose:   RandomFill pattern for the Freetronics 4x4x4 Cube
   Author:    Adam Reed (adam@secretcode.ninja)
   Licence:   BSD 3-Clause Licence

   Inspired by Trilobyte Projects "4x4x4 Led cube demo"
   at https://www.youtube.com/watch?v=adXXSitxPdo&t=111
*/

// Include required libraries
#include <SPI.h>
#include "Cube.h"
#include "Cube4_ARUtils.h"

/*
   User editable variables
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
   Don't edit these variables
*/
#define TOTAL_LEDS 65     // Set the total number of LEDs in the cube
int points[TOTAL_LEDS];
struct coordinate leds[TOTAL_LEDS];

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
    serial->println("RandomFill v1.0");
  }
  // Populate an array of points from 1 to 64, so that we
  // can later shuffle the order
  for (int i = 1; i < TOTAL_LEDS; i++) {
    points[i] = i;
  }

  // Build the full array of LEDs so that we have coordinates to match the above points
  buildLEDsArray(leds);
}

void loop(void) {
  // Shuffle the array, so that we can illumante all LEDs in
  // a random order
  shuffle(points, TOTAL_LEDS);

  // Loop through the shuffled array, turning the LEDs on
  for (int i = 1; i < TOTAL_LEDS; i++) {
    byte randomColour = random(0, USER_DEFINED_COLOURS);

    cube.set(leds[points[i]].x, leds[points[i]].y, leds[points[i]].z, colours[randomColour]);
    delay(theDelay);
  }

  // Add an extended pause in the middle of the sequence
  delay(middleDelay);

  // Loop through the array (in the same order as before)
  // turning the LEDs off
  for (int i = 1; i < TOTAL_LEDS; i++) {
    
    cube.set(leds[points[i]].x, leds[points[i]].y, leds[points[i]].z, BLACK);
    delay(theDelay);
  }

  // Add an extended pause at the end of the sequence
  delay(middleDelay);
}

