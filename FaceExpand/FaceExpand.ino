
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
  rgb_t theColour = ORANGE;
  
  faceExpand(theColour, theDelay);
}

void faceExpand(rgb_t theColour, int theDelay)
{
  // Expand out on first face
  cube.box(3,0,0, 3,0,0, theColour);
  delay(theDelay);
  cube.box(2,0,0, 3,0,1, theColour);
  delay(theDelay);
  cube.box(1,0,0, 3,0,2, theColour);
  delay(theDelay);
  cube.box(0,0,0, 3,0,3, theColour);
  delay(theDelay);

  // Contract on first face
  cube.all(BLACK);
  cube.box(0,0,1, 2,0,3, theColour);
  delay(theDelay);
  cube.all(BLACK);
  cube.box(0,0,2, 1,0,3, theColour);
  delay(theDelay);
  cube.all(BLACK);
  cube.box(0,0,3, 0,0,3, theColour);
  delay(theDelay);

  // Expand out on second face
  cube.box(0,0,2, 0,1,3, theColour);
  delay(theDelay);
  cube.box(0,0,1, 0,2,3, theColour);
  delay(theDelay);
  cube.box(0,0,0, 0,3,3, theColour);
  delay(theDelay);

  // Contract on second face
  cube.all(BLACK);
  cube.box(0,1,0, 0,3,2, theColour);
  delay(theDelay);
  cube.all(BLACK);
  cube.box(0,2,0, 0,3,1, theColour);
  delay(theDelay);
  cube.all(BLACK);
  cube.box(0,3,0, 0,3,0, theColour);
  delay(theDelay);

  // Expand out on third face
  cube.box(0,3,0, 1,3,1, theColour);
  delay(theDelay);
  cube.box(0,3,0, 2,3,2, theColour);
  delay(theDelay);
  cube.box(0,3,0, 3,3,3, theColour);
  delay(theDelay);

  // Contract on second face
  cube.all(BLACK);
  cube.box(1,3,1, 3,3,3, theColour);
  delay(theDelay);
  cube.all(BLACK);
  cube.box(2,3,2, 3,3,3, theColour);
  delay(theDelay);
  cube.all(BLACK);
  cube.box(3,3,3, 3,3,3, theColour);
  delay(theDelay);

  // Expand out on fourth face
  cube.box(3,2,2, 3,3,3, theColour);
  delay(theDelay);
  cube.box(3,1,1, 3,3,3, theColour);
  delay(theDelay);
  cube.box(3,0,0, 3,3,3, theColour);
  delay(theDelay);

  // Contract on fourth face
  cube.all(BLACK);
  cube.box(3,0,0, 3,2,2, theColour);
  delay(theDelay);
  cube.all(BLACK);
  cube.box(3,0,0, 3,1,1, theColour);
  delay(theDelay);
  cube.all(BLACK);
  cube.box(3,0,0, 3,0,0, theColour);
  delay(theDelay);  
}

