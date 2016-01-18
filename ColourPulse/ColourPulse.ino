/*
 * File:    ColourPulse.ino
 * Version: 1.0
 * Author:  Adam Reed (adam@secretcode.ninja)
 * License: BSD 3-Clause Licence
 */

// Include required libraries
#include <SPI.h>
#include "Cube.h"
#include "Utils.h"

// Define global variables
// frequency influences how often the colour is changes as it fades in and out
//   smaller number mean more frequent
byte frequency = 5;

// theDelay tracks how long to pause between colour changes
byte theDelay = 50;

// theColour sets the colour that is used as the basis of the effect
rgb_t theColour = RGB(0x4B, 0x00, 0x82); // Violet
//rgb_t theColour = GREEN;

// Create an instance of the cube class
Cube cube;

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
    serial->println("Colour Pulse v1.0");
  }
}

void loop(void) {
  struct hsv theColourInHSV = convertHexToHSV(theColour);

  for (int i = 1; i <= 100; i++) {
    int x = i % frequency;
    if (x == 0 ) {
      theColourInHSV.v = i;

      rgb_t theNewColour = hsv2rgb(theColourInHSV);

      cube.all(theNewColour);
      delay(theDelay);
    }
  }
  for (int i = 100; i >= 1; i--) {
    int x = i % frequency;
    if (x == 0 ) {
      theColourInHSV.v = i;

      rgb_t theNewColour = hsv2rgb(theColourInHSV);

      cube.all(theNewColour);
      delay(theDelay);
    }
  }
}






  }
}


