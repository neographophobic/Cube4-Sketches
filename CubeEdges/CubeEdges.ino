
/*
 * File:    CubeEdges.ino
 * Version: 1.0
 * Author:  Adam Reed (adam@secretcode.ninja)
 * License: BSD 3-Clause Licence
 */

#include "SPI.h"
#include "Cube.h"

Cube cube;

/*
 * User editable variables
 */

struct startPoint
{
  byte X;
  byte Y;
  byte Z;
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
  rgb_t theColour = BLUE;
  int theDelay = 250;

  cube.all(BLACK);
  delay(theDelay * 2);

  // 030 out
  struct startPoint initialPoint;

  struct startPoint middleMovePoint1;
  struct startPoint middleMovePoint2;
  struct startPoint middleMovePoint3;

  struct startPoint finalMovePoint1;
  struct startPoint finalMovePoint2;
  struct startPoint finalMovePoint3;
  struct startPoint finalMovePoint4;
  struct startPoint finalMovePoint5;
  struct startPoint finalMovePoint6;
  struct startPoint finalMovePoint7;
  struct startPoint finalMovePoint8;
  struct startPoint finalMovePoint9;

  initialPoint.X = 0;
  initialPoint.Y = 3;
  initialPoint.Z = 0;

  // From first point
  cube.set(initialPoint.X, initialPoint.Y, initialPoint.Z, theColour);
  delay(theDelay);

  for (int i = 1; i <= 3; i++) {
    cube.set(initialPoint.X + i, initialPoint.Y, initialPoint.Z, theColour);
    cube.set(initialPoint.X, initialPoint.Y - i, initialPoint.Z, theColour);
    cube.set(initialPoint.X, initialPoint.Y, initialPoint.Z + i, theColour);
    delay(theDelay);

    // Note where we end up as this will become the start points
    // for the next set of movements
    middleMovePoint1.X = initialPoint.X + i;
    middleMovePoint1.Y = initialPoint.Y;
    middleMovePoint1.Z = initialPoint.Z;
    
    middleMovePoint2.X = initialPoint.X;
    middleMovePoint2.Y = initialPoint.Y - i;
    middleMovePoint2.Z = initialPoint.Z;

    middleMovePoint3.X = initialPoint.X;
    middleMovePoint3.Y = initialPoint.Y;
    middleMovePoint3.Z = initialPoint.Z + i;
  }
  
  // Second Part - from the three new points
  for (int i = 1; i <= 3; i++) {
    cube.set(middleMovePoint1.X - i, middleMovePoint1.Y, middleMovePoint1.Z, theColour);
    cube.set(middleMovePoint1.X, middleMovePoint1.Y - i, middleMovePoint1.Z, theColour);
    cube.set(middleMovePoint1.X, middleMovePoint1.Y, middleMovePoint1.Z + i, theColour);

    cube.set(middleMovePoint2.X + i, middleMovePoint2.Y, middleMovePoint2.Z, theColour);
    cube.set(middleMovePoint2.X, middleMovePoint2.Y + i, middleMovePoint2.Z, theColour);
    cube.set(middleMovePoint2.X, middleMovePoint2.Y, middleMovePoint2.Z + i, theColour);

    cube.set(middleMovePoint3.X + i, middleMovePoint3.Y, middleMovePoint3.Z, theColour);
    cube.set(middleMovePoint3.X, middleMovePoint3.Y - i, middleMovePoint3.Z, theColour);
    cube.set(middleMovePoint3.X, middleMovePoint3.Y, middleMovePoint3.Z - i, theColour);
    delay(theDelay);

    // Note where we end up as this will become the start points
    // for the next set of movements
    finalMovePoint1.X = middleMovePoint1.X - i;
    finalMovePoint1.Y = middleMovePoint1.Y;
    finalMovePoint1.Z = middleMovePoint1.Z;
    
    finalMovePoint2.X = middleMovePoint1.X;
    finalMovePoint2.Y = middleMovePoint1.Y - i;
    finalMovePoint2.Z = middleMovePoint1.Z;

    finalMovePoint3.X = middleMovePoint1.X;
    finalMovePoint3.Y = middleMovePoint1.Y;
    finalMovePoint3.Z = middleMovePoint1.Z + i;

    finalMovePoint4.X = middleMovePoint2.X + i;
    finalMovePoint4.Y = middleMovePoint2.Y;
    finalMovePoint4.Z = middleMovePoint2.Z;
    
    finalMovePoint5.X = middleMovePoint2.X;
    finalMovePoint5.Y = middleMovePoint2.Y + i;
    finalMovePoint5.Z = middleMovePoint2.Z;

    finalMovePoint6.X = middleMovePoint2.X;
    finalMovePoint6.Y = middleMovePoint2.Y;
    finalMovePoint6.Z = middleMovePoint2.Z + i;

    finalMovePoint7.X = middleMovePoint3.X + i;
    finalMovePoint7.Y = middleMovePoint3.Y;
    finalMovePoint7.Z = middleMovePoint3.Z;
    
    finalMovePoint8.X = middleMovePoint3.X;
    finalMovePoint8.Y = middleMovePoint3.Y - i;
    finalMovePoint8.Z = middleMovePoint3.Z;

    finalMovePoint9.X = middleMovePoint3.X;
    finalMovePoint9.Y = middleMovePoint3.Y;
    finalMovePoint9.Z = middleMovePoint3.Z - i;
}

