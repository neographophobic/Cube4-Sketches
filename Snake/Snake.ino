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
  // Always call as 3,3,3, true
  snake(3, 3, 3, true, theColour);
  snake(3, 3, 3, true, BLACK);
}

void snake(byte xPos, byte yPos, byte zPos, bool topToBottom, rgb_t theColour)
{
  bool forwardMotion = false;

  int xLoop = 0;
  int zLoop = 0;
  while (zLoop < 4)
  {
    while (xLoop < 4)
    {
      cube.set(xPos, yPos, zPos, theColour);
      delay(theDelay);
      if (forwardMotion) {
        xPos++;
      } else {
        xPos--;
      }
      xLoop++;
    }

    if (forwardMotion) {
      forwardMotion = false;
      xPos = 3;
    } else {
      forwardMotion = true;
      xPos = 0;
    }
    if (topToBottom) {
      zPos--;
    } else {
      zPos++;
    }
    xLoop = 0;
    zLoop++;
  }
  if (yPos != 0) {
    yPos--;
    if (topToBottom) {
      zPos = 0;
      snake(xPos, yPos, zPos, false, theColour);
    } else {
      zPos = 3;
      snake(xPos, yPos, zPos, true, theColour);
    }
  }
}

