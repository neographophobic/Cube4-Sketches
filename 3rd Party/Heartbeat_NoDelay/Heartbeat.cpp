/*
    File:     Heartbeat.cpp
    Purpose:  Heartbeat pattern for the Freetronics 4x4x4 Cube (non blocking)

    Original Author:   Jonathan Oxer (jon@freetronics.com)
    License:           GPLv3
    The example is part of the Cube4 Library from Freetronics
    https://github.com/freetronics/Cube4. I've changed the drawing
    to use my library's buildLEDArray function which removed the need
    for the while loops.

    Modified by:       Adam Reed (adam@secretcode.ninja)
*/

// Include for Arduino Library
#include <Arduino.h>

// Include for Cube Library
#include "Cube.h"

// Include for helper functions for the cube
#include "Cube4_ARUtils.h"

// Include the header file for this class
#include "Heartbeat.h"

Heartbeat::Heartbeat(Cube cube, int riseAndFallDelay, int firstBeatDelay, int restDelay, int beatDelay)
{
  // Retain the reference to the cube
  _cube = cube;

  // Retain the delays we will use
  _riseAndFallDelay = riseAndFallDelay;
  _firstBeatDelay = firstBeatDelay;
  _restDelay = restDelay;
  _beatDelay = beatDelay;

  // Set the default initial state for the animation
  _state = 1;

  // Track where we are in the array of LED coordinates for the animation
  _xyzPos = 0;

  // Build the full array of LEDs so that we have coordinates to match the above coordinates
  buildLEDsArray(_leds);

  // Set the time we last ran the code to zero as it hasn't run yet
  _previousMillis = 0;
}

void Heartbeat::update()
{
  // Handles drawing the Heartbeat animation.

  /* This code is designed to be non blocking, so instead of using
     "delay()", it uses a state machine to track where it is upto in the
     animation. It then uses the time and the difference between this run
     and the last run to determine if it needs to change to a different
     state
  */

  // Get the current time
  unsigned long currentMillis = millis();

  if ((_state == 1) && (currentMillis - _previousMillis >= _beatDelay))
  {
    _rise();

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;

    if (_xyzPos > 64) {
      _state++;
    }
  }
  else if ((_state == 2) && (currentMillis - _previousMillis >= _riseAndFallDelay))
  {
    // Pause between rise and fall. Do nothing.

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 3) && (currentMillis - _previousMillis >= _beatDelay))
  {
    _fall();

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;

    if (_xyzPos == 0) {
      _state++;
    }
  }
  else if ((_state == 4) && (currentMillis - _previousMillis >= _firstBeatDelay))
  {
    // Pause between beat. Do nothing.

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 5) && (currentMillis - _previousMillis >= _beatDelay))
  {
    _rise();

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;

    if (_xyzPos > 64) {
      _state++;
    }
  }
  else if ((_state == 6) && (currentMillis - _previousMillis >= _firstBeatDelay))
  {
    // Pause between rise and fall. Do nothing.

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 7) && (currentMillis - _previousMillis >= _beatDelay))
  {
    _fall();

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;

    if (_xyzPos == 0) {
      _state++;
    }
  }
  else if ((_state == 8) && (currentMillis - _previousMillis >= _restDelay))
  {
    // Long pause between beat. Do nothing.

    // Remember the time for future reference, and move to the
    // first state
    _previousMillis = currentMillis;
    _state = 1;
  }
}

/**
   Illuminate one LED at a time, starting from the bottom
*/
void Heartbeat::_rise()
{
  _cube.set(_leds[_xyzPos].x, _leds[_xyzPos].y, _leds[_xyzPos].z, RED);
  _xyzPos++;
}

/**
   Extinguish one LED at a time, starting from the top
*/
void Heartbeat::_fall()
{
  _cube.set(_leds[_xyzPos].x, _leds[_xyzPos].y, _leds[_xyzPos].z, BLACK);
  _xyzPos--;
}

