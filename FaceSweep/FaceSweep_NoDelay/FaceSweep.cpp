/*
    File:     FaceSweep.cpp
    Purpose:  FaceSweep pattern for the Freetronics 4x4x4 Cube (non blocking)
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
#include "FaceSweep.h"

FaceSweep::FaceSweep(Cube cube, int moveDelay, int sweepPause)
{
  // Retain the reference to the cube
  _cube = cube;

  // Retain the delays we will use
  _moveDelay = moveDelay;
  _sweepPause = sweepPause;

  // Set the default initial state for the animation
  _state = 0;

  // Set the time we last ran the code to zero as it hasn't run yet
  _previousMillis = 0;
}

void FaceSweep::update(rgb_t theColour)
{
  // Handles drawing the FaceSweep animation.

  /* This code is designed to be non blocking, so instead of using
     "delay()", it uses a state machine to track where it is upto in the
     animation. It then uses the time and the difference between this run
     and the last run to determine if it needs to change to a different
     state
  */

  // Get the current time
  unsigned long currentMillis = millis();

  if ((_state == 0) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Clear the CUBE
    _cube.all(BLACK);

    // Move 1: Face Y0 -> Z3 (1 -> 5)
    // Step 1
    _cube.setplane(Y, 0, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 1) && (currentMillis - _previousMillis >= _sweepPause))
  {
    // Delay at end of a move

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 2) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 1 - Step 2
    _cube.line(0, 0, 0, 3, 0, 0, BLACK);
    _cube.line(0, 1, 0, 3, 1, 0, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 3) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 1 - Step 3
    _cube.line(0, 1, 0, 3, 1, 0, BLACK);
    _cube.line(0, 0, 1, 3, 0, 1, BLACK);
    _cube.line(0, 2, 0, 3, 2, 0, theColour);
    _cube.line(0, 1, 1, 3, 1, 1, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 4) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 1 - Step 4
    _cube.line(0, 2, 0, 3, 2, 0, BLACK);
    _cube.line(0, 1, 1, 3, 1, 1, BLACK);
    _cube.line(0, 0, 2, 3, 0, 2, BLACK);
    _cube.line(0, 3, 0, 3, 3, 0, theColour);
    _cube.line(0, 2, 1, 3, 2, 1, theColour);
    _cube.line(0, 1, 2, 3, 1, 2, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 5) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 1 - Step 5
    _cube.line(0, 3, 0, 3, 3, 0, BLACK);
    _cube.line(0, 2, 1, 3, 2, 1, BLACK);
    _cube.line(0, 1, 2, 3, 1, 2, BLACK);
    _cube.line(0, 3, 1, 3, 3, 1, theColour);
    _cube.line(0, 2, 2, 3, 2, 2, theColour);
    _cube.line(0, 1, 3, 3, 1, 3, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 6) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 1 - Step 6
    _cube.line(0, 3, 1, 3, 3, 1, BLACK);
    _cube.line(0, 2, 2, 3, 2, 2, BLACK);
    _cube.line(0, 3, 2, 3, 3, 2, theColour);
    _cube.line(0, 2, 3, 3, 2, 3, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 7) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 1 - Step 7
    _cube.line(0, 3, 2, 3, 3, 2, BLACK);
    _cube.line(0, 3, 3, 3, 3, 3, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 8) && (currentMillis - _previousMillis >= _sweepPause))
  {
    // Delay at end of a move

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 9) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 2: Face Z3 -> X3 (5 -> 4)
    // Step 1
    _cube.line(0, 0, 3, 0, 3, 3, BLACK);
    _cube.line(0, 0, 2, 0, 3, 2, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 10) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 2 - Step 2
    _cube.line(0, 0, 2, 0, 3, 2, BLACK);
    _cube.line(1, 0, 3, 1, 3, 3, BLACK);
    _cube.line(0, 0, 1, 0, 3, 1, theColour);
    _cube.line(1, 0, 2, 1, 3, 2, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 11) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 2 - Step 3
    _cube.line(0, 0, 1, 0, 3, 1, BLACK);
    _cube.line(1, 0, 2, 1, 3, 2, BLACK);
    _cube.line(2, 0, 3, 2, 3, 3, BLACK);
    _cube.line(0, 0, 0, 0, 3, 0, theColour);
    _cube.line(1, 0, 1, 1, 3, 1, theColour);
    _cube.line(2, 0, 2, 2, 3, 2, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 12) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 2 - Step 4
    _cube.line(0, 0, 0, 0, 3, 0, BLACK);
    _cube.line(1, 0, 1, 1, 3, 1, BLACK);
    _cube.line(2, 0, 2, 2, 3, 2, BLACK);
    _cube.line(1, 0, 0, 1, 3, 0, theColour);
    _cube.line(2, 0, 1, 2, 3, 1, theColour);
    _cube.line(3, 0, 2, 3, 3, 2, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 13) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 2 - Step 5
    _cube.line(1, 0, 0, 1, 3, 0, BLACK);
    _cube.line(2, 0, 1, 2, 3, 1, BLACK);
    _cube.line(2, 0, 0, 2, 3, 0, theColour);
    _cube.line(3, 0, 1, 3, 3, 1, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 14) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 2 - Step 6
    _cube.line(2, 0, 0, 2, 3, 0, BLACK);
    _cube.line(3, 0, 0, 3, 3, 0, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 15) && (currentMillis - _previousMillis >= _sweepPause))
  {
    // Delay at end of a move

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 16) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 3: Face X3 -> Y3 (4 -> 3)
    // Step 1
    _cube.line(3, 0, 0, 3, 0, 3, BLACK);
    _cube.line(2, 0, 0, 2, 0, 3, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 17) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 3 - Step 2
    _cube.line(3, 1, 0, 3, 1, 3, BLACK);
    _cube.line(2, 0, 0, 2, 0, 3, BLACK);
    _cube.line(1, 0, 0, 1, 0, 3, theColour);
    _cube.line(2, 1, 0, 2, 1, 3, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 18) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 3 - Step 3
    _cube.line(3, 2, 0, 3, 2, 3, BLACK);
    _cube.line(1, 0, 0, 1, 0, 3, BLACK);
    _cube.line(2, 1, 0, 2, 1, 3, BLACK);
    _cube.line(0, 0, 0, 0, 0, 3, theColour);
    _cube.line(1, 1, 0, 1, 1, 3, theColour);
    _cube.line(2, 2, 0, 2, 2, 3, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 19) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 3 - Step 4
    _cube.line(0, 0, 0, 0, 0, 3, BLACK);
    _cube.line(1, 1, 0, 1, 1, 3, BLACK);
    _cube.line(2, 2, 0, 2, 2, 3, BLACK);
    _cube.line(0, 1, 0, 0, 1, 3, theColour);
    _cube.line(1, 2, 0, 1, 2, 3, theColour);
    _cube.line(2, 3, 0, 2, 3, 3, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 20) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 3 - Step 5
    _cube.line(0, 1, 0, 0, 1, 3, BLACK);
    _cube.line(1, 2, 0, 1, 2, 3, BLACK);
    _cube.line(0, 2, 0, 0, 2, 3, theColour);
    _cube.line(1, 3, 0, 1, 3, 3, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 21) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 3 - Step 6
    _cube.line(0, 2, 0, 0, 2, 3, BLACK);
    _cube.line(0, 3, 0, 0, 3, 3, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 22) && (currentMillis - _previousMillis >= _sweepPause))
  {
    // Delay at end of a move

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 23) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 4: Face Y3 -> Z0 (3 -> 6)
    // Step 1
    _cube.line(0, 3, 3, 3, 3, 3, BLACK);
    _cube.line(0, 2, 3, 3, 2, 3, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 24) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 4 - Step 2
    _cube.line(0, 2, 3, 3, 2, 3, BLACK);
    _cube.line(0, 3, 2, 3, 3, 2, BLACK);
    _cube.line(0, 1, 3, 3, 1, 3, theColour);
    _cube.line(0, 2, 2, 3, 2, 2, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 25) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 4 - Step 3
    _cube.line(0, 1, 3, 3, 1, 3, BLACK);
    _cube.line(0, 2, 2, 3, 2, 2, BLACK);
    _cube.line(0, 3, 1, 3, 3, 1, BLACK);
    _cube.line(0, 0, 3, 3, 0, 3, theColour);
    _cube.line(0, 1, 2, 3, 1, 2, theColour);
    _cube.line(0, 2, 1, 3, 2, 1, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 26) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 4 - Step 4
    _cube.line(0, 0, 3, 3, 0, 3, BLACK);
    _cube.line(0, 1, 2, 3, 1, 2, BLACK);
    _cube.line(0, 2, 1, 3, 2, 1, BLACK);
    _cube.line(0, 0, 2, 3, 0, 2, theColour);
    _cube.line(0, 1, 1, 3, 1, 1, theColour);
    _cube.line(0, 2, 0, 3, 2, 0, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 27) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 4 - Step 5
    _cube.line(0, 0, 2, 3, 0, 2, BLACK);
    _cube.line(0, 1, 1, 3, 1, 1, BLACK);
    _cube.line(0, 0, 1, 3, 0, 1, theColour);
    _cube.line(0, 1, 0, 3, 1, 0, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 28) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 4 - Step 6
    _cube.line(0, 0, 1, 3, 0, 1, BLACK);
    _cube.line(0, 0, 0, 3, 0, 0, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 29) && (currentMillis - _previousMillis >= _sweepPause))
  {
    // Delay at end of a move

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 30) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 5: Face Z0 -> X0 (6 -> 2)
    // Step 1
    _cube.line(3, 0, 0, 3, 3, 0, BLACK);
    _cube.line(3, 0, 1, 3, 3, 1, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 31) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 5 - Step 2
    _cube.line(3, 0, 1, 3, 3, 1, BLACK);
    _cube.line(2, 0, 0, 2, 3, 0, BLACK);
    _cube.line(3, 0, 2, 3, 3, 2, theColour);
    _cube.line(2, 0, 1, 2, 3, 1, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 32) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 5 - Step 3
    _cube.line(3, 0, 2, 3, 3, 2, BLACK);
    _cube.line(2, 0, 1, 2, 3, 1, BLACK);
    _cube.line(1, 0, 0, 1, 3, 0, BLACK);
    _cube.line(3, 0, 3, 3, 3, 3, theColour);
    _cube.line(2, 0, 2, 2, 3, 2, theColour);
    _cube.line(1, 0, 1, 1, 3, 1, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 33) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 5 - Step 4
    _cube.line(3, 0, 3, 3, 3, 3, BLACK);
    _cube.line(2, 0, 2, 2, 3, 2, BLACK);
    _cube.line(1, 0, 1, 1, 3, 1, BLACK);
    _cube.line(2, 0, 3, 2, 3, 3, theColour);
    _cube.line(1, 0, 2, 1, 3, 2, theColour);
    _cube.line(0, 0, 1, 0, 3, 1, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 34) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 5 - Step 5
    _cube.line(2, 0, 3, 2, 3, 3, BLACK);
    _cube.line(1, 0, 2, 1, 3, 2, BLACK);
    _cube.line(1, 0, 3, 1, 3, 3, theColour);
    _cube.line(0, 0, 2, 0, 3, 2, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 35) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 5 - Step 6
    _cube.line(1, 0, 3, 1, 3, 3, BLACK);
    _cube.line(0, 0, 3, 0, 3, 3, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 36) && (currentMillis - _previousMillis >= _sweepPause))
  {
    // Delay at end of a move

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 37) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 6: Face X0 -> Y0 (2 -> 1)
    // Step 1
    _cube.line(0, 3, 0, 0, 3, 3, BLACK);
    _cube.line(1, 3, 0, 1, 3, 3, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 38) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 6 - Step 2
    _cube.line(1, 3, 0, 1, 3, 3, BLACK);
    _cube.line(0, 2, 0, 0, 2, 3, BLACK);
    _cube.line(2, 3, 0, 2, 3, 3, theColour);
    _cube.line(1, 2, 0, 1, 2, 3, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 39) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 6 - Step 3
    _cube.line(2, 3, 0, 2, 3, 3, BLACK);
    _cube.line(1, 2, 0, 1, 2, 3, BLACK);
    _cube.line(0, 1, 0, 0, 1, 3, BLACK);
    _cube.line(1, 1, 0, 1, 1, 3, theColour);
    _cube.line(2, 2, 0, 2, 2, 3, theColour);
    _cube.line(3, 3, 0, 3, 3, 3, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 40) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 6 - Step 4
    _cube.line(1, 1, 0, 1, 1, 3, BLACK);
    _cube.line(2, 2, 0, 2, 2, 3, BLACK);
    _cube.line(3, 3, 0, 3, 3, 3, BLACK);
    _cube.line(3, 2, 0, 3, 2, 3, theColour);
    _cube.line(2, 1, 0, 2, 1, 3, theColour);
    _cube.line(1, 0, 0, 1, 0, 3, theColour);

    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 41) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 6 - Step 5
    _cube.line(3, 2, 0, 3, 2, 3, BLACK);
    _cube.line(2, 1, 0, 2, 1, 3, BLACK);
    _cube.line(3, 1, 0, 3, 1, 3, theColour);
    _cube.line(2, 0, 0, 2, 0, 3, theColour);
    // Remember the time for future reference, and move to the
    // next state
    _previousMillis = currentMillis;
    _state++;
  }
  else if ((_state == 42) && (currentMillis - _previousMillis >= _moveDelay))
  {
    // Move 6 - Step 6
    _cube.line(3, 1, 0, 3, 1, 3, BLACK);
    _cube.line(3, 0, 0, 3, 0, 3, theColour);

    // Remember the time for future reference, and move to the
    // first state
    _previousMillis = currentMillis;
    _state = 0;
  }
}

