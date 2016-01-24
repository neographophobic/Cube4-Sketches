/*
 * File:      Spiral.ino
 * Purpose:   Spiral pattern for the Freetronics 4x4x4 Cube
 * Author:    Adam Reed (adam@secretcode.ninja)
 * License:   BSD 3-Clause Licence
 */

// Include required libraries
#include <SPI.h>
#include "Cube.h"
#include "Cube4_ARUtils.h"

// Create an instance of the cube class
Cube cube;

// leds is an array of the x,y,z coordinates of each of the LEDs in our
// cube.
struct coordinate leds[64];

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

  // Build the full array of LEDs so that we have coordinates to match the above coordinates
  buildLEDsArray(leds);
}

void loop(void) {
  // Set the delay between each part of the animation, and the colour to use
  int theDelay = 100;
  rgb_t theColour = BLUE;

  // Illuminate the "odd" directions (rear to front, left to right, top to bottom)
  for (byte i = 1; i <= 6; i = i + 2) {
    spiral(i, theColour, theDelay);
    spiral(i, BLACK, theDelay);
  }

  // Illuminate the "even" directions (front to rear, right to left, bottom to top)
  for (byte i = 2; i <= 6; i = i + 2) {
    spiral(i, theColour, theDelay);
    spiral(i, BLACK, theDelay);
  }
}

// Sprial illuminates the LEDs around the outside of the cube one after the other in one of the 6 possible directions.
// The directions are:-
//    * 1 rear to front
//    * 2 front to rear
//    * 3 left to right
//    * 4 right to left
//    * 5 top to bottom
//    * 6 bottom to top
void spiral(byte direction, rgb_t theColour, int theDelay)
{
  // How many items there are in the array of coordinates to process
  const int itemsToProcess = 48;

  // Arrays identifying the 48 LEDs that make up the edge coordinates for the animation
  int rearToFront[itemsToProcess] = {64, 48, 32, 16, 15, 14, 13, 29, 45, 61, 62, 63, 60, 44, 28, 12, 11, 10, 9, 25, 41, 57, 58, 59, 56, 40, 24, 8, 7, 6, 5, 21, 37, 53, 54, 55, 52, 36, 20, 4, 3, 2, 1, 17, 33, 49, 50, 51};
  int frontToRear[itemsToProcess] = {52, 36, 20, 4, 3, 2, 1, 17, 33, 49, 50, 51, 56, 40, 24, 8, 7, 6, 5, 21, 37, 53, 54, 55, 60, 44, 28, 12, 11, 10, 9, 25, 41, 57, 58, 59, 64, 48, 32, 16, 15, 14, 13, 29, 45, 61, 62, 63};
  int leftToRight[itemsToProcess] = {49, 33, 17, 1, 5, 9, 13, 29, 45, 61, 57, 53, 50, 34, 18, 2, 6, 10, 14, 30, 46, 62, 58, 54, 51, 35, 19, 3, 7, 11, 15, 31, 47, 63, 59, 55, 52, 36, 20, 4, 8, 12, 16, 32, 48, 64, 60, 56};
  int rightToLeft[itemsToProcess] = {52, 36, 20, 4, 8, 12, 16, 32, 48, 64 , 60 , 56, 51, 35, 19, 3, 7, 11, 15, 31, 47, 63, 59, 55, 50, 34, 18, 2, 6, 10, 14, 30, 46, 62, 58, 54, 49, 33, 17, 1,  5, 9, 13, 29, 45, 61, 57, 53};
  int topToBottom[itemsToProcess] = {64, 60, 56, 52, 51, 50, 49, 53, 57, 61, 62, 63, 48, 44, 40, 36, 35, 34, 33, 37, 41, 45, 46, 47, 32 , 28, 24, 20, 19, 18, 17, 21, 25, 29, 30, 31, 16, 12, 8, 4, 3, 2, 1, 5, 9, 13, 14, 15};
  int bottomToTop[itemsToProcess] = {16, 12, 8, 4, 3, 2, 1, 5, 9, 13, 14, 15, 32 , 28, 24, 20, 19, 18, 17, 21, 25, 29, 30, 31, 48, 44, 40, 36, 35, 34, 33, 37, 41, 45, 46, 47, 64, 60, 56, 52, 51, 50, 49, 53, 57, 61, 62, 63};

  // Loop through the items to total items that we need to progress
  for (byte i = 0; i < itemsToProcess; i++) {
    // From the array of LED positions for a given LED, illuminate the appropriate LED
    switch (direction)
    {
      case 1:
        cube.set(leds[rearToFront[i]].x, leds[rearToFront[i]].y, leds[rearToFront[i]].z, theColour);
        break;
      case 2:
        cube.set(leds[frontToRear[i]].x, leds[frontToRear[i]].y, leds[frontToRear[i]].z, theColour);
        break;
      case 3:
        cube.set(leds[leftToRight[i]].x, leds[leftToRight[i]].y, leds[leftToRight[i]].z, theColour);
        break;
      case 4:
        cube.set(leds[rightToLeft[i]].x, leds[rightToLeft[i]].y, leds[rightToLeft[i]].z, theColour);
        break;
      case 5:
        cube.set(leds[topToBottom[i]].x, leds[topToBottom[i]].y, leds[topToBottom[i]].z, theColour);
        break;
      case 6:
        cube.set(leds[bottomToTop[i]].x, leds[bottomToTop[i]].y, leds[bottomToTop[i]].z, theColour);
        break;
    }
    delay(theDelay);
  }
}


