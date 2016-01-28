/*
   File:      LoopingBoxes.ino
   Purpose:   Looping Boxes pattern for the Freetronics 4x4x4 Cube
   Author:    Adam Reed (adam@secretcode.ninja)
   Licence:   BSD 3-Clause Licence
*/

// Include required libraries
#include "Cube.h"

/*
   User editable variables
*/
// The colour to use for the inner square
rgb_t innerColour = GREEN;

// The colour to use for the outer square
rgb_t outerColour = RED;

// The delay between each step of an animation
int theDelay = 150;

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
    serial->println("Looping Boxes v1.0");
  }
}

void loop(void) {
  // Move 1
  cube.box(0, 0, 0, 3, 3, 0, outerColour, 2);

  cube.box(1, 1, 3, 2, 2, 3, innerColour, 2);
  delay(theDelay);

  // Move 2
  cube.box(0, 0, 0, 3, 3, 0, BLACK, 2);
  cube.box(0, 0, 1, 3, 3, 1, outerColour, 2);

  cube.box(1, 1, 3, 2, 2, 3, BLACK, 2);
  cube.box(1, 1, 2, 2, 2, 2, innerColour, 2);
  delay(theDelay);

  // Move 3
  cube.box(0, 0, 1, 3, 3, 1, BLACK, 2);
  cube.box(0, 0, 2, 3, 3, 2, outerColour, 2);

  cube.box(1, 1, 2, 2, 2, 2, BLACK, 2);
  cube.box(1, 1, 1, 2, 2, 1, innerColour, 2);
  delay(theDelay);

  // Move 4
  cube.box(0, 0, 2, 3, 3, 2, BLACK, 2);
  cube.box(0, 0, 3, 3, 3, 3, outerColour, 2);

  cube.box(1, 1, 1, 2, 2, 1, BLACK, 2);
  cube.box(1, 1, 0, 2, 2, 0, innerColour, 2);
  delay(theDelay);

  // Move 5
  cube.box(0, 0, 3, 3, 3, 3, BLACK, 2);
  cube.line(1, 0, 3, 1, 3, 3, outerColour);
  cube.line(2, 3, 3, 3, 3, 3, outerColour);
  cube.line(2, 0, 3, 3, 0, 3, outerColour);
  cube.line(3, 0, 2, 3, 3, 2, outerColour);

  cube.box(1, 1, 0, 2, 2, 0, BLACK, 2);
  cube.box(0, 1, 0, 1, 2, 0, innerColour, 2);
  delay(theDelay);

  // Move 6
  cube.line(1, 0, 3, 1, 3, 3, BLACK);
  cube.line(2, 3, 3, 3, 3, 3, BLACK);
  cube.line(2, 0, 3, 3, 0, 3, BLACK);
  cube.line(3, 0, 2, 3, 3, 2, BLACK);
  cube.line(2, 0, 3, 2, 3, 3, outerColour);
  cube.line(3, 0, 2, 3, 0, 3, outerColour);
  cube.line(3, 3, 2, 3, 3, 3, outerColour);
  cube.line(3, 0, 1, 3, 3, 1, outerColour);

  cube.box(0, 1, 0, 1, 2, 0, BLACK, 2);
  cube.box(0, 1, 0, 0, 2, 1, innerColour, 2);
  delay(theDelay);

  // Move 7
  cube.line(2, 0, 3, 2, 3, 3, BLACK);
  cube.line(3, 0, 1, 3, 3, 1, BLACK);
  cube.box(3, 0, 0, 3, 3, 3, outerColour, 2);

  cube.box(0, 1, 0, 0, 2, 1, BLACK, 2);
  cube.box(0, 1, 1, 0, 2, 2, innerColour, 2);
  delay(theDelay);

  // Move 8
  cube.box(3, 0, 0, 3, 3, 3, BLACK, 2);
  cube.box(2, 0, 0, 2, 3, 3, outerColour, 2);

  cube.box(0, 1, 1, 0, 2, 2, BLACK, 2);
  cube.box(1, 1, 1, 1, 2, 2, innerColour, 2);
  delay(theDelay);

  // Move 9
  cube.box(2, 0, 0, 2, 3, 3, BLACK, 2);
  cube.box(1, 0, 0, 1, 3, 3, outerColour, 2);

  cube.box(1, 1, 1, 1, 2, 2, BLACK, 2);
  cube.box(2, 1, 1, 2, 2, 2, innerColour, 2);
  delay(theDelay);

  // Move 10
  cube.box(1, 0, 0, 1, 3, 3, BLACK, 2);
  cube.box(0, 0, 0, 0, 3, 3, outerColour, 2);

  cube.box(2, 1, 1, 2, 2, 2, BLACK, 2);
  cube.box(3, 1, 1, 3, 2, 2, innerColour, 2);
  delay(theDelay);

  // Move 11
  cube.box(0, 0, 0, 0, 3, 3, BLACK, 2);
  cube.line(1, 0, 0, 1, 0, 3, outerColour);
  cube.line(0, 2, 0, 0, 2, 3, outerColour);
  cube.line(0, 0, 0, 0, 1, 0, outerColour);
  cube.line(0, 0, 3, 0, 1, 3, outerColour);

  cube.box(3, 1, 1, 3, 2, 2, BLACK, 2);
  cube.box(3, 2, 1, 3, 3, 2, innerColour, 2);
  delay(theDelay);

  // Move 12
  cube.line(1, 0, 0, 1, 0, 3, BLACK);
  cube.line(0, 2, 0, 0, 2, 3, BLACK);
  cube.line(0, 0, 0, 0, 1, 0, BLACK);
  cube.line(0, 0, 3, 0, 1, 3, BLACK);
  cube.line(2, 0, 0, 2, 0, 3, outerColour);
  cube.line(0, 1, 0, 0, 1, 3, outerColour);
  cube.line(0, 0, 0, 1, 0, 0, outerColour);
  cube.line(0, 0, 3, 1, 0, 3, outerColour);

  cube.box(3, 2, 1, 3, 3, 2, BLACK, 2);
  cube.box(2, 3, 1, 3, 3, 2, innerColour, 2);
  delay(theDelay);

  // Move 13
  cube.line(2, 0, 0, 2, 0, 3, BLACK);
  cube.line(0, 1, 0, 0, 1, 3, BLACK);
  cube.line(0, 0, 0, 1, 0, 0, BLACK);
  cube.line(0, 0, 3, 1, 0, 3, BLACK);
  cube.box(0, 0, 0, 3, 0, 3, outerColour, 2);

  cube.box(2, 3, 1, 3, 3, 2, BLACK, 2);
  cube.box(1, 3, 1, 2, 3, 2, innerColour, 2);
  delay(theDelay);

  // Move 14
  cube.box(0, 0, 0, 3, 0, 3, BLACK, 2);
  cube.box(0, 1, 0, 3, 1, 3, outerColour, 2);

  cube.box(1, 3, 1, 2, 3, 2, BLACK, 2);
  cube.box(1, 2, 1, 2, 2, 2, innerColour, 2);
  delay(theDelay);

  // Move 15
  cube.box(0, 1, 0, 3, 1, 3, BLACK, 2);
  cube.box(0, 2, 0, 3, 2, 3, outerColour, 2);

  cube.box(1, 2, 1, 2, 2, 2, BLACK, 2);
  cube.box(1, 1, 1, 2, 1, 2, innerColour, 2);
  delay(theDelay);

  // Move 16
  cube.box(0, 2, 0, 3, 2, 3, BLACK, 2);
  cube.box(0, 3, 0, 3, 3, 3, outerColour, 2);

  cube.box(1, 1, 1, 2, 1, 2, BLACK, 2);
  cube.box(1, 0, 1, 2, 0, 2, innerColour, 2);
  delay(theDelay);

  // Move 17
  cube.box(0, 3, 0, 3, 3, 3, BLACK, 2);
  cube.line(0, 3, 2, 3, 3, 2, outerColour);
  cube.line(0, 2, 0, 3, 2, 0, outerColour);
  cube.line(0, 3, 0, 0, 3, 1, outerColour);
  cube.line(3, 3, 0, 3, 3, 1, outerColour);

  cube.box(1, 0, 1, 2, 0, 2, BLACK, 2);
  cube.box(1, 0, 2, 2, 0, 3, innerColour, 2);
  delay(theDelay);

  // Move 18
  cube.line(0, 3, 2, 3, 3, 2, BLACK);
  cube.line(0, 2, 0, 3, 2, 0, BLACK);
  cube.line(0, 3, 0, 0, 3, 1, BLACK);
  cube.line(3, 3, 0, 3, 3, 1, BLACK);
  cube.line(0, 3, 1, 3, 3, 1, outerColour);
  cube.line(0, 1, 0, 3, 1, 0, outerColour);
  cube.line(0, 2, 0, 0, 3, 0, outerColour);
  cube.line(3, 2, 0, 3, 3, 0, outerColour);

  cube.box(1, 0, 2, 2, 0, 3, BLACK, 2);
  cube.box(1, 0, 3, 2, 1, 3, innerColour, 2);
  delay(theDelay);

  // Move 19 (clear the end of the previous move
  // as move 1 is then the start).
  cube.line(0, 3, 1, 3, 3, 1, BLACK);
  cube.line(0, 1, 0, 3, 1, 0, BLACK);
  cube.line(0, 2, 0, 0, 3, 0, BLACK);
  cube.line(3, 2, 0, 3, 3, 0, BLACK);

  cube.box(1, 0, 3, 2, 1, 3, BLACK, 2);
}

