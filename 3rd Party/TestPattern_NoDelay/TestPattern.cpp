/*
    File:     TestPattern.cpp
    Purpose:  TestPattern pattern for the Freetronics 4x4x4 Cube (non blocking)

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

// Include for helper functions for the cube
#include "Cube4_ARUtils.h"

// Include the header file for this class
#include "TestPattern.h"

TestPattern::TestPattern(Cube cube)
{
  // Retain the reference to the cube
  _cube = cube;

  // Set the default initial state for the animation
  _state = 1;

  // Track where we are in the array of LED coordinates for the animation
  _xyzPos = 1;

  // Build the full array of LEDs so that we have coordinates to match the above coordinates
  buildLEDsArray(_leds);

  // Set the initial brightness for the fadeWhite
  _brightness = 0;

  // Set that we should be increasing brightness
  _brightnessIncrease = true;

  // Set the time we last ran the code to zero as it hasn't run yet
  _previousMillis = 0;

  // Seed the random number generator
  randomSeed(analogRead(UNUSED_ANALOG_PIN));
}

void TestPattern::stepThroughLEDs(rgb_t theColour)
{
  // Handles drawing the TestPattern stepThroughLEDs animation.

  /* This code is designed to be non blocking, so instead of using
     "delay()", it uses a state machine to track where it is upto in the
     animation. It then uses the time and the difference between this run
     and the last run to determine if it needs to change to a different
     state
  */

  // Get the current time
  unsigned long currentMillis = millis();

  if ((currentMillis - _previousMillis >= 500))
  {
    _cube.all(BLACK);
    _cube.set(_leds[_xyzPos].x, _leds[_xyzPos].y, _leds[_xyzPos].z, theColour);
    _xyzPos++;

    if (_xyzPos > 64) {
      _xyzPos = 1;
    }

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
}

void TestPattern::cycleCubeColours()
{
  // Handles drawing the TestPattern cycleCubeColours animation.

  // Get the current time
  unsigned long currentMillis = millis();

  if ((_state == 1) && (currentMillis - _previousMillis >= 1000))
  {
    _cube.all(RED);
    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 2) && (currentMillis - _previousMillis >= 1000))
  {
    _cube.all(GREEN);
    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 3) && (currentMillis - _previousMillis >= 1000))
  {
    _cube.all(BLUE);
    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 4) && (currentMillis - _previousMillis >= 1000))
  {
    _cube.all(ORANGE);
    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 5) && (currentMillis - _previousMillis >= 1000))
  {
    _cube.all(PINK);
    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 6) && (currentMillis - _previousMillis >= 1000))
  {
    _cube.all(RGB(0x00, 0x44, 0xA));
    // Remember the time for future reference, and move back to
    // the first state
    _previousMillis = currentMillis;
    _state = 1;
  }
}

void TestPattern::fadeWhite()
{
  // Handles drawing the TestPattern fadeWhite animation.

  // Get the current time
  unsigned long currentMillis = millis();

  if ((currentMillis - _previousMillis >= 3))
  {
    _cube.all(RGB(_brightness, _brightness, _brightness));

    if (_brightnessIncrease) {
      _brightness++;
      if (_brightness > 255) {
        _brightness = 255;
        _brightnessIncrease = false;
      }
    }
    else
    {
      _brightness--;
      if (_brightness < 0) {
        _brightness = 0;
        _brightnessIncrease = true;
      }
    }

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
}

void TestPattern::randomPastel() {
  // Handles drawing the Random Pastels Colours animation.

  // Get the current time
  unsigned long currentMillis = millis();

  if (currentMillis - _previousMillis >= 2)
  {
    // Pick a random x, y, z, location on the cube, and set it's colour to
    // the mixture of random values of red, green and blue (each between 0 and 255)
    _cube.set(random(0, 4), random(0, 4), random(0, 4), RGB(random(0, 256), random(0, 256), random(0, 256)));

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
}


