/*
 * File:    Snake.ino
 * Version: 1.0
 * Author:  Adam Reed (adam@secretcode.ninja)
 * License: BSD 3-Clause Licence
 *
 * Inspired by Trilobyte Projects "4x4x4 Led cube demo"
 * at https://www.youtube.com/watch?v=adXXSitxPdo&t=7
 */

#include "SPI.h"
#include "Cube.h"

Cube cube;

/*
 * User editable variables
 */

// Define the colour to use
rgb_t theColour = GREEN;

// Define the delay between lighting up each LED
int theDelay = 100;

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
    serial->println("Snake v1.0");
  }
}

void loop(void) {
  snake(3, 3, 0, theColour);
  snake(3, 3, 0, BLACK);
}

void snake(byte xPos, byte yPos, byte zPos, rgb_t theColour)
{
  // Indicate whether the snake is moving left to right, or right to left
  // - X Direction
  bool leftToRightMovement = false;
  if (xPos == 0) {
    leftToRightMovement = true;
  }

  // Indicate whether the snake is moving top to bottom, or bottom to top
  // - Z Direction
  bool topToBottom = false;
  if (zPos == 3) {
    topToBottom = true;
  }

  // Counters to track our position for X and Z planes
  int xLoop = 0;
  int zLoop = 0;

  // Outer loop ensures we light up the LEDs from the top to bottom, or
  // bottom to top, depending on our given "Z" direction information
  while (zLoop < 4)
  {

    // The inner loop lights up a given LED, and ensures that all LEDs
    // are lit up in its row based of the direction (X) we are moving
    // one at a time until all 4 are lit.
    while (xLoop < 4)
    {
      // Light up the LED
      cube.set(xPos, yPos, zPos, theColour);

      // Wait the provided time
      delay(theDelay);

      // Move to the next LED based off our X direction
      if (leftToRightMovement) {
        xPos++; // Next LED to the right
      } else {
        xPos--; // Next LED to the left
      }

      // Increment loop counter
      xLoop++;
    }

    // Ensure that when we are at the edge of the cube, the X position
    // is correctly set for the next interation, and that we flip the
    // left to right movement direction
    if (leftToRightMovement) {
      leftToRightMovement = false;
      xPos = 3;
    } else {
      leftToRightMovement = true;
      xPos = 0;
    }

    // Set the Z plane to work with based on the direction up or down we
    // are moving
    if (topToBottom) {
      zPos--;
    } else {
      zPos++;
    }

    // Reset the X Loop so that all 4 planes are lit up
    xLoop = 0;

    // Increment loop counter
    zLoop++;
  }

  // Handle movement in the Y direction
  if (yPos != 0) {
    // We aren't at the front of the cube, so move forward
    yPos--;

    // Ensure that when we are at the edge of the cube, the Z position
    // is correctly set for the next interation, and recursively call
    // the snake function to handle it.
    if (topToBottom) {
      zPos = 0;
    } else {
      zPos = 3;
    }
    snake(xPos, yPos, zPos, theColour);
  }
}

