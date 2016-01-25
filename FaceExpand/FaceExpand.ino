/*
   File:      FaceExpand.ino
   Purpose:   FaceExpand pattern for the Freetronics 4x4x4 Cube
   Author:    Adam Reed (adam@secretcode.ninja)
   Licence:   BSD 3-Clause Licence
*/

// Include required libraries
#include <SPI.h>
#include "Cube.h"
#include "Cube4_ARUtils.h"

/*
   User editable variables
*/


/*
   Don't edit these variables
*/
// Create an instance of the cube class
Cube cube;

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
  int theDelay = 75;
  rgb_t theColour = GREEN;

  // Loop the animation, starting from position 5 (0,0,0)
  // using the provided colour and delay
  faceExpand(5, theColour, theDelay);
}

/*
   faceExpands starts in a corner then diagnoally expands to the
   other corner on the same face. It then contracts in the same
   maner towards the opposite corner. It requires the colour to
   use, and the delay between each frame. Finally it also requires
   a starting position. The valid positions are:-

      1: 3,0,0 moving right to left (towards 0,0,3) (Corner 4 -> Corner 5)
      2: 0,0,3 moving top to bottom (towards 0,3,0) (Corner 5 -> Corner 2)
      3: 0,3,0 moving left to right (towards 3,3,3) (Corner 2 -> Corner 7)
      4: 3,3,3 moving top to bottom (towards 0,0,0) (Corner 7 -> Corner 1)

      5: 0,0,0 moving left to right (towards 3,0,3) (Corner 1 -> Corner 8)
      6: 3,0,3 moving top to bottom (towards 3,3,0) (Corner 8 -> Corner 3)
      7: 3,3,0 moving right to left (towards 0,3,3) (Corner 3 -> Corner 6)
      8: 0,3,3 moving top to bottom (towards 0,0,0) (Corner 6 -> Corner 1)
*/
void faceExpand(byte startPosition, rgb_t theColour, int theDelay)
{
  // Track the coordinates to use for the boxes we draw
  struct coordinate start;
  struct coordinate end;

  // Track where we are in the animation sequence (there are
  // 4 steps).
  byte move = startPosition;
  byte movesCompleted = 0;

  // Track whether we are moving left to right (moves 5 -> 8)
  // or right to left (moves 1 -> 4)
  bool leftToRightMovement = true;
  if (startPosition <= 4) {
    leftToRightMovement = false;
  }

  // Set the start position coordinates based of the users
  // choice.
  switch (startPosition) {
    case 1:
      start.x = 3;
      start.y = 0;
      start.z = 0;
      break;
    case 2:
      start.x = 0;
      start.y = 0;
      start.z = 3;
      break;
    case 3:
      start.x = 0;
      start.y = 3;
      start.z = 0;
      break;
    case 4:
      start.x = 3;
      start.y = 3;
      start.z = 3;
      break;
    case 5:
      start.x = 0;
      start.y = 0;
      start.z = 0;
      break;
    case 6:
      start.x = 3;
      start.y = 0;
      start.z = 3;
      break;
    case 7:
      start.x = 3;
      start.y = 3;
      start.z = 0;
      break;
    case 8:
      start.x = 0;
      start.y = 3;
      start.z = 3;
      break;
  }

  // Match the end coordinates for the box to the start
  // coordinates so that only a single LED is lit up.
  end.x = start.x;
  end.y = start.y;
  end.z = start.z;

  if (firstRun)
  {
    // As it's the first time the animation has run, illuminate
    // the start position, and then flag that this isn't
    // required for subsquent loops (as the last step of the loop
    // lights up the start positon for then next time through)
    cube.box(start.x, start.y, start.z, end.x, end.y, end.z, theColour);
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
          start.x--;
          end.z++;
          break;
        case 2:
          start.z--;
          end.y++;
          break;
        case 3:
          end.x++;
          end.z++;
          break;
        case 4:
          start.y--;
          start.z--;
          break;
        case 5:
          end.x++;
          end.z++;
          break;
        case 6:
          start.z--;
          end.y++;
          break;
        case 7:
          start.x--;
          end.z++;
          break;
        case 8:
          start.y--;
          start.z--;
          break;
      }

      // Draw the box in the given colour and then pause for the
      // provided delay.
      cube.box(start.x, start.y, start.z, end.x, end.y, end.z, theColour);
      delay(theDelay);
    }

    // Contract animation - repeat 3 times.
    for (byte i = 1; i <= 3; i++) {
      // Determine the change in coordinates for the start and end
      // point.
      switch (move) {
        case 1:
          start.z++;
          end.x--;
          break;
        case 2:
          start.y++;
          end.z--;
          break;
        case 3:
          start.x++;
          start.z++;
          break;
        case 4:
          end.y--;
          end.z--;
          break;
        case 5:
          start.x++;
          start.z++;
          break;
        case 6:
          start.y++;
          end.z--;
          break;
        case 7:
          start.z++;
          end.x--;
          break;
        case 8:
          end.y--;
          end.z--;
          break;
      }

      // Draw the box in the given colour and then pause for the
      // provided delay, after blanking all of the LEDs.
      cube.all(BLACK);
      cube.box(start.x, start.y, start.z, end.x, end.y, end.z, theColour);
      delay(theDelay);
    }

    // Increment the move count
    move++;
    if (leftToRightMovement && move > 8 ) {
      // As we can start at any of the 4 moves (5 to 8) that move
      // left to right, if we get to the 8th one, start back at
      // move 5.
      move = 5;
    }

    if (!leftToRightMovement && move > 4 ) {
      // As we can start at any of the 4 moves (1 to 4) that move
      // right to left, if we get to the 4th one, start back at
      // move 1.
      move = 1;
    }

    // Track how many moves total we have done
    movesCompleted++;
  }
}

