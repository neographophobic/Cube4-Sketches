/*
   File:      Cubes.h
   Purpose:   Cubes pattern for the Freetronics 4x4x4 Cube (non blocking)

   Original Author:   Blake Kus (blakekus@gmail.com)
   License:           GPLv3
   Thia example is part of the Cube4 Library from Freetronics
   https://github.com/freetronics/Cube4.

   Modified by:       Adam Reed (adam@secretcode.ninja)
*/

// Ensure that this header file is only processed once, regardless of how
// many time it is included
#ifndef Cubes_h
#define Cubes_h

// Include for Arduino Library
#include <Arduino.h>

// Include for Cube Library
#include "Cube.h"

// Define the size of the cube
#define CUBE_SIZE 4

// Declare out class, with public and private variables and functions
class Cubes {
  public:
    // Constructor method, requiring the cube class, and the time in
    // milliseconds between frames
    Cubes(Cube cube, int theDelay);

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
};

#endif

