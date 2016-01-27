/*
    File:     LaserShow.cpp
    Purpose:  LaserShow pattern for the Freetronics 4x4x4 Cube (non blocking)

    Original Author:   Blake Kus (blakekus@gmail.com)
    License:           GPLv3
    This example is part of the Cube4 Library from Freetronics
    https://github.com/freetronics/Cube4. I've made minor modifications.

    Modified by:       Adam Reed (adam@secretcode.ninja)
*/

// Include for Arduino Library
#include <Arduino.h>

// Include for Cube Library
#include "Cube.h"

// Include for helper functions for the cube
#include "Cube4_ARUtils.h"

// Include the header file for this class
#include "LaserShow.h"

LaserShow::LaserShow(Cube cube, int theDelay)
{
  // Retain the reference to the cube
  _cube = cube;

  // Retain the delay we will use
  _theDelay = theDelay;

  // Set the initial X and Y positions
  _xPos = 0;
  _yPos = 0;

  // Set the initial change in X and Y values
  _xStep = 1;
  _yStep = 0;

  // Set the initial "Loop" counter
  _counter = 0;

  // Set the time we last ran the code to zero as it hasn't run yet
  _previousMillis = 0;
}

void LaserShow::update(rgb_t theColours[])
{
  // Handles drawing the LaserShow animation.

  /* This code is designed to be non blocking, so instead of using
     "delay()", it uses a state machine to track where it is upto in the
     animation. It then uses the time and the difference between this run
     and the last run to determine if it needs to change to a different
     state
  */

  // Get the current time
  unsigned long currentMillis = millis();

  if (currentMillis - _previousMillis >= _theDelay)
  {
    _cube.all(BLACK);
    if (_counter <= 12) {
      _cube.line(0, 3, 0, _yPos, 3 - _xPos, 3, theColours[0]);
      _cube.line(3, 3, 0, 3 - _xPos, 3 - _yPos, 3, theColours[1]);
      _cube.line(3, 0, 0, 3 - _yPos, _xPos, 3, theColours[2]);
      _cube.line(0, 0, 0, _xPos, _yPos, 3, theColours[3]);
    } else {
      _cube.line(0, 3, 3, _yPos, 3 - _xPos, 0, theColours[0]);
      _cube.line(3, 3, 3, 3 - _xPos, 3 - _yPos, 0, theColours[1]);
      _cube.line(3, 0, 3, 3 - _yPos, _xPos, 0, theColours[2]);
      _cube.line(0, 0, 3, _xPos, _yPos, 0, theColours[3]);
    }
    if (_xPos == 3 && _yPos == 0) {
      _xStep = 0;
      _yStep = 1;
    } else if (_xPos == 3 && _yPos == 3) {
      _xStep = -1;
      _yStep = 0;
    } else if (_xPos == 0 && _yPos == 3) {
      _xStep = 0;
      _yStep = -1;
    } else if (_xPos == 0 && _yPos == 0) {
      _xStep = 1;
      _yStep = 0;
    }
    _xPos += _xStep;
    _yPos += _yStep;

    _counter++;
    if (_counter == 24) {
      _counter = 0;
    }

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
}

