/*
 *  File:     Spiral.h
 *  Purpose:  Spiral pattern for the Freetronics 4x4x4 Cube (non blocking)
 *  Author:   Adam Reed (adam@secretcode.ninja)
 *  Licence:  BSD 3-Clause Licence
 */

// Ensure that this header file is only processed once, regardless of how
// many time it is included
#ifndef Spiral_h
#define Spiral_h

// Include for Arduino Library
#include <Arduino.h>

// Include for Cube Library
#include "Cube.h"

// Include for helper functions for the cube
#include "Cube4_ARUtils.h"

// Declare out class, with public and private variables and functions
class Spiral {
  public:
    // Constructor method, requiring the cube class, and the time in
    // milliseconds between frames
    Spiral(Cube cube, int theDelay);

    // Function to determine what the current state of the animation
    // should be, and to update the cube to that state if appropriate
    // with the provided colour
    void update(rgb_t theColour = BLUE);

  private:
    // Reference to the cube
    Cube _cube;

    // Delay between animation states in milliseconds
    int _theDelay;

    // The state the animation is in
    int _state;

    // Tracks the time the code was last run
    unsigned long _previousMillis;

    // leds is an array of the x,y,z coordinates of each of the
    // LEDs in our cube.
    struct coordinate _leds[65];

    // How many items there are in the array of coordinates to process
    static const int _itemsToProcess = 48;

    // Track where we are in the array of LED coordinates for the animation
    byte _counter;

    void drawAnimation(byte direction, rgb_t theColour);
};

#endif

