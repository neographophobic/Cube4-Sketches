/*
    File:     DoubleCube.cpp
    Purpose:  DoubleCube pattern for the Freetronics 4x4x4 Cube (non blocking)

    Original Author:   ADA
    This example was contributed by sparky-nz on the Freetronics forums:
    http://forum.freetronics.com/viewtopic.php?f=32&t=5579. I've made some
    minor modifications, including simplifying the drawing, and ensuring
    that the random number generator is seeded.

    Modified by:       Adam Reed (adam@secretcode.ninja)
*/

// Include for Arduino Library
#include <Arduino.h>

// Include for Cube Library
#include "Cube.h"

// Include the header file for this class
#include "DoubleCube.h"

DoubleCube::DoubleCube(Cube cube, int theDelay)
{
  // Retain the reference to the cube
  _cube = cube;

  // Retain the delay we will use
  _theDelay = theDelay;

  // Set the time we last ran the code to zero as it hasn't run yet
  _previousMillis = 0;
}

void DoubleCube::update()
{
  // Handles drawing the DoubleCube animation.

  /* This code is designed to be non blocking, so instead of using
     "delay()", it uses a state machine to track where it is upto in the
     animation. It then uses the time and the difference between this run
     and the last run to determine if it needs to change to a different
     state
  */

  // Get the current time
  unsigned long currentMillis = millis();

  // Setup variables to track the colours to use
  byte redValue;
  byte greenValue;
  byte blueValue;

  if (currentMillis - _previousMillis >= _theDelay)
  {
    // Seed the random number generator
    randomSeed(analogRead(UNUSED_ANALOG_PIN));

    // Outer Cube
    redValue = random(0, 2) * 255;
    greenValue = random(0, 2) * 255;
    blueValue = random(0, 2) * 255;
    _cube.box(0, 0, 0, 3, 3, 3, RGB(redValue, greenValue, blueValue), 3);

    // Inner Cube
    redValue = random(0, 2) * 255;
    greenValue = random(0, 2) * 255;
    blueValue = random(0, 2) * 255;
    _cube.box(1, 1, 1, 2, 2, 2, RGB(redValue, greenValue, blueValue), 3);

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
}

