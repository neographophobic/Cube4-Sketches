
/*
 * File:    RotatePlane.ino
 * Version: 1.0
 * Author:  Adam Reed (adam@secretcode.ninja)
 * License: BSD 3-Clause Licence
 *
 * TODO: Consider adding an up and down version
 */

#include "SPI.h"
#include "Cube.h"

Cube cube;

/*
 * User editable variables
 */

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
  // Sweep from Left to Right, in a clockwise motion 7 times
  for (byte i = 0; i < 7; i++)
  {
    sweep(true, true, BLUE, theDelay);
  }

  // Clear the cube
  cube.all(BLACK);
  
  // Sweep from Left to Right, in a anticlockwise motion 7 times
  for (byte i = 0; i < 7; i++)
  {
    sweep(true, false, GREEN, theDelay);
  }

  // Clear the cube
  cube.all(BLACK);
}

/*
 * Run a sweeping animation, starting on either the left or right hand side, and running
 * in a clockwise or anticlockwise motion, using the provided colour, and pausing for
 * the period specified in theDelay
 */
void sweep(bool startFromLeftHandSide, bool clockwise, rgb_t theColour, int theDelay)
{
  // Sequence of frames to display for clockwise motion
  byte clockwiseSequence[] = {1, 2, 3, 4, 5, 6};

  // Sequence of frames to display for anticlockwise motion
  byte antiClockwiseSequence[] = {1, 6, 5, 4, 3, 2};

  // The position to start from within the sequence arrays
  byte arrayPosition = 0;

  // If not starting on the left hand side of the cube, start from position 3 in the
  // array, not position 0.
  if (!startFromLeftHandSide)
  {
    arrayPosition = 3;
  }

  // Loop through the six frames that make up the animation
  for (byte i = 1; i <= 6; i++)
  {

    if (clockwise) {
      // Show the appropriate from from the clockwise array
      animationFrame(clockwiseSequence[arrayPosition], theColour, theDelay);
    } else {
      // Show the appropriate from from the anticlockwise array
      animationFrame(antiClockwiseSequence[arrayPosition], theColour, theDelay);
    }

    // Move to the next frame within the sequence array
    arrayPosition++;

    if (arrayPosition == 6)
    {
      // If we get to an array position > 5 we run out of frames, so reset it back to
      // zero. This is useful when starting from the right hand side of the cube
      arrayPosition = 0;
    }
  }
}

/*
 * Show the specified frame of the animation, using the provided
 * colour, pausing for the set delay time.
 */
void animationFrame(byte theFrame, rgb_t theColour, int theDelay)
{
  // Clear the Cube
  cube.all(BLACK);

  // There are 6 possible animation frames. This switch will show
  // the requested frame by drawing the appropriate lines.
  switch (theFrame)
  {
    case 1:
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(1, 1, 0, 1, 1, 3, theColour);
      cube.line(2, 2, 0, 2, 2, 3, theColour);
      cube.line(3, 3, 0, 3, 3, 3, theColour);
      break;
    case 2:
      cube.line(0, 1, 0, 0, 1, 3, theColour);
      cube.line(1, 1, 0, 1, 1, 3, theColour);
      cube.line(2, 2, 0, 2, 2, 3, theColour);
      cube.line(3, 2, 0, 3, 2, 3, theColour);
      break;
    case 3:
      cube.line(0, 2, 0, 0, 2, 3, theColour);
      cube.line(1, 2, 0, 1, 2, 3, theColour);
      cube.line(2, 1, 0, 2, 1, 3, theColour);
      cube.line(3, 1, 0, 3, 1, 3, theColour);
      break;
    case 4:
      cube.line(0, 3, 0, 0, 3, 3, theColour);
      cube.line(1, 2, 0, 1, 2, 3, theColour);
      cube.line(2, 1, 0, 2, 1, 3, theColour);
      cube.line(3, 0, 0, 3, 0, 3, theColour);
      break;
    case 5:
      cube.line(1, 2, 0, 1, 2, 3, theColour);
      cube.line(1, 3, 0, 1, 3, 3, theColour);
      cube.line(2, 0, 0, 2, 0, 3, theColour);
      cube.line(2, 1, 0, 2, 1, 3, theColour);
      break;
    case 6:
      cube.line(1, 0, 0, 1, 0, 3, theColour);
      cube.line(1, 1, 0, 1, 1, 3, theColour);
      cube.line(2, 2, 0, 2, 2, 3, theColour);
      cube.line(2, 3, 0, 2, 3, 3, theColour);
      break;
  }

  // Display the lines for the provided delay period.
  delay(theDelay);
}

