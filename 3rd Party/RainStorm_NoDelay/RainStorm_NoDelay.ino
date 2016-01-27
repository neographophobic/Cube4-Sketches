/*
   File:      RainStorm_NoDelay.ino
   Purpose:   RainStorm pattern for the Freetronics 4x4x4 Cube (non blocking)

    Original Author:   Jonathan Oxer (jon@freetronics.com)
    License:           GPLv3
    The example is part of the Cube4 Library from Freetronics
    https://github.com/freetronics/Cube4.

    Modified by:       Adam Reed (adam@secretcode.ninja)
*/

// Include required libraries
#include <SPI.h>
#include "Cube.h"
#include "RainStorm.h"

/*
   User editable variables
*/
// rainDropDelay is the delay between raindrop movements
int rainDropDelay = 50;

// showClouds displays a "cloud" layer at the top
bool showClouds = true;

// lightingInterval is how many raindrops between random 
// lightning strikes, on average
int lightingInterval = 20;

// maxLightningBolts is maximum number of lightning flashes 
// per strick
int maxLightningBolts = 2;

// Create an instance of the cube class
Cube cube;

// Create an instance of the RainStorm class
RainStorm rainstorm(cube, rainDropDelay, showClouds, lightingInterval, maxLightningBolts);

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
    serial->println("RainStorm v1.0 (non-blocking)");
  }
}

void loop(void) {
  rainstorm.update();
}

