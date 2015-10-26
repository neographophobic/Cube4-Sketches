
/*
 * File:    CubeEdges.ino
 * Version: 1.0
 * Author:  Adam Reed (adam@secretcode.ninja)
 * License: BSD 3-Clause Licence
 * 
 * Inspired by Trilobyte Projects "4x4x4 Led cube demo"
 * at https://www.youtube.com/watch?v=adXXSitxPdo&t=91
 */

#include "SPI.h"
#include "Cube.h"

Cube cube;

/*
 * User editable variables
 */
rgb_t theColour = BLUE;   // The colour to use
int theDelay = 100;       // How long to pause between each step

/*
 * Don't edit these variables
 */

// Struct to track the X,Y,Z position
struct point
{
  byte X;
  byte Y;
  byte Z;
};

// Struct to track the 3 X,Y,Z positions we end up
// after an animation sequence
struct endPoints
{
  struct point point1;
  struct point point2;
  struct point point3;
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
  // Animate the edges of the cube, starting from 033
  cubeEdge(0,3,3, theColour, theDelay);
  // Wipe the edges, starting from 000
  cubeEdge(0,0,0, BLACK, theDelay);

  // Animate the edges of the cube, starting from 000
  cubeEdge(0,0,0, theColour, theDelay);
  // Wipe the edges, starting from 303
  cubeEdge(3,0,3, BLACK, theDelay);

  // Animate the edges of the cube, starting from 303
  cubeEdge(3,0,3, theColour, theDelay);
  // Wipe the edges, starting from 033
  cubeEdge(0,3,3, BLACK, theDelay);
}

