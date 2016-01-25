/*
    File:     Sweep.cpp
    Purpose:  Sweep pattern for the Freetronics 4x4x4 Cube (non blocking)
    Author:   Adam Reed (adam@secretcode.ninja)
    Licence:  BSD 3-Clause Licence
*/

// Include for Arduino Library
#include "Arduino.h"

// Include for Cube Library
#include "Cube.h"

// Include the header file for this class
#include "Sweep.h"

Sweep::Sweep(Cube cube, int theDelay)
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

void Sweep::update(rgb_t theColour)
{
  // Handles drawing the Sweep animation.

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
    drawSweepAnimationFrame(0, 0, 1, 1, 2, 2, 3, 3, theColour);

    // Move to the next frame
    _state = 2;

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
  else if ((_state == 2) && (currentMillis - _previousMillis >= _theDelay))
  {
    drawSweepAnimationFrame(0, 1, 1, 1, 2, 2, 3, 2, theColour);

    // Move to the next state
    _state = 3;

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
  else if ((_state == 3) && (currentMillis - _previousMillis >= _theDelay))
  {
    drawSweepAnimationFrame(0, 2, 1, 2, 2, 1, 3, 1, theColour);

    // Move to the next state
    _state = 4;

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
  else if ((_state == 4) && (currentMillis - _previousMillis >= _theDelay))
  {
    drawSweepAnimationFrame(0, 3, 1, 2, 2, 1, 3, 0, theColour);

    // Move to the next state
    _state = 5;

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
  else if ((_state == 5) && (currentMillis - _previousMillis >= _theDelay))
  {
    drawSweepAnimationFrame(1, 2, 1, 3, 2, 0, 2, 1, theColour);

    // Move to the next state
    _state = 6;

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
  else if ((_state == 6) && (currentMillis - _previousMillis >= _theDelay))
  {
    drawSweepAnimationFrame(1, 0, 1, 1, 2, 2, 2, 3, theColour);

    // Move back to the next state
    _state = 1;

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
}

void Sweep::drawSweepAnimationFrame(byte x1, byte y1, byte x2, byte y2, byte x3, byte y3, byte x4, byte y4, rgb_t theColour)
{
  _cube.all(BLACK);
  _cube.line(x1, y1, 0, x1, y1, 3, theColour);
  _cube.line(x2, y2, 0, x2, y2, 3, theColour);
  _cube.line(x3, y3, 0, x3, y3, 3, theColour);
  _cube.line(x4, y4, 0, x4, y4, 3, theColour);
}

