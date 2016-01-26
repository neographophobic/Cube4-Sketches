/*
    File:     FaceSweep.h
    Purpose:  FaceSweep pattern for the Freetronics 4x4x4 Cube (non blocking)
    Author:   Adam Reed (adam@secretcode.ninja)
    Licence:  BSD 3-Clause Licence
*/

// Ensure that this header file is only processed once, regardless of how
// many time it is included
#ifndef FaceSweep_h
#define FaceSweep_h

// Include for Arduino Library
#include <Arduino.h>

// Include for Cube Library
#include "Cube.h"

// Include for helper functions for the cube
#include "Cube4_ARUtils.h"

// Declare out class, with public and private variables and functions
class FaceSweep {
  public:
    // Constructor method, requiring the cube class, and the time in
    // milliseconds between frames, and sweeps
    FaceSweep(Cube cube, int moveDelay, int sweepPause);

    // Function to determine what the current state of the animation
    // should be, and to update the cube to that state if appropriate
    // with the provided colour
    void update(rgb_t theColour = BLUE);

  private:
    // Reference to the cube
    Cube _cube;

    // Delay between animation states in milliseconds
    int _moveDelay;

    // Delay between animation states in milliseconds
    int _sweepPause;

    // The state the animation is in
    int _state;

    // Tracks the time the code was last run
    unsigned long _previousMillis;
};

#endif

