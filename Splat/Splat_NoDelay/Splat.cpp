/*
    File:     Splat.cpp
    Purpose:  Splat pattern for the Freetronics 4x4x4 Cube (non blocking)
    Author:   Adam Reed (adam@secretcode.ninja)
    Licence:  BSD 3-Clause Licence
*/

// Include for Arduino Library
#include <Arduino.h>

// Include for Cube Library
#include "Cube.h"

// Include the header file for this class
#include "Splat.h"

Splat::Splat(Cube cube, int theDelay)
{
  // Retain the reference to the cube
  _cube = cube;

  // Retain the delay we will use
  _theDelay = theDelay;

  // Set the default initial state for the animation
  _state = 1;

  // Set the time we last ran the code to zero as it hasn't run yet
  _previousMillis = 0;
}

void Splat::update(rgb_t theColour)
{
  // Handles drawing the Splat animation.

  /* This code is designed to be non blocking, so instead of using
     "delay()", it uses a state machine to track where it is upto in the
     animation. It then uses the time and the difference between this run
     and the last run to determine if it needs to change to a different
     state
  */

  // Get the current time
  unsigned long currentMillis = millis();

  if ((_state == 1) && (currentMillis - _previousMillis >= _theDelay))
  {
    _cube.setplane(Z, 0, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 2) && (currentMillis - _previousMillis >= _theDelay))
  {
    _cube.all(BLACK);
    _cube.box(0, 0, 0, 1, 1, 0, theColour);
    _cube.box(2, 2, 0, 3, 3, 0, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 3) && (currentMillis - _previousMillis >= _theDelay))
  {
    _cube.all(BLACK);
    _cube.set(0, 0, 0, theColour);
    _cube.set(3, 3, 0, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 4) && (currentMillis - _previousMillis >= _theDelay))
  {
    _cube.all(BLACK);
    _cube.line(0, 1, 1, 1, 0, 1, theColour);
    _cube.line(2, 3, 1, 3, 2, 1, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 5) && (currentMillis - _previousMillis >= _theDelay))
  {
    _cube.all(BLACK);
    _cube.line(2, 0, 2, 0, 2, 2, theColour);
    _cube.line(1, 3, 2, 3, 1, 2, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 6) && (currentMillis - _previousMillis >= _theDelay))
  {
    _cube.all(BLACK);
    _cube.line(0, 3, 3, 3, 0, 3, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 7) && (currentMillis - _previousMillis >= _theDelay))
  {
    _cube.line(0, 3, 2, 3, 0, 2, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 8) && (currentMillis - _previousMillis >= _theDelay))
  {
    _cube.line(0, 3, 1, 3, 0, 1, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 9) && (currentMillis - _previousMillis >= _theDelay))
  {
    _cube.line(0, 3, 0, 3, 0, 0, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 10) && (currentMillis - _previousMillis >= _theDelay))
  {
    _cube.line(0, 3, 3, 3, 0, 3, BLACK);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 11) && (currentMillis - _previousMillis >= _theDelay))
  {
    _cube.line(0, 3, 2, 3, 0, 2, BLACK);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 12) && (currentMillis - _previousMillis >= _theDelay))
  {
    _cube.line(0, 3, 1, 3, 0, 1, BLACK);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 13) && (currentMillis - _previousMillis >= _theDelay))
  {
    _cube.box(2, 0, 0, 3, 1, 0, theColour);
    _cube.box(0, 2, 0, 1, 3, 0, theColour);

    // Remember the time for future reference, and move to the
    // first state
    _previousMillis = currentMillis;
    _state = 1;
  }
}

