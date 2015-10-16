
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
// Used to ensure that there isn't a double pause if
// the animation keeps running in a loop
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

  // Loop the animation, starting from position 1 (3,0,0)
  // using the provided colour and delay
  faceExpand(1, theColour, theDelay);
}

void faceExpand(byte startPosition, rgb_t theColour, int theDelay)
{
  // Track the coordinates to use for the boxes we draw
  byte startX;
  byte startY;
  byte startZ;
  byte endX;
  byte endY;
  byte endZ;

  // Track where we are in the animation sequence (there are
  // 4 steps).
  byte move = startPosition;
  byte movesCompleted = 0;

  // Set the start position coordinates based of the users
  // choice.
  switch (startPosition) {
    case 1:
      startX = 3;
      startY = 0;
      startZ = 0;
      break;
    case 2:
      startX = 0;
      startY = 0;
      startZ = 3;
      break;
    case 3:
      startX = 0;
      startY = 3;
      startZ = 0;
      break;
    case 4:
      startX = 3;
      startY = 3;
      startZ = 3;
      break;
  }

  // Match the end coordinates for the box to the start
  // coordinates so that only a single LED is lit up.
  endX = startX;
  endY = startY;
  endZ = startZ;

  if (firstRun)
  {
    // As it's the first time the animation has run, illuminate
    // the start position, and then flag that this isn't
    // required for subsquent loops (as the last step of the loop
    // lights up the start positon for then next time through)
    cube.box(startX, startY, startZ, endX, endY, endZ, theColour);
    delay(theDelay);
    firstRun = false;
  }

  // There are 4 moves to complete, so loop 4 times (starting from zero)
  while (movesCompleted < 4)
  {

    // Expand animation - repeat 3 times.
    for (byte i = 1; i <= 3; i++) {
      // Determine the change in coordinates for the start and end
      // point.
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

      // Draw the box in the given colour and then pause for the
      // provided delay.
      cube.box(startX, startY, startZ, endX, endY, endZ, theColour);
      delay(theDelay);
    }

    // Contract animation - repeat 3 times.
    for (byte i = 1; i <= 3; i++) {
      // Determine the change in coordinates for the start and end
      // point.
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


      // Draw the box in the given colour and then pause for the
      // provided delay, after blanking all of the LEDs.
      cube.all(BLACK);
      cube.box(startX, startY, startZ, endX, endY, endZ, theColour);
      delay(theDelay);
    }

    // Increment the move count
    move++;
    if (move > 4 ) {
      // As we can start at any of the 4 moves, if we get to
      // the 4th one, start back at move 1.
      move = 1;
    }

    // Track how many moves total we have done
    movesCompleted++;
  }
}

