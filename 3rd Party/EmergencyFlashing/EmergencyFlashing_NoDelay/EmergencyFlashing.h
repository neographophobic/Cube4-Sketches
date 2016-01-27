/*
   File:      EmergencyFlashing.h
   Purpose:   EmergencyFlashing pattern for the Freetronics 4x4x4 Cube (non blocking)

   Original Author:   yatto
   This sketch was contributed by yatto on the Freetronics forums:
   http://forum.freetronics.com/viewtopic.php?f=32&t=6507.

   Modified by:       Adam Reed (adam@secretcode.ninja)
*/

// Ensure that this header file is only processed once, regardless of how
// many time it is included
#ifndef EmergencyFlashing_h
#define EmergencyFlashing_h

// Include for Arduino Library
#include <Arduino.h>

// Include for Cube Library
#include "Cube.h"

// Declare out class, with public and private variables and functions
class EmergencyFlashing {
  public:
    // Constructor method, requiring the cube class, and the time in
    // milliseconds between both the fast and slow flashes
    EmergencyFlashing(Cube cube, int fastDelay, int slowDelay);

    // Function to determine what the current state of the animation
    // should be, and to update the cube to that state if appropriate
    void update();

  private:
    // Reference to the cube
    Cube _cube;

    // fastDelay tracks the delay between the fast flashes
    int _fastDelay;

    // slowDelay tracks the delay between the slow flashes
    int _slowDelay;

    // Counters for the number of flashes we have
    byte _flash;
    byte _fastFlashes;

    // The state the animation is in
    int _state;

    // Tracks the time the code was last run
    unsigned long _previousMillis;
};

#endif

