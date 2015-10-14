
#include "SPI.h"
#include "Cube.h"

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
    serial->println("Expanding v1.0");
  }
}

void loop(void) {
  rgb_t theColour = BLUE;
  int theDelay = 100;

  cube.all(BLACK);
  delay(theDelay);

  expand(0, 0, 0, RED, theDelay);
  expand(0, 3, 0, GREEN, theDelay);
  expand(3, 3, 0, BLUE, theDelay);
  expand(3, 0, 0, YELLOW, theDelay);
  
  expand(0, 0, 3, PINK, theDelay);
  expand(0, 3, 3, WHITE, theDelay);
  expand(3, 3, 3, PURPLE, theDelay);
  expand(3, 0, 3, ORANGE, theDelay);
}

void expand(byte x, byte y, byte z, rgb_t theColour, int theDelay)
{
  // Track the users original starting point
  byte xOrig = x;
  byte yOrig = y;
  byte zOrig = z;

  // Track the start and end point for the box
  byte startX = x;
  byte startY = y;
  byte startZ = z;
  byte endX = x;
  byte endY = y;
  byte endZ = z;

  cube.all(BLACK);
  cube.set(xOrig, yOrig, zOrig, theColour);
  delay(theDelay);

  // Expand
  for (byte i = 1; i <= 3; i++)
  {
    if (xOrig == 0 && yOrig == 0 && zOrig == 0) {
      endX++;
      endY++;
      endZ++;
    }

    if (xOrig == 0 && yOrig == 3 && zOrig == 0) {
      startY--;
      endX++;
      endZ++;
    }

    if (xOrig == 3 && yOrig == 3 && zOrig == 0) {
      startX--;
      startY--;
      endZ++;
    }

    if (xOrig == 3 && yOrig == 0 && zOrig == 0) {
      startX--;
      endY++;
      endZ++;
    }

    if (xOrig == 0 && yOrig == 0 && zOrig == 3) {
      startZ--;
      endX++;
      endY++;
    }

    if (xOrig == 0 && yOrig == 3 && zOrig == 3) {
      startY--;
      startZ--;
      endX++;
    }

    if (xOrig == 3 && yOrig == 3 && zOrig == 3) {
      startX--;
      startY--;
      startZ--;
    }

    if (xOrig == 3 && yOrig == 0 && zOrig == 3) {
      startX--;
      startZ--;
      endY++;
    }

    cube.box(startX, startY, startZ, endX, endY, endZ, theColour);
    delay(theDelay);
  }

  // Contract
  for (byte i = 1; i <= 2; i++)
  {

    if (xOrig == 0 && yOrig == 0 && zOrig == 0) {
      endX--;
      endY--;
      endZ--;
    }

    if (xOrig == 0 && yOrig == 3 && zOrig == 0) {
      startY++;
      endX--;
      endZ--;
    }

    if (xOrig == 3 && yOrig == 3 && zOrig == 0) {
      startX++;
      startY++;
      endZ--;
    }

    if (xOrig == 3 && yOrig == 0 && zOrig == 0) {
      startX++;
      endY--;
      endZ--;
    }

    if (xOrig == 0 && yOrig == 0 && zOrig == 3) {
      startZ++;
      endX--;
      endY--;
    }

    if (xOrig == 0 && yOrig == 3 && zOrig == 3) {
      startY++;
      startZ++;
      endX--;
    }

    if (xOrig == 3 && yOrig == 3 && zOrig == 3) {
      startX++;
      startY++;
      startZ++;
    }

    if (xOrig == 3 && yOrig == 0 && zOrig == 3) {
      startX++;
      startZ++;
      endY--;
    }

    cube.all(BLACK);
    cube.box(startX, startY, startZ, endX, endY, endZ, theColour);
    delay(theDelay);
  }

  cube.all(BLACK);
  cube.set(xOrig, yOrig, zOrig, theColour);
  delay(theDelay);
}

