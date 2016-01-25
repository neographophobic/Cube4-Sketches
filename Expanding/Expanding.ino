/*
   File:      Expanding.ino
   Purpose:   Expanding pattern for the Freetronics 4x4x4 Cube
   Author:    Adam Reed (adam@secretcode.ninja)
   Licence:   BSD 3-Clause Licence
*/

// Include required libraries
#include <SPI.h>
#include "Cube.h"

/*
   User editable variables
*/
// Define the delay between each step of an animation
int theDelay = 100;

/*
   Don't edit these variables
*/
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
    serial->println("Expanding v1.0");
  }
}

void loop(void) {

  // Clear the cube
  cube.all(BLACK);
  delay(theDelay);

  // Expand out from each of the 8 cornerns
  expand(0, 0, 0, RED, theDelay);
  expand(0, 3, 0, GREEN, theDelay);
  expand(3, 3, 0, BLUE, theDelay);
  expand(3, 0, 0, YELLOW, theDelay);

  expand(0, 0, 3, PINK, theDelay);
  expand(0, 3, 3, WHITE, theDelay);
  expand(3, 3, 3, PURPLE, theDelay);
  expand(3, 0, 3, ORANGE, theDelay);
}

/*
   Expand LEDs from a given start point diagonally, then contract
   them back again.
     x,y,x = Starting position (any of the 8 corners of the cube)
     theColour = The Colour to use for the animation
     theDelay = The delay between each step of the animation
*/
void expand(byte x, byte y, byte z, rgb_t theColour, int theDelay)
{
  // Track the users original starting point
  byte xOrig = x;
  byte yOrig = y;
  byte zOrig = z;

  // Track the start and end point for the box we use to create
  // the animation
  byte startX = x;
  byte startY = y;
  byte startZ = z;
  byte endX = x;
  byte endY = y;
  byte endZ = z;

  // Clear the cube
  cube.all(BLACK);

  // Start by animating the starting coordinate
  cube.set(xOrig, yOrig, zOrig, theColour);
  delay(theDelay);

  // Expand
  for (byte i = 1; i <= 3; i++)
  {
    /*
       There are three expand animation steps
       Depending on where we started from, each step is either
       an addition or subtraction from either the start point,
       or end point for the box. The following if statements
       handle the maths.
    */

    // Bottom Front Left Starting Point (Corner 1)
    if (xOrig == 0 && yOrig == 0 && zOrig == 0) {
      endX++;
      endY++;
      endZ++;
    }

    // Bottom Back Left Starting Point (Corner 2)
    if (xOrig == 0 && yOrig == 3 && zOrig == 0) {
      startY--;
      endX++;
      endZ++;
    }

    // Bottom Back Right Starting Point (Corner 3)
    if (xOrig == 3 && yOrig == 3 && zOrig == 0) {
      startX--;
      startY--;
      endZ++;
    }

    // Bottom Front Right Starting Point (Corner 4)
    if (xOrig == 3 && yOrig == 0 && zOrig == 0) {
      startX--;
      endY++;
      endZ++;
    }

    // Top Front Left Starting Point (Corner 5)
    if (xOrig == 0 && yOrig == 0 && zOrig == 3) {
      startZ--;
      endX++;
      endY++;
    }

    // Top Back Left Starting Point (Corner 6)
    if (xOrig == 0 && yOrig == 3 && zOrig == 3) {
      startY--;
      startZ--;
      endX++;
    }

    // Top Back Right Starting Point (Corner 7)
    if (xOrig == 3 && yOrig == 3 && zOrig == 3) {
      startX--;
      startY--;
      startZ--;
    }

    // Top Front Right Starting Point (Corner 8)
    if (xOrig == 3 && yOrig == 0 && zOrig == 3) {
      startX--;
      startZ--;
      endY++;
    }

    // Draw a filled in box from the calculated start coordinates
    // to the calculated end coordinates in the given colour then
    // pause for the provided delay
    cube.box(startX, startY, startZ, endX, endY, endZ, theColour);
    delay(theDelay);
  }

  // Contract
  for (byte i = 1; i <= 2; i++)
  {
    /*
       There are two contract animation steps
       These steps are the opposite to was was done to expand.

       The starting points refer to where the animation started
       to expand from, not where it's contracting from.
    */

    // Bottom Front Left Starting Point (Corner 1)
    if (xOrig == 0 && yOrig == 0 && zOrig == 0) {
      endX--;
      endY--;
      endZ--;
    }

    // Bottom Back Left Starting Point (Corner 2)
    if (xOrig == 0 && yOrig == 3 && zOrig == 0) {
      startY++;
      endX--;
      endZ--;
    }

    // Bottom Back Right Starting Point (Corner 3)
    if (xOrig == 3 && yOrig == 3 && zOrig == 0) {
      startX++;
      startY++;
      endZ--;
    }

    // Bottom Front Right Starting Point (Corner 4)
    if (xOrig == 3 && yOrig == 0 && zOrig == 0) {
      startX++;
      endY--;
      endZ--;
    }

    // Top Front Left Starting Point (Corner 5)
    if (xOrig == 0 && yOrig == 0 && zOrig == 3) {
      startZ++;
      endX--;
      endY--;
    }

    // Top Back Left Starting Point (Corner 6)
    if (xOrig == 0 && yOrig == 3 && zOrig == 3) {
      startY++;
      startZ++;
      endX--;
    }

    // Top Back Right Starting Point (Corner 7)
    if (xOrig == 3 && yOrig == 3 && zOrig == 3) {
      startX++;
      startY++;
      startZ++;
    }

    // Top Front Right Starting Point (Corner 8)
    if (xOrig == 3 && yOrig == 0 && zOrig == 3) {
      startX++;
      startZ++;
      endY--;
    }

    // Clear the cube, then draw a filled in box from the
    // calculated start coordinates to the calculated end
    // coordinates in the given colour then pause for the
    // provided delay
    cube.all(BLACK);
    cube.box(startX, startY, startZ, endX, endY, endZ, theColour);
    delay(theDelay);
  }

  // Finish the animation by clearing the cube, and then
  // illuminating the original start coordinate for the
  // delay period.
  cube.all(BLACK);
  cube.set(xOrig, yOrig, zOrig, theColour);
  delay(theDelay);
}

