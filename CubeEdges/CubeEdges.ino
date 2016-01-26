
/*
    File:     CubeEdges.ino
    Purpose:  CubeEdges pattern for the Freetronics 4x4x4 Cube
    Author:   Adam Reed (adam@secretcode.ninja)
    Licence:  BSD 3-Clause Licence

    Inspired by Trilobyte Projects "4x4x4 Led cube demo"
    at https://www.youtube.com/watch?v=adXXSitxPdo&t=91
*/

// Include required libraries
#include <SPI.h>
#include "Cube.h"
#include "Cube4_ARUtils.h"

/*
   User editable variables
*/
rgb_t theColour = BLUE;   // The colour to use
int theDelay = 100;       // How long to pause between each step

/*
   Don't edit these variables
*/
// Create an instance of the cube class
Cube cube;

// Struct to track the 3 X,Y,Z positions we end up
// after an animation sequence
struct endPoints
{
  struct coordinate point1;
  struct coordinate point2;
  struct coordinate point3;
};

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
    serial->println("Cube Edges v1.0");
  }
}

void loop(void) {
  // Animate the edges of the cube, starting from 033 (Corner 6)
  cubeEdge(0, 3, 3, theColour, theDelay);
  // Wipe the edges, starting from 000 (Corner 1)
  cubeEdge(0, 0, 0, BLACK, theDelay);

  // Animate the edges of the cube, starting from 000 (Corner 1)
  cubeEdge(0, 0, 0, theColour, theDelay);
  // Wipe the edges, starting from 303 (Corner 8)
  cubeEdge(3, 0, 3, BLACK, theDelay);

  // Animate the edges of the cube, starting from 303 (Corner 8)
  cubeEdge(3, 0, 3, theColour, theDelay);
  // Wipe the edges, starting from 033 (Corner 6)
  cubeEdge(0, 3, 3, BLACK, theDelay);
}

void cubeEdge(byte x, byte y, byte z, rgb_t theColour, int theDelay)
{
  // Start at the initial point
  struct coordinate initialPoint;
  initialPoint.x = x;
  initialPoint.y = y;
  initialPoint.z = z;
  cube.set(initialPoint.x, initialPoint.y, initialPoint.z, theColour);
  delay(theDelay);

  // First part - from the initial point
  struct endPoints newPointsSecondPart;
  for (int i = 1; i <= 3; i++) {
    newPointsSecondPart = lightUpLEDs(initialPoint, i, theColour);
    delay(theDelay);
  }

  // Second Part - from the three new points
  struct endPoints newPointsThirdPart1;
  struct endPoints newPointsThirdPart2;
  struct endPoints newPointsThirdPart3;
  for (int i = 1; i <= 3; i++) {
    newPointsThirdPart1 = lightUpLEDs(newPointsSecondPart.point1, i, theColour);
    newPointsThirdPart2 = lightUpLEDs(newPointsSecondPart.point2, i, theColour);
    newPointsThirdPart3 = lightUpLEDs(newPointsSecondPart.point3, i, theColour);
    delay(theDelay);
  }

  // Final Part - from the nine new points
  for (int i = 1; i <= 3; i++) {
    lightUpLEDs(newPointsThirdPart1.point1, i, theColour);
    lightUpLEDs(newPointsThirdPart1.point2, i, theColour);
    lightUpLEDs(newPointsThirdPart1.point3, i, theColour);

    lightUpLEDs(newPointsThirdPart2.point1, i, theColour);
    lightUpLEDs(newPointsThirdPart2.point2, i, theColour);
    lightUpLEDs(newPointsThirdPart2.point3, i, theColour);

    lightUpLEDs(newPointsThirdPart3.point1, i, theColour);
    lightUpLEDs(newPointsThirdPart3.point2, i, theColour);
    lightUpLEDs(newPointsThirdPart3.point3, i, theColour);
    delay(theDelay);
  }
}

struct endPoints lightUpLEDs(struct coordinate initialPoint, byte animationStep, rgb_t theColour)
{
  // For every given initial point, we move in 3 directions
  struct coordinate newPoint1;
  struct coordinate newPoint2;
  struct coordinate newPoint3;

  // Default the three new positions to the value we were passed
  newPoint1 = initialPoint;
  newPoint2 = initialPoint;
  newPoint3 = initialPoint;

  // Update the new positions to their new location based on where we
  // started from
  byte corner = getCorner(initialPoint);
  switch (corner)
  {
    case 1: // Initial Point: 000 (Corner 1)
      newPoint1.y = initialPoint.y + animationStep;
      newPoint2.x = initialPoint.x + animationStep;
      newPoint3.z = initialPoint.z + animationStep;
      break;
    case 2: // Initial Point: 030 (Corner 2)
      newPoint1.y = initialPoint.y - animationStep;
      newPoint2.x = initialPoint.x + animationStep;
      newPoint3.z = initialPoint.z + animationStep;
      break;
    case 3: // Initial Point: 330 (Corner 3)
      newPoint1.x = initialPoint.x - animationStep;
      newPoint2.y = initialPoint.y - animationStep;
      newPoint3.z = initialPoint.z + animationStep;
      break;
    case 4: // Initial Point: 300 (Corner 4)
      newPoint1.x = initialPoint.x - animationStep;
      newPoint2.y = initialPoint.y + animationStep;
      newPoint3.z = initialPoint.z + animationStep;
      break;
    case 5: // Initial Point: 003 (Corner 5)
      newPoint1.y = initialPoint.y + animationStep;
      newPoint2.x = initialPoint.x + animationStep;
      newPoint3.z = initialPoint.z - animationStep;
      break;
    case 6: // Initial Point: 033 (Corner 6)
      newPoint1.y = initialPoint.y - animationStep;
      newPoint2.x = initialPoint.x + animationStep;
      newPoint3.z = initialPoint.z - animationStep;
      break;
    case 7: // Initial Point: 333 (Corner 7)
      newPoint1.x = initialPoint.x - animationStep;
      newPoint2.y = initialPoint.y - animationStep;
      newPoint3.z = initialPoint.z - animationStep;
      break;
    case 8: // Initial Point: 303 (Corner 8)
      newPoint1.x = initialPoint.x - animationStep;
      newPoint2.y = initialPoint.y + animationStep;
      newPoint3.z = initialPoint.z - animationStep;
      break;
  }

  // Light up the required LEDs
  cube.set(newPoint1.x, newPoint1.y, newPoint1.z, theColour);
  cube.set(newPoint2.x, newPoint2.y, newPoint2.z, theColour);
  cube.set(newPoint3.x, newPoint3.y, newPoint3.z, theColour);

  // Return the 3 X,Y,Z points we have got to with this pass
  struct endPoints theEndPoints;
  theEndPoints.point1 = newPoint1;
  theEndPoints.point2 = newPoint2;
  theEndPoints.point3 = newPoint3;

  return theEndPoints;
}

