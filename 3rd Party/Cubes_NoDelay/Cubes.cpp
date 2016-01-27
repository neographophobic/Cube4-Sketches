/*
   File:      Cubes.cpp
   Purpose:   Cubes pattern for the Freetronics 4x4x4 Cube (non blocking)

   Original Author:   Blake Kus (blakekus@gmail.com)
   License:           GPLv3
   Thia example is part of the Cube4 Library from Freetronics
   https://github.com/freetronics/Cube4.

   Modified by:       Adam Reed (adam@secretcode.ninja)
*/

// Include for Arduino Library
#include <Arduino.h>

// Include for Cube Library
#include "Cube.h"

// Include the header file for this class
#include "Cubes.h"

Cubes::Cubes(Cube cube, int theDelay)
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

void Cubes::update(rgb_t theColour)
{
  // Handles drawing the Cubes animation.

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
    // Solid
    _cube.all(BLACK);
    _cube.box(0, 0, 0, CUBE_SIZE - 1, CUBE_SIZE - 1, CUBE_SIZE - 1, RED);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 2) && (currentMillis - _previousMillis >= _theDelay))
  {
    // Walls only
    _cube.all(BLACK);
    _cube.box(0, 0, 0, CUBE_SIZE - 1, CUBE_SIZE - 1, CUBE_SIZE - 1, GREEN, 1);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 3) && (currentMillis - _previousMillis >= _theDelay))
  {
    // Edges only
    _cube.all(BLACK);
    _cube.box(0, 0, 0, CUBE_SIZE - 1, CUBE_SIZE - 1, CUBE_SIZE - 1, BLUE, 2);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 4) && (currentMillis - _previousMillis >= _theDelay))
  {
    // Walls and inner different colours
    _cube.all(BLACK);
    _cube.box(0, 0, 0, CUBE_SIZE - 1, CUBE_SIZE - 1, CUBE_SIZE - 1, WHITE, 3, RED);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 5) && (currentMillis - _previousMillis >= _theDelay))
  {
    // Edges and inner different colours
    _cube.all(BLACK);
    _cube.box(0, 0, 0, CUBE_SIZE - 1, CUBE_SIZE - 1, CUBE_SIZE - 1, PURPLE, 4, WHITE);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 6) && (currentMillis - _previousMillis >= _theDelay))
  {
    _cube.all(BLACK);
    _cube.box(0, 0, 0, CUBE_SIZE - 1, CUBE_SIZE - 1, CUBE_SIZE - 1, BLACK, 4, RED);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 7) && (currentMillis - _previousMillis >= _theDelay))
  {
    // Hollow sphere
    _cube.all(BLACK);
    _cube.box(0, 0, 0, CUBE_SIZE - 1, CUBE_SIZE - 1, CUBE_SIZE - 1, BLACK, 4, RED);
    _cube.box(1, 1, 1, CUBE_SIZE - 2, CUBE_SIZE - 2, CUBE_SIZE - 2, BLACK);

    // Remember the time for future reference, and move to the
    // first state
    _previousMillis = currentMillis;
    _state = 1;
  }
}

