/*
    File:     RainStorm.cpp
    Purpose:  RainStorm pattern for the Freetronics 4x4x4 Cube (non blocking)

    Original Author:   Jonathan Oxer (jon@freetronics.com)
    License:           GPLv3
    The example is part of the Cube4 Library from Freetronics
    https://github.com/freetronics/Cube4.

    Modified by:       Adam Reed (adam@secretcode.ninja)
*/

// Include for Arduino Library
#include <Arduino.h>

// Include for Cube Library
#include "Cube.h"

// Include the header file for this class
#include "RainStorm.h"

RainStorm::RainStorm(Cube cube, int rainDropDelay, bool showClouds, int lightingInterval, int maxLightningBolts)
{
  // Retain the reference to the cube
  _cube = cube;

  // Retain the rain drop delay we will use
  _rainDropDelay = rainDropDelay;

  // Retain whether to show the clouds or not
  _showClouds = showClouds;

  // Retain frequently lightning should occur, on average
  _lightingInterval = lightingInterval;

  // Retain maximum number of lightning flashes
  _maxLightningBolts = maxLightningBolts;

  // How many lightning flashes this time, and
  // how many have been shown
  _lightningFlashes = 0;
  _lightningFlashesShown = 0;

  // Set initial rain drop z values
  _drop1ZPos = 2;
  _drop2ZPos = 0;

  // Set the default initial state for the animation
  _state = 1;

  // Set the time we last ran the code to zero as it hasn't run yet
  _previousMillis = 0;
}

void RainStorm::update()
{
  // Handles drawing the RainStorm animation.

  /* This code is designed to be non blocking, so instead of using
     "delay()", it uses a state machine to track where it is upto in the
     animation. It then uses the time and the difference between this run
     and the last run to determine if it needs to change to a different
     state
  */

  // Get the current time
  unsigned long currentMillis = millis();

  // Seed the random number generator
  randomSeed(analogRead(UNUSED_ANALOG_PIN));

  if ((_state == 1) && (currentMillis - _previousMillis >= _rainDropDelay))
  {
    if (_drop1ZPos == 4)
    {
      _drop1XPos = random(4);
      _drop1YPos = random(4);
    }

    if (_drop2ZPos == 4)
    {
      _drop2XPos = random(4);
      _drop2YPos = random(4);
    }

    _cube.all(BLACK);
    clouds();

    if (_drop1ZPos > 0)
    {
      _drop1ZPos--;
      _cube.set(_drop1XPos, _drop1YPos, _drop1ZPos, BLUE);
    } else {
      _drop1ZPos = 4;
    }

    if (_drop2ZPos > 0)
    {
      _drop2ZPos--;
      _cube.set(_drop2XPos, _drop2YPos, _drop2ZPos, BLUE);
    } else {
      _drop2ZPos = 4;
    }

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;

    // Determine whether to show lightning (which will change
    // the state if required)
    lightning();
  }
  else if ((_state == 2) && (currentMillis - _previousMillis >= _rainDropDelay))
  {
    _cube.all(WHITE);
    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 3) && (currentMillis - _previousMillis >= 50))
  {
    _cube.all(BLACK);
    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 4) && (currentMillis - _previousMillis >= 150))
  {
    // Do nothing, just delay

    // Remember the time for future reference, and move to the
    // first state
    _previousMillis = currentMillis;

    // Increment the number of lightning flashes shown
    _lightningFlashesShown++;

    if (_lightningFlashesShown < _lightningFlashes)
    {
      // Start the lightning display again
      _state = 2;
    }
    else
    {
      // Go back to raining
      _state = 1;
      _lightningFlashesShown = 0;
    }
  }
}

void RainStorm::clouds() {
  if (_showClouds) {
    _cube.setplane(Z, 3, WHITE);
  }
}

void RainStorm::lightning() {
  if (random(_lightingInterval) == 1)
  {
    // Yes we should show lightning, so set the state
    // to the first part of lightning
    _state = 2;

    // Determine the number of flashes to use
    _lightningFlashes = random(0, _maxLightningBolts + 1);
  }
  else
  {
    // No lightning, so set state to the rain state
    _state = 1;
  }
}

