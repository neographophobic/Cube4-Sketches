/*
    File:     LaserShow.h
    Purpose:  LaserShow pattern for the Freetronics 4x4x4 Cube (non blocking)

    Original Author:   Blake Kus (blakekus@gmail.com)
    License:           GPLv3
    This example is part of the Cube4 Library from Freetronics
    https://github.com/freetronics/Cube4.

    Modified by:       Adam Reed (adam@secretcode.ninja)
*/

// Ensure that this header file is only processed once, regardless of how
// many time it is included
#ifndef LaserShow_h
#define LaserShow_h

// Include for Arduino Library
#include <Arduino.h>

// Include for Cube Library
#include "Cube.h"

// Declare out class, with public and private variables and functions
class LaserShow {
  public:
    // Constructor method, requiring the cube class, and the time in
    // milliseconds between frames
    LaserShow(Cube cube, int theDelay);

    // Function to determine what the current state of the animation
    // should be, and to update the cube to that state if appropriate
    // with the provided colour
    void update(rgb_t theColours[]);

  private:
    // Reference to the cube
    Cube _cube;

    // Delay between animation states in milliseconds
    int _theDelay;

    // Track the X and Y positions
    byte _xPos;
    byte _yPos;

    // Track the change in X and Y positions
    byte _xStep;
    byte _yStep;

    // "Loop" counter
    byte _counter;

    // Tracks the time the code was last run
    unsigned long _previousMillis;
};

#endif

