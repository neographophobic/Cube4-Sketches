/*
   File:      EmergencyFlashing.ino
   Purpose:   Emergency Flashing pattern for the Freetronics 4x4x4 Cube

   Original Author:   yatto
   This sketch was contributed by yatto on the Freetronics forums:
   http://forum.freetronics.com/viewtopic.php?f=32&t=6507.

   Modified by:       Adam Reed (adam@secretcode.ninja)
*/

// Include required libraries
#include <SPI.h>
#include "Cube.h"

/*
   User editable variables
*/
int fastDelay = 50;
int slowDelay = 350;

/*
   Don't edit these variables
*/
// Create an instance of the cube class
Cube cube;

void setup(void)
{
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
    serial->println("Emergency Flashing v1.0");
  }}

void loop(void) {
  //Fast Flash
  for (int i = 1; i <= 4; i++) {

    // Red Flash
    for (int j = 1; j <= 3; j++) {
      cube.box(0, 0, 0, 1, 3, 3, RED);
      delay(fastDelay);
      cube.all(BLACK);
      delay(fastDelay);
    }

    // Extra delay between Red and Blue Flashes
    delay(fastDelay);

    // Blue Flash
    for (int j = 1; j <= 3; j++) {
      cube.box(2, 0, 0, 3, 3, 3, BLUE);
      delay(fastDelay);
      cube.all(BLACK);
      delay(fastDelay);
    }

    // Extra delay between Red and Blue Flashes
    delay(fastDelay);
  }

  //Slow Flash
  for (int i = 1; i <= 4; i++) {
    cube.all(BLACK);
    cube.box(0, 0, 0, 1, 3, 3, RED);
    delay(slowDelay);
    cube.all(BLACK);
    cube.box(2, 0, 0, 3, 3, 3, BLUE);
    delay(slowDelay);
  }

  cube.all(BLACK);
}