  // Final Part - from the three new points
//  byte point5X = 0;
//  byte point5Y = 0;
//  byte point5Z = 3;
//
//  byte point6X = 3;
//  byte point6Y = 3;
//  byte point6Z = 3;
//
//  byte point7X = 3;
//  byte point7Y = 0;
//  byte point7Z = 0;
//
//  cube.set(point5X + 1, point5Y, point5Z, theColour);
//  cube.set(point5X, point5Y + 1, point5Z, theColour);
//  cube.set(point5X, point5Y, point5Z - 1, theColour);
//  cube.set(point6X - 1, point6Y, point6Z, theColour);
//  cube.set(point6X, point6Y - 1, point6Z, theColour);
//  cube.set(point6X, point6Y, point6Z - 1, theColour);
//  cube.set(point7X - 1, point7Y, point7Z, theColour);
//  cube.set(point7X, point7Y + 1, point7Z, theColour);
//  cube.set(point7X, point7Y, point7Z + 1, theColour);
//  delay(theDelay);
//
//  cube.set(point5X + 2, point5Y, point5Z, theColour);
//  cube.set(point5X, point5Y + 2, point5Z, theColour);
//  cube.set(point5X, point5Y, point5Z - 2, theColour);
//  cube.set(point6X - 2, point6Y, point6Z, theColour);
//  cube.set(point6X, point6Y - 2, point6Z, theColour);
//  cube.set(point6X, point6Y, point6Z - 2, theColour);
//  cube.set(point7X - 2, point7Y, point7Z, theColour);
//  cube.set(point7X, point7Y + 2, point7Z, theColour);
//  cube.set(point7X, point7Y, point7Z + 2, theColour);
//  delay(theDelay);
//
//  cube.set(point5X + 3, point5Y, point5Z, theColour);
//  cube.set(point5X, point5Y + 3, point5Z, theColour);
//  cube.set(point5X, point5Y, point5Z - 3, theColour);
//  cube.set(point6X - 3, point6Y, point6Z, theColour);
//  cube.set(point6X, point6Y - 3, point6Z, theColour);
//  cube.set(point6X, point6Y, point6Z - 3, theColour);
//  cube.set(point7X - 3, point7Y, point7Z, theColour);
//  cube.set(point7X, point7Y + 3, point7Z, theColour);
//  cube.set(point7X, point7Y, point7Z + 3, theColour);
//  delay(theDelay);
}

}

