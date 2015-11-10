
/*
 * File:    FacePeel.ino
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

// Struct to track the X,Y,Z position
struct point
{
  byte X;
  byte Y;
  byte Z;
};

struct aLine
{
  struct point startPoint;
  struct point endPoint;
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
    serial->println("FacePeel v1.0");
  }
}

void loop(void) {
  rgb_t theColour = BLUE;
  int theDelay = 100;

  while (1 == 0) {
    // 1 -> 3
    faceDraw(0, 0, 0, 3, 3, 0, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 1 -> 6
    faceDraw(0, 0, 0, 0, 3, 3, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 1 -> 8
    faceDraw(0, 0, 0, 3, 0, 3, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 2 -> 4
    faceDraw(0, 3, 0, 3, 0, 0, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 2 -> 5
    faceDraw(0, 3, 0, 0, 0, 3, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 2 -> 7
    faceDraw(0, 3, 0, 3, 3, 3, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 3 -> 1
    faceDraw(3, 3, 0, 0, 0, 0, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 3 -> 6
    faceDraw(3, 3, 0, 0, 3, 3, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 3 -> 8
    faceDraw(3, 3, 0, 3, 0, 3, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 4 -> 2
    faceDraw(3, 0, 0, 0, 3, 0, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 4 -> 5
    faceDraw(3, 0, 0, 0, 0, 3, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 4 -> 7
    faceDraw(3, 0, 0, 3, 3, 3, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 5 -> 2
    faceDraw(0, 0, 3, 0, 3, 0, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 5 -> 4
    faceDraw(0, 0, 3, 3, 0, 0, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 5 -> 7
    faceDraw(0, 0, 3, 3, 3, 3, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 6 -> 1
    faceDraw(0, 3, 3, 0, 0, 0, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 6 -> 3
    faceDraw(0, 3, 3, 3, 3, 0, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 6 -> 8
    faceDraw(0, 3, 3, 3, 0, 3, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 7 -> 2
    faceDraw(3, 3, 3, 0, 3, 0, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 7 -> 4
    faceDraw(3, 3, 3, 3, 0, 0, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 7 -> 5
    faceDraw(3, 3, 3, 0, 0, 3, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 8 -> 1
    faceDraw(3, 0, 3, 0, 0, 0, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 8 -> 3
    faceDraw(3, 0, 3, 3, 3, 0, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);

    // 8 -> 6
    faceDraw(3, 0, 3, 0, 3, 3, theColour, theDelay);
    delay(theDelay);
    cube.all(BLACK);
    delay(theDelay);
  }
  // Top to Bottom
//  faceDraw(0, 0, 3, 3, 3, 3, theColour, theDelay);
//  peel(0, 0, 3, 3, 3, 3, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);

//  faceDraw(0, 3, 3, 3, 0, 3, theColour, theDelay);
//  peel(0, 3, 3, 3, 0, 3, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);

//  faceDraw(3, 3, 3, 0, 0, 3, theColour, theDelay);
//  peel(3, 3, 3, 0, 0, 3, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);

//  faceDraw(3, 0, 3, 0, 3, 3, theColour, theDelay);
//  peel(3, 0, 3, 0, 3, 3, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);

  // Bottom to Top
//  faceDraw(0, 0, 0, 3, 3, 0, theColour, theDelay);
//  peel(0, 0, 0, 3, 3, 0, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);

//  faceDraw(0, 3, 0, 3, 0, 0, theColour, theDelay);
//  peel(0, 3, 0, 3, 0, 0, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);

//  faceDraw(3, 3, 0, 0, 0, 0, theColour, theDelay);
//  peel(3, 3, 0, 0, 0, 0, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);

//  faceDraw(3, 0, 0, 0, 3, 0, theColour, theDelay);
//  peel(3, 0, 0, 0, 3, 0, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);

  // Front to back
//  faceDraw(0, 0, 0, 3, 0, 3, theColour, theDelay);
//  peel(0, 0, 0, 3, 0, 3, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);

//  faceDraw(0, 0, 3, 3, 0, 0, theColour, theDelay);
//  peel(0, 0, 3, 3, 0, 0, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);

//  faceDraw(3, 0, 3, 0, 0, 0, theColour, theDelay);
//  peel(3, 0, 3, 0, 0, 0, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);

//  faceDraw(3, 0, 0, 0, 0, 3, theColour, theDelay);
//  peel(3, 0, 0, 0, 0, 3, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);  

  // Back to Front
//  faceDraw(0, 3, 0, 3, 3, 3, theColour, theDelay);
//  peel(0, 3, 0, 3, 3, 3, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);

//  faceDraw(0, 3, 3, 3, 3, 0, theColour, theDelay);
//  peel(0, 3, 3, 3, 3, 0, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);

//  faceDraw(3, 3, 3, 0, 3, 0, theColour, theDelay);
//  peel(3, 3, 3, 0, 3, 0, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);

//  faceDraw(3, 3, 0, 0, 3, 3, theColour, theDelay);
//  peel(3, 3, 0, 0, 3, 3, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);  

  // Left to Right
//  faceDraw(0, 0, 0, 0, 3, 3, theColour, theDelay);
//  peel(0, 0, 0, 0, 3, 3, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);

//  faceDraw(0, 3, 0, 0, 0, 3, theColour, theDelay);
//  peel(0, 3, 0, 0, 0, 3, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);

//  faceDraw(0, 3, 3, 0, 0, 0, theColour, theDelay);
//  peel(0, 3, 3, 0, 0, 0, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);

//  faceDraw(0, 0, 3, 0, 3, 0, theColour, theDelay);
//  peel(0, 0, 3, 0, 3, 0, theColour, theDelay);
//  cube.all(BLACK);
//  delay(theDelay);  

  // Right to Left
  faceDraw(3, 3, 0, 3, 0, 3, theColour, theDelay);
  peel(3, 3, 0, 3, 0, 3, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  faceDraw(3, 0, 0, 3, 3, 3, theColour, theDelay);
  peel(3, 0, 0, 3, 3, 3, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  faceDraw(3, 0, 3, 3, 3, 0, theColour, theDelay);
  peel(3, 0, 3, 3, 3, 0, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  faceDraw(3, 3, 3, 3, 0, 0, theColour, theDelay);
  peel(3, 3, 3, 3, 0, 0, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);  
}

void faceDraw(byte x1, byte y1, byte z1, byte x2, byte y2, byte z2, rgb_t theColour, int theDelay)
{
  // 8 Corners to the cube. Determine which ones to use
  byte startPosition = getPosition(x1, y1, z1);
  byte stopPosition = getPosition(x2, y2, z2);

  // From each of the 8 corners there are 3 valid directions
  // broken into 2 sections (start -> middle -> end)

  struct point startPoint;
  struct point endPoint;

  startPoint.X = x1;
  startPoint.Y = y1;
  startPoint.Z = z1;

  endPoint.X = x1;
  endPoint.Y = y1;
  endPoint.Z = z1;

  // First part of the move
  cube.set(startPoint.X, startPoint.Y, startPoint.Z, theColour);
  delay(theDelay);

  // Next 3 steps
  for (byte i = 1; i <= 3; i++) {
    if (startPosition == 1 && stopPosition == 3) {
      startPoint.Y++;
      endPoint.X++;
    } else if (startPosition == 1 && stopPosition == 6) {
      startPoint.Y++;
      endPoint.Z++;
    } else if (startPosition == 1 && stopPosition == 8) {
      startPoint.Z++;
      endPoint.X++;
    }
    if (startPosition == 2 && stopPosition == 4) {
      startPoint.Y--;
      endPoint.X++;
    } else if (startPosition == 2 && stopPosition == 5) {
      startPoint.Y--;
      endPoint.Z++;
    } else if (startPosition == 2 && stopPosition == 7) {
      startPoint.Z++;
      endPoint.X++;
    }
    if (startPosition == 3 && stopPosition == 1) {
      startPoint.X--;
      endPoint.Y--;
    } else if (startPosition == 3 && stopPosition == 6) {
      startPoint.X--;
      endPoint.Z++;
    } else if (startPosition == 3 && stopPosition == 8) {
      startPoint.Y--;
      endPoint.Z++;
    }
    if (startPosition == 4 && stopPosition == 2) {
      startPoint.X--;
      endPoint.Y++;
    } else if (startPosition == 4 && stopPosition == 5) {
      startPoint.X--;
      endPoint.Z++;
    } else if (startPosition == 4 && stopPosition == 7) {
      startPoint.Z++;
      endPoint.Y++;
    }
    if (startPosition == 5 && stopPosition == 2) {
      startPoint.Z--;
      endPoint.Y++;
    } else if (startPosition == 5 && stopPosition == 4) {
      startPoint.Z--;
      endPoint.X++;
    } else if (startPosition == 5 && stopPosition == 7) {
      startPoint.X++;
      endPoint.Y++;
    }
    if (startPosition == 6 && stopPosition == 1) {
      startPoint.Y--;
      endPoint.Z--;
    } else if (startPosition == 6 && stopPosition == 3) {
      startPoint.X++;
      endPoint.Z--;
    } else if (startPosition == 6 && stopPosition == 8) {
      startPoint.Y--;
      endPoint.X++;
    }
    if (startPosition == 7 && stopPosition == 2) {
      startPoint.X--;
      endPoint.Z--;
    } else if (startPosition == 7 && stopPosition == 4) {
      startPoint.Y--;
      endPoint.Z--;
    } else if (startPosition == 7 && stopPosition == 5) {
      startPoint.X--;
      endPoint.Y--;
    }
    if (startPosition == 8 && stopPosition == 1) {
      startPoint.X--;
      endPoint.Z--;
    } else if (startPosition == 8 && stopPosition == 3) {
      startPoint.Z--;
      endPoint.Y++;
    } else if (startPosition == 8 && stopPosition == 6) {
      startPoint.X--;
      endPoint.Y++;
    }

    drawLine(startPoint, endPoint, theColour, theDelay);
  }

  // Final 3 steps
  for (byte i = 1; i <= 3; i++) {
    if (startPosition == 1 && stopPosition == 3) {
      startPoint.X++;
      endPoint.Y++;
    } else if (startPosition == 1 && stopPosition == 6) {
      startPoint.Z++;
      endPoint.Y++;
    } else if (startPosition == 1 && stopPosition == 8) {
      startPoint.X++;
      endPoint.Z++;
    }
    if (startPosition == 2 && stopPosition == 4) {
      startPoint.X++;
      endPoint.Y--;
    } else if (startPosition == 2 && stopPosition == 5) {
      startPoint.Z++;
      endPoint.Y--;
    } else if (startPosition == 2 && stopPosition == 7) {
      startPoint.X++;
      endPoint.Z++;
    }
    if (startPosition == 3 && stopPosition == 1) {
      startPoint.Y--;
      endPoint.X--;
    } else if (startPosition == 3 && stopPosition == 6) {
      startPoint.Z++;
      endPoint.X--;
    } else if (startPosition == 3 && stopPosition == 8) {
      startPoint.Z++;
      endPoint.Y--;
    }
    if (startPosition == 4 && stopPosition == 2) {
      startPoint.Y++;
      endPoint.X--;
    } else if (startPosition == 4 && stopPosition == 5) {
      startPoint.Z++;
      endPoint.X--;
    } else if (startPosition == 4 && stopPosition == 7) {
      startPoint.Y++;
      endPoint.Z++;
    }
    if (startPosition == 5 && stopPosition == 2) {
      startPoint.Y++;
      endPoint.Z--;
    } else if (startPosition == 5 && stopPosition == 4) {
      startPoint.X++;
      endPoint.Z--;
    } else if (startPosition == 5 && stopPosition == 7) {
      startPoint.Y++;
      endPoint.X++;
    }
    if (startPosition == 6 && stopPosition == 1) {
      startPoint.Z--;
      endPoint.Y--;
    } else if (startPosition == 6 && stopPosition == 3) {
      startPoint.Z--;
      endPoint.X++;
    } else if (startPosition == 6 && stopPosition == 8) {
      startPoint.X++;
      endPoint.Y--;
    }
    if (startPosition == 7 && stopPosition == 2) {
      startPoint.Z--;
      endPoint.X--;
    } else if (startPosition == 7 && stopPosition == 4) {
      startPoint.Z--;
      endPoint.Y--;
    } else if (startPosition == 7 && stopPosition == 5) {
      startPoint.Y--;
      endPoint.X--;
    }
    if (startPosition == 8 && stopPosition == 1) {
      startPoint.Z--;
      endPoint.X--;
    } else if (startPosition == 8 && stopPosition == 3) {
      startPoint.Y++;
      endPoint.Z--;
    } else if (startPosition == 8 && stopPosition == 6) {
      startPoint.Y++;
      endPoint.X--;
    }

    drawLine(startPoint, endPoint, theColour, theDelay);
  }
}

void drawLine(struct point startPoint, struct point endPoint, rgb_t theColour, int theDelay)
{
  if (startPoint.Y > endPoint.Y && startPoint.Z < endPoint.Z ||
      startPoint.X > endPoint.X && startPoint.Z == endPoint.Z ||
      startPoint.X > endPoint.X && startPoint.Y == endPoint.Y ||
      startPoint.Y > endPoint.Y && startPoint.X == endPoint.X
     ) {
    // Work around bug in line drawing code by swapping start and
    // end point if particular condiations are meet
    cube.line(endPoint.X, endPoint.Y, endPoint.Z,
              startPoint.X, startPoint.Y, startPoint.Z, theColour);
  } else {
    cube.line(startPoint.X, startPoint.Y, startPoint.Z,
              endPoint.X, endPoint.Y, endPoint.Z, theColour);
  }
  delay(theDelay);
}

void peel(byte x1, byte y1, byte z1, byte x2, byte y2, byte z2, rgb_t theColour, int theDelay)
{
  // 8 Corners to the cube. Determine which ones to use
  byte startPosition = getPosition(x1, y1, z1);
  byte stopPosition = getPosition(x2, y2, z2);

  aLine lines[7];

  // Figure out where the lines to move are
  lines[0].startPoint.X = x1;
  lines[0].startPoint.Y = y1;
  lines[0].startPoint.Z = z1;
  lines[0].endPoint.X = x1;
  lines[0].endPoint.Y = y1;
  lines[0].endPoint.Z = z1;

  for (byte i = 1; i <= 3; i++) {
    lines[i].startPoint.X = lines[i - 1].startPoint.X;
    lines[i].startPoint.Y = lines[i - 1].startPoint.Y;
    lines[i].startPoint.Z = lines[i - 1].startPoint.Z;
    lines[i].endPoint.X = lines[i - 1].endPoint.X;
    lines[i].endPoint.Y = lines[i - 1].endPoint.Y;
    lines[i].endPoint.Z = lines[i - 1].endPoint.Z;

    if (startPosition == 1 && stopPosition == 3) {
      lines[i].startPoint.Y++;
      lines[i].endPoint.X++;
    }
    if (startPosition == 1 && stopPosition == 6) {
      lines[i].startPoint.Z++;
      lines[i].endPoint.Y++;
    }    
    if (startPosition == 1 && stopPosition == 8) {
      lines[i].startPoint.Z++;
      lines[i].endPoint.X++;
    }    
    if (startPosition == 2 && stopPosition == 4) {
      lines[i].startPoint.X++;
      lines[i].endPoint.Y--;
    }
    if (startPosition == 2 && stopPosition == 5) {
      lines[i].startPoint.Y--;
      lines[i].endPoint.Z++;
    }
    if (startPosition == 2 && stopPosition == 7) {
      lines[i].startPoint.Z++;
      lines[i].endPoint.X++;
    }
    if (startPosition == 3 && stopPosition == 1) {
      lines[i].startPoint.X--;
      lines[i].endPoint.Y--;
    }
    if (startPosition == 3 && stopPosition == 6) {
      lines[i].startPoint.X--;
      lines[i].endPoint.Z++;
    }
    if (startPosition == 3 && stopPosition == 8) {
      lines[i].startPoint.Z++;
      lines[i].endPoint.Y--;
    }
    if (startPosition == 4 && stopPosition == 2) {
      lines[i].startPoint.X--;
      lines[i].endPoint.Y++;
    }
    if (startPosition == 4 && stopPosition == 5) {
      lines[i].startPoint.X--;
      lines[i].endPoint.Z++;
    }
    if (startPosition == 4 && stopPosition == 7) {
      lines[i].startPoint.Z++;
      lines[i].endPoint.Y++;
    }
    if (startPosition == 5 && stopPosition == 2) {
      lines[i].startPoint.Z--;
      lines[i].endPoint.Y++;
    }
    if (startPosition == 5 && stopPosition == 4) {
      lines[i].startPoint.Z--;
      lines[i].endPoint.X++;
    }
    if (startPosition == 5 && stopPosition == 7) {
      lines[i].startPoint.X++;
      lines[i].endPoint.Y++;
    }
    if (startPosition == 6 && stopPosition == 1) {
      lines[i].startPoint.Z--;
      lines[i].endPoint.Y--;
    }
    if (startPosition == 6 && stopPosition == 3) {
      lines[i].startPoint.Z--;
      lines[i].endPoint.X++;
    }
    if (startPosition == 6 && stopPosition == 8) {
      lines[i].startPoint.Y--;
      lines[i].endPoint.X++;
    }
    if (startPosition == 7 && stopPosition == 2) {
      lines[i].startPoint.X--;
      lines[i].endPoint.Z--;
    }
    if (startPosition == 7 && stopPosition == 4) {
      lines[i].startPoint.Y--;
      lines[i].endPoint.Z--;
    }
    if (startPosition == 7 && stopPosition == 5) {
      lines[i].startPoint.X--;
      lines[i].endPoint.Y--;
    }
    if (startPosition == 8 && stopPosition == 1) {
      lines[i].startPoint.X--;
      lines[i].endPoint.Z--;
    }
    if (startPosition == 8 && stopPosition == 3) {
      lines[i].startPoint.Y++;
      lines[i].endPoint.Z--;
    }
    if (startPosition == 8 && stopPosition == 6) {
      lines[i].startPoint.X--;
      lines[i].endPoint.Y++;
    }
  }

  for (byte i = 4; i <= 6; i++) {
    lines[i].startPoint.X = lines[i - 1].startPoint.X;
    lines[i].startPoint.Y = lines[i - 1].startPoint.Y;
    lines[i].startPoint.Z = lines[i - 1].startPoint.Z;
    lines[i].endPoint.X = lines[i - 1].endPoint.X;
    lines[i].endPoint.Y = lines[i - 1].endPoint.Y;
    lines[i].endPoint.Z = lines[i - 1].endPoint.Z;


    if (startPosition == 1 && stopPosition == 3) {
      lines[i].startPoint.X++;
      lines[i].endPoint.Y++;
    }
    if (startPosition == 1 && stopPosition == 6) {
      lines[i].startPoint.Y++;
      lines[i].endPoint.Z++;
    }    
    if (startPosition == 1 && stopPosition == 8) {
      lines[i].startPoint.X++;
      lines[i].endPoint.Z++;
    }   
    if (startPosition == 2 && stopPosition == 4) {
      lines[i].startPoint.Y--;
      lines[i].endPoint.X++;
    }
    if (startPosition == 2 && stopPosition == 5) {
      lines[i].startPoint.Z++;
      lines[i].endPoint.Y--;
    }
    if (startPosition == 2 && stopPosition == 7) {
      lines[i].startPoint.X++;
      lines[i].endPoint.Z++;
    }
    if (startPosition == 3 && stopPosition == 1) {
      lines[i].startPoint.Y++;
      lines[i].endPoint.X--;
    }
    if (startPosition == 3 && stopPosition == 6) {
      lines[i].startPoint.Z++;
      lines[i].endPoint.X--;
    }
    if (startPosition == 3 && stopPosition == 8) {
      lines[i].startPoint.Y--;
      lines[i].endPoint.Z++;
    }
    if (startPosition == 4 && stopPosition == 2) {
      lines[i].startPoint.Y++;
      lines[i].endPoint.X--;
    }
    if (startPosition == 4 && stopPosition == 5) {
      lines[i].startPoint.Z++;
      lines[i].endPoint.X--;
    }
    if (startPosition == 4 && stopPosition == 7) {
      lines[i].startPoint.Y++;
      lines[i].endPoint.Z++;
    }
    if (startPosition == 5 && stopPosition == 2) {
      lines[i].startPoint.Y++;
      lines[i].endPoint.Z--;
    }
    if (startPosition == 5 && stopPosition == 4) {
      lines[i].startPoint.X++;
      lines[i].endPoint.Z--;
    }
    if (startPosition == 5 && stopPosition == 7) {
      lines[i].startPoint.Y++;
      lines[i].endPoint.X++;
    }
    if (startPosition == 6 && stopPosition == 1) {
      lines[i].startPoint.Y--;
      lines[i].endPoint.Z--;
    }
    if (startPosition == 6 && stopPosition == 3) {
      lines[i].startPoint.X++;
      lines[i].endPoint.Z--;
    }
    if (startPosition == 6 && stopPosition == 8) {
      lines[i].startPoint.X++;
      lines[i].endPoint.Y--;
    }
    if (startPosition == 7 && stopPosition == 2) {
      lines[i].startPoint.Z--;
      lines[i].endPoint.X--;
    }
    if (startPosition == 7 && stopPosition == 4) {
      lines[i].startPoint.Z--;
      lines[i].endPoint.Y--;
    }
    if (startPosition == 7 && stopPosition == 5) {
      lines[i].startPoint.Y--;
      lines[i].endPoint.X--;
    }
    if (startPosition == 8 && stopPosition == 1) {
      lines[i].startPoint.Z--;
      lines[i].endPoint.X--;
    }
    if (startPosition == 8 && stopPosition == 3) {
      lines[i].startPoint.Z--;
      lines[i].endPoint.Y++;
    }
    if (startPosition == 8 && stopPosition == 6) {
      lines[i].startPoint.Y++;
      lines[i].endPoint.X--;
    }
  }

  int count[7];
  int startingCount = 1;
  for (byte i = 0; i <= 6; i++) {
    count[i] = startingCount;
    startingCount--;
  }

  for (byte i = 1; i <= 9; i++) {
    for (byte j = 0; j <= 6; j++) {
      if (count[j] >= 1 && count[j] <= 3) {
        drawLine(lines[j].startPoint, lines[j].endPoint, BLACK, 0);
        if (startPosition >= 5 && stopPosition >= 5) {
          lines[j].startPoint.Z--;
          lines[j].endPoint.Z--;
        }
        if (startPosition <= 4 && stopPosition <= 4) {
          lines[j].startPoint.Z++;
          lines[j].endPoint.Z++;
        }
        if ((startPosition == 1 && stopPosition == 8) ||
            (startPosition == 5 && stopPosition == 4) ||
            (startPosition == 8 && stopPosition == 1) ||
            (startPosition == 4 && stopPosition == 5)) {
          lines[j].startPoint.Y++;
          lines[j].endPoint.Y++;        
            }
        if ((startPosition == 2 && stopPosition == 7) ||
            (startPosition == 6 && stopPosition == 3) ||
            (startPosition == 7 && stopPosition == 2) ||
            (startPosition == 3 && stopPosition == 6)) {
          lines[j].startPoint.Y--;
          lines[j].endPoint.Y--;        
            }
        if ((startPosition == 1 && stopPosition == 6) ||
            (startPosition == 2 && stopPosition == 5) ||
            (startPosition == 5 && stopPosition == 2) ||
            (startPosition == 6 && stopPosition == 1)) {
          lines[j].startPoint.X++;
          lines[j].endPoint.X++;        
            }
        if ((startPosition == 3 && stopPosition == 8) ||
            (startPosition == 4 && stopPosition == 7) ||
            (startPosition == 7 && stopPosition == 4) ||
            (startPosition == 8 && stopPosition == 3)) {
          lines[j].startPoint.X--;
          lines[j].endPoint.X--;        
            }
            drawLine(lines[j].startPoint, lines[j].endPoint, theColour, 0);
      }

      count[j]++;
    }
    delay(theDelay);
  }
}

byte getPosition(byte X, byte Y, byte Z) {
  if (X == 0 && Y == 0 && Z == 0) {
    return 1;
  } else if (X == 0 && Y == 3 && Z == 0) {
    return 2;
  } else if (X == 3 && Y == 3 && Z == 0) {
    return 3;
  } else if (X == 3 && Y == 0 && Z == 0) {
    return 4;
  } else if (X == 0 && Y == 0 && Z == 3) {
    return 5;
  } else if (X == 0 && Y == 3 && Z == 3) {
    return 6;
  } else if (X == 3 && Y == 3 && Z == 3) {
    return 7;
  } else if (X == 3 && Y == 0 && Z == 3) {
    return 8;
  }  
}

