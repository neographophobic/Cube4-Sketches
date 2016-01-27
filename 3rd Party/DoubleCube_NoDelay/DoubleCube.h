/*
    File:     DoubleCube.h
    Purpose:  Double Cube pattern for the Freetronics 4x4x4 Cube (non blocking)

    Original Author:   ADA
    This example was contributed by sparky-nz on the Freetronics forums:
    http://forum.freetronics.com/viewtopic.php?f=32&t=5579.

    Modified by:       Adam Reed (adam@secretcode.ninja)
*/

// Ensure that this header file is only processed once, regardless of how
// many time it is included
#ifndef DoubleCube_h
#define DoubleCube_h

/*==========================================================================
    APPLICATION SETTINGS (USER EDITABLE)

    UNUSED_ANALOG_PIN   An unused analog pin that is used as a seed for the
                        random number generator to ensure that the random
                        pattern is different each time the cube is started
  ============================================================================ */
#define UNUSED_ANALOG_PIN      0
/*========================================================================== */

// Include for Arduino Library
#include <Arduino.h>

// Include for Cube Library
#include "Cube.h"

// Declare out class, with public and private variables and functions
class DoubleCube {
  public:
    // Constructor method, requiring the cube class, and the time in
    // milliseconds between frames
    DoubleCube(Cube cube, int theDelay);

    // Function to determine what the current state of the animation
    // should be, and to update the cube to that state if appropriate
    void update();

  private:
    // Reference to the cube
    Cube _cube;

    // Delay between animation states in milliseconds
    int _theDelay;

    // Tracks the time the code was last run
    unsigned long _previousMillis;
};

#endif

