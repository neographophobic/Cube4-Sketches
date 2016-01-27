/*
    File:     RainStorm.h
    Purpose:  RainStorm pattern for the Freetronics 4x4x4 Cube (non blocking)

    Original Author:   Jonathan Oxer (jon@freetronics.com)
    License:           GPLv3
    The example is part of the Cube4 Library from Freetronics
    https://github.com/freetronics/Cube4.

    Modified by:       Adam Reed (adam@secretcode.ninja)
*/

// Ensure that this header file is only processed once, regardless of how
// many time it is included
#ifndef RainStorm_h
#define RainStorm_h

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
class RainStorm {
  public:
    // Constructor method, requiring the cube class, the time in
    // milliseconds between raindrops, whether to show the cloud
    // layer, and the frequency and number of lightning strikes
    RainStorm(Cube cube, int rainDropDelay, bool showClouds, int lightingInterval, int maxLightningBolts);

    // Function to determine what the current state of the animation
    // should be, and to update the cube to that state if appropriate
    void update();

  private:
    // Reference to the cube
    Cube _cube;

    // Delay between raindrops
    int _rainDropDelay;

    // Whether to show cloud layer
    bool _showClouds;

    // How frequently lightning should occur, on average
    int _lightingInterval;

    // Maximum number of lightning flashes
    int _maxLightningBolts;

    // How many lightning flashes this time, and how
    // many have been shown
    int _lightningFlashes;
    int _lightningFlashesShown;

    // Rain drop locations
    byte _drop1XPos;
    byte _drop1YPos;
    byte _drop1ZPos;

    byte _drop2XPos;
    byte _drop2YPos;
    byte _drop2ZPos;

    // The state the animation is in
    int _state;

    // Tracks the time the code was last run
    unsigned long _previousMillis;

    // Function to draw the clouds
    void clouds();

    // Function to determine if we should be showing
    // lightning
    void lightning();
};

#endif

