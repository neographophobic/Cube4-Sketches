/*
   File:      FaceSweep.ino
   Purpose:   FaceSweep pattern for the Freetronics 4x4x4 Cube
   Author:    Adam Reed (adam@secretcode.ninja)
   Licence:   BSD 3-Clause Licence

   Inspired by Trilobyte Projects "4x4x4 Led cube demo"
   at https://www.youtube.com/watch?v=adXXSitxPdo&t=1
*/

// Include required libraries
#include "Cube.h"

/*
   User editable variables
*/
// Define the colour to use
rgb_t theColour = BLUE;

// Define the delay between each step of an animation
int moveDelay = 75;

// Define the delay between the end of one animation, and the
// start of the next one
int sweepPause = 75;

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
    serial->println("FaceSweep v1.0");
  }
}

void loop(void) {
  // Run the Face Sweep Animation
  faceSweep(theColour);
}

void faceSweep(rgb_t theColour)
{
  // Clear the CUBE
  cube.all(BLACK);

  // Move 1: Face Y0 -> Z3 (1 -> 5)
  // Step 1
  cube.setplane(Y, 0, theColour);
  delay(moveDelay);

  // Step 2
  cube.line(0, 0, 0, 3, 0, 0, BLACK);
  cube.line(0, 1, 0, 3, 1, 0, theColour);
  delay(moveDelay);

  // Step 3
  cube.line(0, 1, 0, 3, 1, 0, BLACK);
  cube.line(0, 0, 1, 3, 0, 1, BLACK);
  cube.line(0, 2, 0, 3, 2, 0, theColour);
  cube.line(0, 1, 1, 3, 1, 1, theColour);
  delay(moveDelay);

  // Step 4
  cube.line(0, 2, 0, 3, 2, 0, BLACK);
  cube.line(0, 1, 1, 3, 1, 1, BLACK);
  cube.line(0, 0, 2, 3, 0, 2, BLACK);
  cube.line(0, 3, 0, 3, 3, 0, theColour);
  cube.line(0, 2, 1, 3, 2, 1, theColour);
  cube.line(0, 1, 2, 3, 1, 2, theColour);
  delay(moveDelay);

  // Step 5
  cube.line(0, 3, 0, 3, 3, 0, BLACK);
  cube.line(0, 2, 1, 3, 2, 1, BLACK);
  cube.line(0, 1, 2, 3, 1, 2, BLACK);
  cube.line(0, 3, 1, 3, 3, 1, theColour);
  cube.line(0, 2, 2, 3, 2, 2, theColour);
  cube.line(0, 1, 3, 3, 1, 3, theColour);
  delay(moveDelay);

  // Step 6
  cube.line(0, 3, 1, 3, 3, 1, BLACK);
  cube.line(0, 2, 2, 3, 2, 2, BLACK);
  cube.line(0, 3, 2, 3, 3, 2, theColour);
  cube.line(0, 2, 3, 3, 2, 3, theColour);
  delay(moveDelay);

  // Step 7
  cube.line(0, 3, 2, 3, 3, 2, BLACK);
  cube.line(0, 3, 3, 3, 3, 3, theColour);
  delay(moveDelay);
  delay(sweepPause);

  // Move 2: Face Z3 -> X3 (5 -> 4)
  // Step 1
  cube.line(0, 0, 3, 0, 3, 3, BLACK);
  cube.line(0, 0, 2, 0, 3, 2, theColour);
  delay(moveDelay);

  // Step 2
  cube.line(0, 0, 2, 0, 3, 2, BLACK);
  cube.line(1, 0, 3, 1, 3, 3, BLACK);
  cube.line(0, 0, 1, 0, 3, 1, theColour);
  cube.line(1, 0, 2, 1, 3, 2, theColour);
  delay(moveDelay);

  // Step 3
  cube.line(0, 0, 1, 0, 3, 1, BLACK);
  cube.line(1, 0, 2, 1, 3, 2, BLACK);
  cube.line(2, 0, 3, 2, 3, 3, BLACK);
  cube.line(0, 0, 0, 0, 3, 0, theColour);
  cube.line(1, 0, 1, 1, 3, 1, theColour);
  cube.line(2, 0, 2, 2, 3, 2, theColour);
  delay(moveDelay);

  // Step 4
  cube.line(0, 0, 0, 0, 3, 0, BLACK);
  cube.line(1, 0, 1, 1, 3, 1, BLACK);
  cube.line(2, 0, 2, 2, 3, 2, BLACK);
  cube.line(1, 0, 0, 1, 3, 0, theColour);
  cube.line(2, 0, 1, 2, 3, 1, theColour);
  cube.line(3, 0, 2, 3, 3, 2, theColour);
  delay(moveDelay);

  // Step 5
  cube.line(1, 0, 0, 1, 3, 0, BLACK);
  cube.line(2, 0, 1, 2, 3, 1, BLACK);
  cube.line(2, 0, 0, 2, 3, 0, theColour);
  cube.line(3, 0, 1, 3, 3, 1, theColour);
  delay(moveDelay);

  // Step 6
  cube.line(2, 0, 0, 2, 3, 0, BLACK);
  cube.line(3, 0, 0, 3, 3, 0, theColour);
  delay(moveDelay);
  delay(sweepPause);

  // Move 3: Face X3 -> Y3 (4 -> 3)
  // Step 1
  cube.line(3, 0, 0, 3, 0, 3, BLACK);
  cube.line(2, 0, 0, 2, 0, 3, theColour);
  delay(moveDelay);

  // Step 2
  cube.line(3, 1, 0, 3, 1, 3, BLACK);
  cube.line(2, 0, 0, 2, 0, 3, BLACK);
  cube.line(1, 0, 0, 1, 0, 3, theColour);
  cube.line(2, 1, 0, 2, 1, 3, theColour);
  delay(moveDelay);

  // Step 3
  cube.line(3, 2, 0, 3, 2, 3, BLACK);
  cube.line(1, 0, 0, 1, 0, 3, BLACK);
  cube.line(2, 1, 0, 2, 1, 3, BLACK);
  cube.line(0, 0, 0, 0, 0, 3, theColour);
  cube.line(1, 1, 0, 1, 1, 3, theColour);
  cube.line(2, 2, 0, 2, 2, 3, theColour);
  delay(moveDelay);

  // Step 4
  cube.line(0, 0, 0, 0, 0, 3, BLACK);
  cube.line(1, 1, 0, 1, 1, 3, BLACK);
  cube.line(2, 2, 0, 2, 2, 3, BLACK);
  cube.line(0, 1, 0, 0, 1, 3, theColour);
  cube.line(1, 2, 0, 1, 2, 3, theColour);
  cube.line(2, 3, 0, 2, 3, 3, theColour);
  delay(moveDelay);

  // Step 5
  cube.line(0, 1, 0, 0, 1, 3, BLACK);
  cube.line(1, 2, 0, 1, 2, 3, BLACK);
  cube.line(0, 2, 0, 0, 2, 3, theColour);
  cube.line(1, 3, 0, 1, 3, 3, theColour);
  delay(moveDelay);

  // Step 6
  cube.line(0, 2, 0, 0, 2, 3, BLACK);
  cube.line(0, 3, 0, 0, 3, 3, theColour);
  delay(moveDelay);
  delay(sweepPause);

  // Move 4: Face Y3 -> Z0 (3 -> 6)
  // Step 1
  cube.line(0, 3, 3, 3, 3, 3, BLACK);
  cube.line(0, 2, 3, 3, 2, 3, theColour);
  delay(moveDelay);

  // Step 2
  cube.line(0, 2, 3, 3, 2, 3, BLACK);
  cube.line(0, 3, 2, 3, 3, 2, BLACK);
  cube.line(0, 1, 3, 3, 1, 3, theColour);
  cube.line(0, 2, 2, 3, 2, 2, theColour);
  delay(moveDelay);

  // Step 3
  cube.line(0, 1, 3, 3, 1, 3, BLACK);
  cube.line(0, 2, 2, 3, 2, 2, BLACK);
  cube.line(0, 3, 1, 3, 3, 1, BLACK);
  cube.line(0, 0, 3, 3, 0, 3, theColour);
  cube.line(0, 1, 2, 3, 1, 2, theColour);
  cube.line(0, 2, 1, 3, 2, 1, theColour);
  delay(moveDelay);

  // Step 4
  cube.line(0, 0, 3, 3, 0, 3, BLACK);
  cube.line(0, 1, 2, 3, 1, 2, BLACK);
  cube.line(0, 2, 1, 3, 2, 1, BLACK);
  cube.line(0, 0, 2, 3, 0, 2, theColour);
  cube.line(0, 1, 1, 3, 1, 1, theColour);
  cube.line(0, 2, 0, 3, 2, 0, theColour);
  delay(moveDelay);

  // Step 5
  cube.line(0, 0, 2, 3, 0, 2, BLACK);
  cube.line(0, 1, 1, 3, 1, 1, BLACK);
  cube.line(0, 0, 1, 3, 0, 1, theColour);
  cube.line(0, 1, 0, 3, 1, 0, theColour);
  delay(moveDelay);

  // Step 6
  cube.line(0, 0, 1, 3, 0, 1, BLACK);
  cube.line(0, 0, 0, 3, 0, 0, theColour);
  delay(moveDelay);
  delay(sweepPause);

  // Move 5: Face Z0 -> X0 (6 -> 2)
  // Step 1
  cube.line(3, 0, 0, 3, 3, 0, BLACK);
  cube.line(3, 0, 1, 3, 3, 1, theColour);
  delay(moveDelay);

  // Step 2
  cube.line(3, 0, 1, 3, 3, 1, BLACK);
  cube.line(2, 0, 0, 2, 3, 0, BLACK);
  cube.line(3, 0, 2, 3, 3, 2, theColour);
  cube.line(2, 0, 1, 2, 3, 1, theColour);
  delay(moveDelay);

  // Step 3
  cube.line(3, 0, 2, 3, 3, 2, BLACK);
  cube.line(2, 0, 1, 2, 3, 1, BLACK);
  cube.line(1, 0, 0, 1, 3, 0, BLACK);
  cube.line(3, 0, 3, 3, 3, 3, theColour);
  cube.line(2, 0, 2, 2, 3, 2, theColour);
  cube.line(1, 0, 1, 1, 3, 1, theColour);
  delay(moveDelay);

  // Step 4
  cube.line(3, 0, 3, 3, 3, 3, BLACK);
  cube.line(2, 0, 2, 2, 3, 2, BLACK);
  cube.line(1, 0, 1, 1, 3, 1, BLACK);
  cube.line(2, 0, 3, 2, 3, 3, theColour);
  cube.line(1, 0, 2, 1, 3, 2, theColour);
  cube.line(0, 0, 1, 0, 3, 1, theColour);
  delay(moveDelay);

  // Step 5
  cube.line(2, 0, 3, 2, 3, 3, BLACK);
  cube.line(1, 0, 2, 1, 3, 2, BLACK);
  cube.line(1, 0, 3, 1, 3, 3, theColour);
  cube.line(0, 0, 2, 0, 3, 2, theColour);
  delay(moveDelay);

  // Step 6
  cube.line(1, 0, 3, 1, 3, 3, BLACK);
  cube.line(0, 0, 3, 0, 3, 3, theColour);
  delay(moveDelay);
  delay(sweepPause);

  // Move 6: Face X0 -> Y0 (2 -> 1)
  // Step 1
  cube.line(0, 3, 0, 0, 3, 3, BLACK);
  cube.line(1, 3, 0, 1, 3, 3, theColour);
  delay(moveDelay);

  // Step 2
  cube.line(1, 3, 0, 1, 3, 3, BLACK);
  cube.line(0, 2, 0, 0, 2, 3, BLACK);
  cube.line(2, 3, 0, 2, 3, 3, theColour);
  cube.line(1, 2, 0, 1, 2, 3, theColour);
  delay(moveDelay);

  // Step 3
  cube.line(2, 3, 0, 2, 3, 3, BLACK);
  cube.line(1, 2, 0, 1, 2, 3, BLACK);
  cube.line(0, 1, 0, 0, 1, 3, BLACK);
  cube.line(1, 1, 0, 1, 1, 3, theColour);
  cube.line(2, 2, 0, 2, 2, 3, theColour);
  cube.line(3, 3, 0, 3, 3, 3, theColour);
  delay(moveDelay);

  // Step 4
  cube.line(1, 1, 0, 1, 1, 3, BLACK);
  cube.line(2, 2, 0, 2, 2, 3, BLACK);
  cube.line(3, 3, 0, 3, 3, 3, BLACK);
  cube.line(3, 2, 0, 3, 2, 3, theColour);
  cube.line(2, 1, 0, 2, 1, 3, theColour);
  cube.line(1, 0, 0, 1, 0, 3, theColour);
  delay(moveDelay);

  // Step 5
  cube.line(3, 2, 0, 3, 2, 3, BLACK);
  cube.line(2, 1, 0, 2, 1, 3, BLACK);
  cube.line(3, 1, 0, 3, 1, 3, theColour);
  cube.line(2, 0, 0, 2, 0, 3, theColour);
  delay(moveDelay);

  // Step 6
  cube.line(3, 1, 0, 3, 1, 3, BLACK);
  cube.line(3, 0, 0, 3, 0, 3, theColour);
  delay(moveDelay);
  delay(sweepPause);
}

