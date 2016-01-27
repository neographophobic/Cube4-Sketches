/*
    File:     TestPattern.h
    Purpose:  TestPattern pattern for the Freetronics 4x4x4 Cube (non blocking)

    Original Author:   Jonathan Oxer (jon@freetronics.com)
    License:           GPLv3
    The example is part of the Cube4 Library from Freetronics
    https://github.com/freetronics/Cube4.

    Modified by:       Adam Reed (adam@secretcode.ninja)
*/

// Ensure that this header file is only processed once, regardless of how
// many time it is included
#ifndef TestPattern_h
#define TestPattern_h

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

// Include for helper functions for the cube
#include "Cube4_ARUtils.h"

// Declare out class, with public and private variables and functions
class TestPattern {
  public:
    // Constructor method, requiring the cube class
    TestPattern(Cube cube);

    // Function to determine what the current state of the animation
    // should be, and to update the cube to that state if appropriate
    // with the provided colour
    void stepThroughLEDs(rgb_t theColour = WHITE);

    void cycleCubeColours();

    void fadeWhite();

    void randomPastel();

  private:
    // Reference to the cube
    Cube _cube;

    // The state the animation is in
    int _state;

    // leds is an array of the x,y,z coordinates of each of the
    // LEDs in our cube.
    struct coordinate _leds[TOTAL_LEDS];

    // xyzPos tracks were we are in the leds array
    byte _xyzPos;

    // The brightness for the fadeWhite current state,
    // and whether to increase or decrease it
    int _brightness;
    bool _brightnessIncrease;

    // Tracks the time the code was last run
    unsigned long _previousMillis;
};

#endif

