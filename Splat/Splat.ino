/*
   File:      Splat.ino
   Purpose:   Splat pattern for the Freetronics 4x4x4 Cube
   Author:    Adam Reed (adam@secretcode.ninja)
   Licence:   BSD 3-Clause Licence
*/

// Include required libraries
#include <SPI.h>
#include "Cube.h"

/*
   User editable variables
*/
// The colour to use for the animation
rgb_t theColour = BLUE;

// The delay between each step of an animation
int theDelay = 50;

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
    serial->println("Splat v1.0");
  }
}

void loop(void) {
  // Draw each of the frames of the animation

  // 1
  cube.setplane(Z, 0, theColour);
  delay(theDelay);

  // 2
  cube.all(BLACK);
  cube.box(0, 0, 0, 1, 1, 0, theColour);
  cube.box(2, 2, 0, 3, 3, 0, theColour);
  delay(theDelay);

  // 3
  cube.all(BLACK);
  cube.set(0, 0, 0, theColour);
  cube.set(3, 3, 0, theColour);
  delay(theDelay);

  // 4
  cube.all(BLACK);
  cube.line(0, 1, 1, 1, 0, 1, theColour);
  cube.line(2, 3, 1, 3, 2, 1, theColour);
  delay(theDelay);

  // 5
  cube.all(BLACK);
  cube.line(2, 0, 2, 0, 2, 2, theColour);
  cube.line(1, 3, 2, 3, 1, 2, theColour);
  delay(theDelay);

  // 6
  cube.all(BLACK);
  cube.line(0, 3, 3, 3, 0, 3, theColour);
  delay(theDelay);

  // 7
  cube.line(0, 3, 2, 3, 0, 2, theColour);
  delay(theDelay);

  // 8
  cube.line(0, 3, 1, 3, 0, 1, theColour);
  delay(theDelay);

  // 9
  cube.line(0, 3, 0, 3, 0, 0, theColour);
  delay(theDelay);

  // 10
  cube.line(0, 3, 3, 3, 0, 3, BLACK);
  delay(theDelay);

  // 11
  cube.line(0, 3, 2, 3, 0, 2, BLACK);
  delay(theDelay);

  // 12
  cube.line(0, 3, 1, 3, 0, 1, BLACK);
  delay(theDelay);

  // 13
  cube.box(2, 0, 0, 3, 1, 0, theColour);
  cube.box(0, 2, 0, 1, 3, 0, theColour);
  delay(theDelay);
}

