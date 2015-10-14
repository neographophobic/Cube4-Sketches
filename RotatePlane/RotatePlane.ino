
/*
 * File:    RotatePlane.ino
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

// Define the colour to use
rgb_t theColour = BLUE;

// Define the delay between each step of an animation
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
    serial->println("RotatePlane v1.0");
  }
}

void loop(void) {

  sweep(0, 0, 1, 1, 2, 2, 3, 3, theColour, theDelay);
  sweep(0, 1, 1, 1, 2, 2, 3, 2, theColour, theDelay);
  sweep(0, 2, 1, 2, 2, 1, 3, 1, theColour, theDelay);
  sweep(0, 3, 1, 2, 2, 1, 3, 0, theColour, theDelay);
  sweep(1, 2, 1, 3, 2, 0, 2, 1, theColour, theDelay);
  sweep(1, 0, 1, 1, 2, 2, 2, 3, theColour, theDelay);

}

/*
 * Create a line from top to bottom of the cube at the given
 * x and y coordinates, and then repeat this for the 3 other
 * provided xy coordinates.
 */
void sweep(byte x1, byte y1,
           byte x2, byte y2,
           byte x3, byte y3,
           byte x4, byte y4,
           rgb_t theColour, int theDelay)
{

  // Clear the Cube
  cube.all(BLACK);

  // Create the first line from x1 and y1 coordinates
  cube.line(x1, y1, 0, x1, y1, 3, theColour);

  // Create the second line from x2 and y2 coordinates
  cube.line(x2, y2, 0, x2, y2, 3, theColour);

  // Create the third line from x3 and y3 coordinates
  cube.line(x3, y3, 0, x3, y3, 3, theColour);

  // Create the fourth line from x4 and y4 coordinates
  cube.line(x4, y4, 0, x4, y4, 3, theColour);

  // Display the lines for the provided delay period.
  delay(theDelay);
}

