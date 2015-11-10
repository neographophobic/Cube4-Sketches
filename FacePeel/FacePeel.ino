
/*
 * File:    FacePeel.ino
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
    serial->println("FacePeel v1.0");
  }
}

void loop(void) {
  rgb_t theColour = BLUE;
  int theDelay = 100;

  cube.all(BLACK);
  delay(theDelay);

  // Complete Top Face
  cube.set(0, 0, 3, theColour);
  delay(theDelay);

  cube.line(1, 0, 3, 0, 1, 3, theColour);
  delay(theDelay);

  cube.line(2, 0, 3, 0, 2, 3, theColour);
  delay(theDelay);

  cube.line(0, 3, 3, 3, 0, 3, theColour);
  delay(theDelay);

  cube.line(1, 3, 3, 3, 1, 3,  theColour);
  delay(theDelay);

  cube.line(2, 3, 3, 3, 2, 3, theColour);
  delay(theDelay);

  cube.set(3, 3, 3, theColour);
  delay(theDelay);

  // Start Peel
  cube.set(3, 0, 3, BLACK);
  cube.set(3, 0, 2, theColour);
  delay(theDelay);

  cube.set(3, 0, 2, BLACK);
  cube.set(3, 0, 1, theColour);
  cube.line(2, 0, 3, 3, 1, 3, BLACK);
  cube.line(2, 0, 2, 3, 1, 2, theColour);
  delay(theDelay);

  cube.set(3, 0, 1, BLACK);
  cube.set(3, 0, 0, theColour);
  cube.line(2, 0, 2, 3, 1, 2, BLACK);
  cube.line(2, 0, 1, 3, 1, 1, theColour);
  cube.line(1, 0, 3, 3, 2, 3, BLACK);
  cube.line(1, 0, 2, 3, 2, 2, theColour);
  delay(theDelay);

  cube.line(2, 0, 1, 3, 1, 1, BLACK);
  cube.line(2, 0, 0, 3, 1, 0, theColour);
  cube.line(1, 0, 2, 3, 2, 2, BLACK);
  cube.line(1, 0, 1, 3, 2, 1, theColour);
  cube.line(0, 0, 3, 3, 3, 3, BLACK);
  cube.line(0, 0, 2, 3, 3, 2, theColour);
  delay(theDelay);

  cube.line(1, 0, 1, 3, 2, 1, BLACK);
  cube.line(1, 0, 0, 3, 2, 0, theColour);
  cube.line(0, 0, 2, 3, 3, 2, BLACK);
  cube.line(0, 0, 1, 3, 3, 1, theColour);
  cube.line(0, 1, 3, 2, 3, 3, BLACK);
  cube.line(0, 1, 2, 2, 3, 2, theColour);
  delay(theDelay);

  cube.line(0, 0, 1, 3, 3, 1, BLACK);
  cube.line(0, 0, 0, 3, 3, 0, theColour);
  cube.line(0, 1, 2, 2, 3, 2, BLACK);
  cube.line(0, 1, 1, 2, 3, 1, theColour);
  cube.line(0, 2, 3, 1, 3, 3, BLACK);
  cube.line(0, 2, 2, 1, 3, 2, theColour);
  delay(theDelay);

  cube.line(0, 1, 1, 2, 3, 1, BLACK);
  cube.line(0, 1, 0, 2, 3, 0, theColour);
  cube.line(0, 2, 2, 1, 3, 2, BLACK);
  cube.line(0, 2, 1, 1, 3, 1, theColour);
  cube.set(0, 3, 3, BLACK);
  cube.set(0, 3, 2, theColour);
  delay(theDelay);

  cube.line(0, 2, 1, 1, 3, 1, BLACK);
  cube.line(0, 2, 0, 1, 3, 0, theColour);
  cube.set(0, 3, 2, BLACK);
  cube.set(0, 3, 1, theColour);
  delay(theDelay);

  cube.set(0, 3, 1, BLACK);
  cube.set(0, 3, 0, theColour);
  delay(theDelay);

  // Wipe the bottom
  cube.set(0, 0, 0, BLACK);
  delay(theDelay);

  cube.line(0, 1, 0, 1, 0, 0, BLACK);
  delay(theDelay);

  cube.line(0, 2, 0, 2, 0, 0, BLACK);
  delay(theDelay);

  cube.line(0, 3, 0, 3, 0, 0, BLACK);
  delay(theDelay);

  cube.line(1, 3, 0, 3, 1, 0, BLACK);
  delay(theDelay);

  cube.line(2, 3, 0, 3, 2, 0, BLACK);
  delay(theDelay);

  cube.set(3, 3, 0, BLACK);
  delay(theDelay);

  delay(1000);
}

