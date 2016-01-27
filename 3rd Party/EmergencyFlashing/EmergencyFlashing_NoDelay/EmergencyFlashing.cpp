/*
   File:      EmergencyFlashing.cpp
   Purpose:   EmergencyFlashing pattern for the Freetronics 4x4x4 Cube (non blocking)

   Original Author:   yatto
   This sketch was contributed by yatto on the Freetronics forums:
   http://forum.freetronics.com/viewtopic.php?f=32&t=6507.

   Modified by:       Adam Reed (adam@secretcode.ninja)
*/

// Include for Arduino Library
#include <Arduino.h>

// Include for Cube Library
#include "Cube.h"

// Include the header file for this class
#include "EmergencyFlashing.h"

EmergencyFlashing::EmergencyFlashing(Cube cube, int fastDelay, int slowDelay)
{
  // Retain the reference to the cube
  _cube = cube;

  // Retain the fastDelay value
  _fastDelay = fastDelay;

  // Retain the slowDelay value
  _slowDelay = slowDelay;

  // Set the number of flashes to 1
  _flash = 0;
  _fastFlashes = 0;

  // Set the default initial state for the animation
  _state = 1;

  // Set the time we last ran the code to zero as it hasn't run yet
  _previousMillis = 0;
}

void EmergencyFlashing::update()
{
  // Handles drawing the EmergencyFlashing animation.

  /* This code is designed to be non blocking, so instead of using
     "delay()", it uses a state machine to track where it is upto in the
     animation. It then uses the time and the difference between this run
     and the last run to determine if it needs to change to a different
     state
  */

  // Get the current time
  unsigned long currentMillis = millis();

  if ((_state == 1) && (currentMillis - _previousMillis >= _fastDelay))
  {
    // Red Fast Flash
    _cube.box(0, 0, 0, 1, 3, 3, RED);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 2) && (currentMillis - _previousMillis >= _fastDelay))
  {
    // Red Fast Flash - Off
    _cube.all(BLACK);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 3) && (currentMillis - _previousMillis >= _fastDelay))
  {
    // Determine where to go

    // We have fast flashed once more
    _fastFlashes++;

    if (_fastFlashes == 3) {
      // Fast flashed this colour enough times, move to the next state
      // and reset the counter
      _state = 4;
      _fastFlashes = 0;
    }
    else
    {
      // We haven't fast flashed enough, but to the start of the cycle
      _state = 1;
    }

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
  else if ((_state == 4) && (currentMillis - _previousMillis >= _fastDelay))
  {
    // Blue Fast Flash
    _cube.box(2, 0, 0, 3, 3, 3, BLUE);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 5) && (currentMillis - _previousMillis >= _fastDelay))
  {
    // Blue Fast Flash - Off
    _cube.all(BLACK);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 6) && (currentMillis - _previousMillis >= _fastDelay))
  {
    // Determine where to go

    // Remember the time for future reference
    _previousMillis = currentMillis;

    // We have fast flashed once more
    _fastFlashes++;

    if (_fastFlashes == 3) {
      // Fast flashed this colour enough times, so reset counter
      _fastFlashes = 0;

      // We have completed a cycle of fast flashes
      _flash++;

      if (_flash == 4) {
        // Completed the fast flash cycle enough times, so reset counter
        // and move to slow flash
        _flash = 0;
        _state = 7;

        // Trick the state machine into believing that when we try
        // state 7 it's delay has already occured.
        _previousMillis = _previousMillis + _slowDelay;
      }
      else
      {
        // Still need to do another fast flash cycle
        _state = 1;
      }
    }
    else
    {
      // We haven't fast flashed enough, but to the start of the cycle
      _state = 4;
    }

  }
  else if ((_state == 7) && (currentMillis - _previousMillis >= _slowDelay))
  {
    // Slow Red Flash
    _cube.all(BLACK);
    _cube.box(0, 0, 0, 1, 3, 3, RED);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 8) && (currentMillis - _previousMillis >= _slowDelay))
  {
    // Slow Blue Flash
    _cube.all(BLACK);
    _cube.box(2, 0, 0, 3, 3, 3, BLUE);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 9) && (currentMillis - _previousMillis >= _slowDelay))
  {
    // Determine where to go

    // We have slow flashed once more
    _flash++;

    if (_flash == 4) {
      // We have done 4 slow flash cycles, so return to fast flashes
      _state = 1;
      _flash = 0;
      _cube.all(BLACK);
    } else {
      // We need to slow flash again
      _state = 7;
    }
  }
}

