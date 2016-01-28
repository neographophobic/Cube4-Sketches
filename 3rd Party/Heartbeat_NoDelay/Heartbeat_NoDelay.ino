/*
    File:     Heartbeat_NoDelay.ino
    Purpose:  Heartbeat pattern for the Freetronics 4x4x4 Cube (non blocking)

    Original Author:   Jonathan Oxer (jon@freetronics.com)
    License:           GPLv3
    The example is part of the Cube4 Library from Freetronics
    https://github.com/freetronics/Cube4. I've changed the drawing
    to use my library's buildLEDArray function which removed the need
    for the while loops.

    Modified by:       Adam Reed (adam@secretcode.ninja)
*/

// Include required libraries
#include "Cube.h"
#include "Cube4_ARUtils.h"
#include "Heartbeat.h"

/*
   User editable variables
*/
// riseAndFallDelay tracks how long to pause between 
// the rise and fall animation
int riseAndFallDelay = 40;

// firstBeatDelay tracks how long to pause between
// the first "beat" and the second.
int firstBeatDelay = 100;

// restDelay is the delay after the second "beat" before
// we reset and start the two beat cycle again
int restDelay = 1000;

// beatDelay is the small delay between lighting up / off
// the LEDs for the rise or fall of the beat.
int beatDelay = 4;

// Create an instance of the cube class
Cube cube;

// Create an instance of the Heartbeat class
Heartbeat heartbeat(cube, riseAndFallDelay, firstBeatDelay, restDelay, beatDelay);

void setup(void) {
  // Serial port options for control of the Cube using serial commands are:
  // 0: Control via the USB connector (most common).
  // 1: Control via the RXD and TXD pins on the main board.
  // -1: Don't attach any serial port to interact with the Cube.
  cube.begin(0, 115200); // Start on serial port 0 (USB) at 115200 baud

  // Wait for the serial interface, to be established, or for a maximum of
  // 3 seconds.
  byte waitCounter = 0;
  while (waitCounter < 30 && !Serial) {
    delay(100);
    waitCounter++;
  }

  // Print Debug Info if a serial interface is present
  if (Serial)
  {
    serial->println("Heartbeat v1.0 (non-blocking)");
  }
}

void loop(void) {
  heartbeat.update();
}

