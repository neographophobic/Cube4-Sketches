/*
    File:     ColourPulse.cpp
    Purpose:  ColourPulse pattern for the Freetronics 4x4x4 Cube (non blocking)
    Author:   Adam Reed (adam@secretcode.ninja)
    Licence:  BSD 3-Clause Licence
*/

// Include for Arduino Library
#include <Arduino.h>

// Include for Cube Library
#include "Cube.h"

// Include for helper functions for the cube
#include "Cube4_ARUtils.h"

// Include the header file for this class
#include "ColourPulse.h"

ColourPulse::ColourPulse(Cube cube, byte brightnessIncrement, int theDelay)
{
  // Retain the reference to the cube
  _cube = cube;

  // Retain the delay we will use
  _theDelay = theDelay;

  // Retain the update frequency
  _brightnessIncrement = brightnessIncrement;

  // Set the default initial state for the animation
  _state = 1;

  // Set the time we last ran the code to zero as it hasn't run yet
  _previousMillis = 0;

  // Set the initial brightness
  _brightness = 1;
}

void ColourPulse::update(rgb_t theColour)
{
  // Handles drawing the ColourPulse animation.

  /* This code is designed to be non blocking, so instead of using
     "delay()", it uses a state machine to track where it is upto in the
     animation. It then uses the time and the difference between this run
     and the last run to determine if it needs to change to a different
     state
  */

  // Get the current time
  unsigned long currentMillis = millis();

  // Convert the provided colour to the HSV representation
  struct hsv theColourInHSV = rgb2hsv(theColour);

  // In HSV color, "V" stands for value which is the "brightness"
  // of the colour. By increasing or decreasing this we can keep the
  // colour, but make it appear brighter or darker

  // Get the brightness value from the HSV colour as an int
  int initialBrightness = (int) theColourInHSV.v;

  if ((_state == 1) && (currentMillis - _previousMillis >= _theDelay))
  {
    if (_brightness >= initialBrightness)
    {
      // We have hit the maximum brightness for this colour, so
      // move to the other state
      _state = 2;

      // Reset brigtness
      _brightness = initialBrightness;
    } else {

      // Update the cube with the given brightness for the provided colour
      updateCubeColour(theColourInHSV, _brightness);

      // Update the brightness by the previously provided increment value
      _brightness = _brightness + _brightnessIncrement;
    }
    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
  else if ((_state == 2) && (currentMillis - _previousMillis >= _theDelay))
  {
    if (_brightness <= 1)
    {
      // We have hit the minimum brightness for this colour, so
      // move to the other state
      _state = 1;

      // Reset brigtness
      _brightness = 0;
    } else {

      // Update the cube with the given brightness for the provided colour
      updateCubeColour(theColourInHSV, _brightness);

      // Update the brightness by the previously provided increment value
      _brightness = _brightness - _brightnessIncrement;
    }

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
}

// updateCubeColour:  Taking the colour in HSV, and a new brightness value
//                    then convert it to RGB and set the cube to that colour
void ColourPulse::updateCubeColour(struct hsv theColourInHSV, int brightness) {
  // Update the brightness value
  theColourInHSV.v = brightness;

  // Convert the newly updated HSV value into RGB
  rgb_t theNewColour = hsv2rgb(theColourInHSV);

  // Update the cube with the new colour
  _cube.all(theNewColour);
}

