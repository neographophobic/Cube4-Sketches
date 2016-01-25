/*
    File:     ColourPulse.h
    Purpose:  ColourPulse pattern for the Freetronics 4x4x4 Cube (non blocking)
    Author:   Adam Reed (adam@secretcode.ninja)
    Licence:  BSD 3-Clause Licence
*/

// Ensure that this header file is only processed once, regardless of how
// many time it is included
#ifndef ColourPulse_h
#define ColourPulse_h

// Include for Arduino Library
#include <Arduino.h>

// Include for Cube Library
#include "Cube.h"

// Include for helper functions for the cube
#include "Cube4_ARUtils.h"

// Declare out class, with public and private variables and functions
class ColourPulse {
  public:
    // Constructor method, requiring the cube class, the frequency to
    // change the colour (smaller is more frequent), and the time in
    // milliseconds between colour changes
    ColourPulse(Cube cube, byte brightnessIncrement, int theDelay);

    // Function to determine what the current state of the annimation
    // should be, and to update the cube to that state if appropriate
    // with the provided colour
    void update(rgb_t theColour = BLUE);

  private:
    // Reference to the cube
    Cube _cube;

    // The frequency to update the cube colour
    byte _brightnessIncrement;

    // Delay between animation states in milliseconds
    int _theDelay;

    // The state the animation is in
    int _state;

    // Tracks the time the code was last run
    unsigned long _previousMillis;

    // Track the brighness
    int _brightness;

    // Taking the colour in HSV, and a new brightness value determine if
    // the cube should be updated, and if so update the cube to the new
    // colour
    void updateCubeColour(struct hsv theColourInHSV, int brightness);
};

#endif

