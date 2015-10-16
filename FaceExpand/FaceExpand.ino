
/*
 * File:    FaceExpand.ino
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

/*
 * Don't edit these variables
 */

bool firstRun = true;

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
    serial->println("FaceExpand v1.0");
  }
}

void loop(void) {
  int theDelay = 100;
  rgb_t theColour = GREEN;

  faceExpand(theColour, theDelay);
}

void faceExpand(rgb_t theColour, int theDelay)
{
  byte startX = 3;
  byte startY = 0;
  byte startZ = 0;
  byte endX = startX;
  byte endY = startY;
  byte endZ = startZ;

  byte move = 1;
  bool movesRemaining = true;

  if (firstRun) 
  {
    cube.box(startX, startY, startZ, endX, endY, endZ, theColour); 
    delay(theDelay);
    firstRun = false;
  }
  
  while (movesRemaining)
  {

    // Expand
    for (byte i = 1; i <= 3; i++) {
      switch (move) {
        case 1:
          startX--;
          endZ++;
          break;
        case 2:
          startZ--;
          endY++;
          break;
        case 3:
          endX++;
          endZ++;
          break;
        case 4:
          startY--;
          startZ--;
          break;
      }
      cube.box(startX, startY, startZ, endX, endY, endZ, theColour);
      delay(theDelay);
    }

    // Contract
    for (byte i = 1; i <= 3; i++) {
      switch (move) {
        case 1:
          startZ++;
          endX--;
          break;
        case 2:
          startY++;
          endZ--;
          break;
        case 3:
          startX++;
          startZ++;
          break;
        case 4:
          endY--;
          endZ--;
          break;
      }
      cube.all(BLACK);
      cube.box(startX, startY, startZ, endX, endY, endZ, theColour);
      delay(theDelay);
    }

    move++;
    if (move > 4 ) {
      movesRemaining = false;
    }
  }
}