void cubeEdge(byte X, byte Y, byte Z, rgb_t theColour, int theDelay)
{
  // Start at the initial point
  struct point initialPoint;
  initialPoint.X = X;
  initialPoint.Y = Y;
  initialPoint.Z = Z;
  cube.set(initialPoint.X, initialPoint.Y, initialPoint.Z, theColour);
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

struct endPoints lightUpLEDs(struct point initialPoint, byte animationStep, rgb_t theColour)
{
    // For every given initial point, we move in 3 directions
    struct point newPoint1;
    struct point newPoint2;
    struct point newPoint3;

    // Calculate the 3 new positions, based on the initial point

    // Initial Point: 000
    if (initialPoint.X == 0 && initialPoint.Y == 0 && initialPoint.Z == 0) {
      newPoint1.X = initialPoint.X;
      newPoint1.Y = initialPoint.Y + animationStep;
      newPoint1.Z = initialPoint.Z;

      newPoint2.X = initialPoint.X + animationStep;
      newPoint2.Y = initialPoint.Y;
      newPoint2.Z = initialPoint.Z;

      newPoint3.X = initialPoint.X;
      newPoint3.Y = initialPoint.Y;
      newPoint3.Z = initialPoint.Z + animationStep;
    }

    // Initial Point: 030
    if (initialPoint.X == 0 && initialPoint.Y == 3 && initialPoint.Z == 0) {
      newPoint1.X = initialPoint.X;
      newPoint1.Y = initialPoint.Y - animationStep;
      newPoint1.Z = initialPoint.Z;

      newPoint2.X = initialPoint.X + animationStep;
      newPoint2.Y = initialPoint.Y;
      newPoint2.Z = initialPoint.Z;

      newPoint3.X = initialPoint.X;
      newPoint3.Y = initialPoint.Y;
      newPoint3.Z = initialPoint.Z + animationStep;
    }

    // Initial Point: 330
    if (initialPoint.X == 3 && initialPoint.Y == 3 && initialPoint.Z == 0) {
      newPoint1.X = initialPoint.X - animationStep;
      newPoint1.Y = initialPoint.Y;
      newPoint1.Z = initialPoint.Z;

      newPoint2.X = initialPoint.X;
      newPoint2.Y = initialPoint.Y - animationStep;
      newPoint2.Z = initialPoint.Z;

      newPoint3.X = initialPoint.X;
      newPoint3.Y = initialPoint.Y;
      newPoint3.Z = initialPoint.Z + animationStep;
    }

    // Initial Point: 300
    if (initialPoint.X == 3 && initialPoint.Y == 0 && initialPoint.Z == 0) {
      newPoint1.X = initialPoint.X - animationStep;
      newPoint1.Y = initialPoint.Y;
      newPoint1.Z = initialPoint.Z;

      newPoint2.X = initialPoint.X;
      newPoint2.Y = initialPoint.Y + animationStep;
      newPoint2.Z = initialPoint.Z;

      newPoint3.X = initialPoint.X;
      newPoint3.Y = initialPoint.Y;
      newPoint3.Z = initialPoint.Z + animationStep;
    }

    // Initial Point: 003
    if (initialPoint.X == 0 && initialPoint.Y == 0 && initialPoint.Z == 3) {
      newPoint1.X = initialPoint.X;
      newPoint1.Y = initialPoint.Y + animationStep;
      newPoint1.Z = initialPoint.Z;

      newPoint2.X = initialPoint.X + animationStep;
      newPoint2.Y = initialPoint.Y;
      newPoint2.Z = initialPoint.Z;

      newPoint3.X = initialPoint.X;
      newPoint3.Y = initialPoint.Y;
      newPoint3.Z = initialPoint.Z - animationStep;
    }

    // Initial Point: 033
    if (initialPoint.X == 0 && initialPoint.Y == 3 && initialPoint.Z == 3) {
      newPoint1.X = initialPoint.X;
      newPoint1.Y = initialPoint.Y - animationStep;
      newPoint1.Z = initialPoint.Z;

      newPoint2.X = initialPoint.X + animationStep;
      newPoint2.Y = initialPoint.Y;
      newPoint2.Z = initialPoint.Z;

      newPoint3.X = initialPoint.X;
      newPoint3.Y = initialPoint.Y;
      newPoint3.Z = initialPoint.Z - animationStep;
    }

    // Initial Point: 333
    if (initialPoint.X == 3 && initialPoint.Y == 3 && initialPoint.Z == 3) {
      newPoint1.X = initialPoint.X - animationStep;
      newPoint1.Y = initialPoint.Y;
      newPoint1.Z = initialPoint.Z;

      newPoint2.X = initialPoint.X;
      newPoint2.Y = initialPoint.Y - animationStep;
      newPoint2.Z = initialPoint.Z;

      newPoint3.X = initialPoint.X;
      newPoint3.Y = initialPoint.Y;
      newPoint3.Z = initialPoint.Z - animationStep;
    }

    // Initial Point: 303
    if (initialPoint.X == 3 && initialPoint.Y == 0 && initialPoint.Z == 3) {
      newPoint1.X = initialPoint.X - animationStep;
      newPoint1.Y = initialPoint.Y;
      newPoint1.Z = initialPoint.Z;

      newPoint2.X = initialPoint.X;
      newPoint2.Y = initialPoint.Y + animationStep;
      newPoint2.Z = initialPoint.Z;

      newPoint3.X = initialPoint.X;
      newPoint3.Y = initialPoint.Y;
      newPoint3.Z = initialPoint.Z - animationStep;
    }

    // Light up the required LEDs
    cube.set(newPoint1.X, newPoint1.Y, newPoint1.Z, theColour);
    cube.set(newPoint2.X, newPoint2.Y, newPoint2.Z, theColour);
    cube.set(newPoint3.X, newPoint3.Y, newPoint3.Z, theColour);

    // Return the 3 X,Y,Z points we have got to with this pass
    struct endPoints theEndPoints;
    theEndPoints.point1 = newPoint1;
    theEndPoints.point2 = newPoint2;
    theEndPoints.point3 = newPoint3;

    return theEndPoints;
}

