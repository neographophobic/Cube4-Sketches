/*
    File:     Heartbeat.h
    Purpose:  Heartbeat pattern for the Freetronics 4x4x4 Cube (non blocking)

    Original Author:   Jonathan Oxer (jon@freetronics.com)
    License:           GPLv3
    The example is part of the Cube4 Library from Freetronics
    https://github.com/freetronics/Cube4. I've changed the drawing
    to use my library's buildLEDArray function which removed the need
    for the while loops.

    Modified by:       Adam Reed (adam@secretcode.ninja)
*/

// Ensure that this header file is only processed once, regardless of how
// many time it is included
#ifndef Heartbeat_h
#define Heartbeat_h

// Include for Arduino Library
#include <Arduino.h>

// Include for Cube Library
#include "Cube.h"

// Include for helper functions for the cube
#include "Cube4_ARUtils.h"

// Declare out class, with public and private variables and functions
class Heartbeat {
  public:
    // Constructor method, requiring the cube class, and the various
    // delays in milliseconds between parts of the animation
    Heartbeat(Cube cube, int riseAndFallDelay, int firstBeatDelay, int restDelay, int beatDelay);

    // Function to determine what the current state of the animation
    // should be, and to update the cube to that state if appropriate
    void update();

  private:
    // Reference to the cube
    Cube _cube;

    // riseAndFallDelay tracks how long to pause between
    // the rise and fall animation
    int _riseAndFallDelay;

    // firstBeatDelay tracks how long to pause between
    // the first "beat" and the second.
    int _firstBeatDelay;

    // restDelay is the delay after the second "beat" before
    // we reset and start the two beat cycle again
    int _restDelay;

    // beatDelay is the small delay between lighting up / off
    // the LEDs for the rise or fall of the beat.
    int _beatDelay;

    // The state the animation is in
    int _state;

    // leds is an array of the x,y,z coordinates of each of the
    // LEDs in our cube.
    struct coordinate _leds[TOTAL_LEDS];

    // xyzPos tracks were we are in the leds array
    byte _xyzPos;
    
    // Tracks the time the code was last run
    unsigned long _previousMillis;

    // The rise and fall animations for the heartbeat
    void _rise();
    void _fall();
};

#endif

