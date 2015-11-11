
/*
 * File:    FlashingCubes.ino
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
    serial->println("Flashing Cubes v1.0");
  }
}

void loop(void) {
  rgb_t theColour = BLUE;
  int theDelay = 500;

  cube.box(1,1,1, 2,2,2, theColour);
  delay(theDelay);
  cube.box(0,0,0, 3,3,3, theColour);
  delay(theDelay);
  cube.box(1,1,1, 2,2,2, BLACK);
  delay(theDelay);
  cube.box(0,0,0, 3,3,3, theColour);
  delay(theDelay);
  cube.box(0,0,0, 3,3,3, BLACK);

}

