/*
    File:     Spiral.cpp
    Purpose:  Spiral pattern for the Freetronics 4x4x4 Cube (non blocking)
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
#include "Spiral.h"

Spiral::Spiral(Cube cube, int theDelay)
{
  // Retain the reference to the cube
  _cube = cube;

  // Retain the delay we will use
  _theDelay = theDelay;

  // Set the default initial state for the animation
  _state = 1;

  // Set the time we last ran the code to zero as it hasn't run yet
  _previousMillis = 0;

  // Track where we are in the array of LED coordinates for the animation
  _counter = 0;

  // Build the full array of LEDs so that we have coordinates to match the above coordinates
  buildLEDsArray(_leds);
}

void Spiral::update(rgb_t theColour)
{
  // Handles drawing the Spiral animation.

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
    drawAnimation(1, theColour);

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
  else if ((_state == 2) && (currentMillis - _previousMillis >= _theDelay))
  {
    drawAnimation(1, BLACK);

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
  else if ((_state == 3) && (currentMillis - _previousMillis >= _theDelay))
  {
    drawAnimation(3, theColour);

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
  else if ((_state == 4) && (currentMillis - _previousMillis >= _theDelay))
  {
    drawAnimation(3, BLACK);

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
  else if ((_state == 5) && (currentMillis - _previousMillis >= _theDelay))
  {
    drawAnimation(5, theColour);

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
  else if ((_state == 6) && (currentMillis - _previousMillis >= _theDelay))
  {
    drawAnimation(5, BLACK);

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
  else if ((_state == 7) && (currentMillis - _previousMillis >= _theDelay))
  {
    drawAnimation(2, theColour);

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
  else if ((_state == 8) && (currentMillis - _previousMillis >= _theDelay))
  {
    drawAnimation(2, BLACK);

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
  else if ((_state == 9) && (currentMillis - _previousMillis >= _theDelay))
  {
    drawAnimation(4, theColour);

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
  else if ((_state == 10) && (currentMillis - _previousMillis >= _theDelay))
  {
    drawAnimation(4, BLACK);

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
  else if ((_state == 11) && (currentMillis - _previousMillis >= _theDelay))
  {
    drawAnimation(6, theColour);

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
  else if ((_state == 12) && (currentMillis - _previousMillis >= _theDelay))
  {
    drawAnimation(6, BLACK);

    // Remember the time for future reference
    _previousMillis = currentMillis;
  }
}

// drawAnimation illuminates the LEDs around the outside of the cube one after the other in one of the 6
// possible directions. The directions are:-
//    * 1 rear to front
//    * 2 front to rear
//    * 3 left to right
//    * 4 right to left
//    * 5 top to bottom
//    * 6 bottom to top
void Spiral::drawAnimation(byte direction, rgb_t theColour)
{
  // Arrays identifying the 48 LEDs that make up the edge coordinates for the animation
  int rearToFront[_itemsToProcess] = {64, 48, 32, 16, 15, 14, 13, 29, 45, 61, 62, 63, 60, 44, 28, 12, 11, 10, 9, 25, 41, 57, 58, 59, 56, 40, 24, 8, 7, 6, 5, 21, 37, 53, 54, 55, 52, 36, 20, 4, 3, 2, 1, 17, 33, 49, 50, 51};
  int frontToRear[_itemsToProcess] = {52, 36, 20, 4, 3, 2, 1, 17, 33, 49, 50, 51, 56, 40, 24, 8, 7, 6, 5, 21, 37, 53, 54, 55, 60, 44, 28, 12, 11, 10, 9, 25, 41, 57, 58, 59, 64, 48, 32, 16, 15, 14, 13, 29, 45, 61, 62, 63};
  int leftToRight[_itemsToProcess] = {49, 33, 17, 1, 5, 9, 13, 29, 45, 61, 57, 53, 50, 34, 18, 2, 6, 10, 14, 30, 46, 62, 58, 54, 51, 35, 19, 3, 7, 11, 15, 31, 47, 63, 59, 55, 52, 36, 20, 4, 8, 12, 16, 32, 48, 64, 60, 56};
  int rightToLeft[_itemsToProcess] = {52, 36, 20, 4, 8, 12, 16, 32, 48, 64 , 60 , 56, 51, 35, 19, 3, 7, 11, 15, 31, 47, 63, 59, 55, 50, 34, 18, 2, 6, 10, 14, 30, 46, 62, 58, 54, 49, 33, 17, 1,  5, 9, 13, 29, 45, 61, 57, 53};
  int topToBottom[_itemsToProcess] = {64, 60, 56, 52, 51, 50, 49, 53, 57, 61, 62, 63, 48, 44, 40, 36, 35, 34, 33, 37, 41, 45, 46, 47, 32 , 28, 24, 20, 19, 18, 17, 21, 25, 29, 30, 31, 16, 12, 8, 4, 3, 2, 1, 5, 9, 13, 14, 15};
  int bottomToTop[_itemsToProcess] = {16, 12, 8, 4, 3, 2, 1, 5, 9, 13, 14, 15, 32 , 28, 24, 20, 19, 18, 17, 21, 25, 29, 30, 31, 48, 44, 40, 36, 35, 34, 33, 37, 41, 45, 46, 47, 64, 60, 56, 52, 51, 50, 49, 53, 57, 61, 62, 63};

  // From the array of LED positions for a given LED, illuminate the appropriate LED
  switch (direction)
  {
    case 1:
      _cube.set(_leds[rearToFront[_counter]].x, _leds[rearToFront[_counter]].y, _leds[rearToFront[_counter]].z, theColour);
      break;
    case 2:
      _cube.set(_leds[frontToRear[_counter]].x, _leds[frontToRear[_counter]].y, _leds[frontToRear[_counter]].z, theColour);
      break;
    case 3:
      _cube.set(_leds[leftToRight[_counter]].x, _leds[leftToRight[_counter]].y, _leds[leftToRight[_counter]].z, theColour);
      break;
    case 4:
      _cube.set(_leds[rightToLeft[_counter]].x, _leds[rightToLeft[_counter]].y, _leds[rightToLeft[_counter]].z, theColour);
      break;
    case 5:
      _cube.set(_leds[topToBottom[_counter]].x, _leds[topToBottom[_counter]].y, _leds[topToBottom[_counter]].z, theColour);
      break;
    case 6:
      _cube.set(_leds[bottomToTop[_counter]].x, _leds[bottomToTop[_counter]].y, _leds[bottomToTop[_counter]].z, theColour);
      break;
  }

  // Increment to the next position in the array of LED coordinates for the animation
  _counter = _counter + 1;

  if (_counter == _itemsToProcess) {
    // Processed all items for this particular animation, so reset the counter and move to the next state
    _counter = 0;
    _state = _state + 1;
    if (_state == 13) {
      // Hit the last state, so return to the first state
      _state = 1;
    }
  }
}

