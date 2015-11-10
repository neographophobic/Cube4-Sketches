
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

  // Complete Top Face
  while(1==1) {
  faceDraw(0, 0, 3, 3, 3, 3, theColour, theDelay);
  peel(3, 0, 3, 0, 3, 3, theColour, theDelay);
  faceDraw(0, 0, 0, 3, 3, 0, BLACK, theDelay);
  }  
  // Start Peel
  cube.set(3, 0, 3, BLACK);
  cube.set(3, 0, 2, theColour);
  delay(theDelay);

  cube.set(3, 0, 2, BLACK);
  cube.set(3, 0, 1, theColour);
  cube.line(2, 0, 3, 3, 1, 3, BLACK);
  cube.line(2, 0, 2, 3, 1, 2, theColour);
  delay(theDelay);

  cube.set(3, 0, 1, BLACK);
  cube.set(3, 0, 0, theColour);
  cube.line(2, 0, 2, 3, 1, 2, BLACK);
  cube.line(2, 0, 1, 3, 1, 1, theColour);
  cube.line(1, 0, 3, 3, 2, 3, BLACK);
  cube.line(1, 0, 2, 3, 2, 2, theColour);
  delay(theDelay);

  cube.line(2, 0, 1, 3, 1, 1, BLACK);
  cube.line(2, 0, 0, 3, 1, 0, theColour);
  cube.line(1, 0, 2, 3, 2, 2, BLACK);
  cube.line(1, 0, 1, 3, 2, 1, theColour);
  cube.line(0, 0, 3, 3, 3, 3, BLACK);
  cube.line(0, 0, 2, 3, 3, 2, theColour);
  delay(theDelay);

  cube.line(1, 0, 1, 3, 2, 1, BLACK);
  cube.line(1, 0, 0, 3, 2, 0, theColour);
  cube.line(0, 0, 2, 3, 3, 2, BLACK);
  cube.line(0, 0, 1, 3, 3, 1, theColour);
  cube.line(0, 1, 3, 2, 3, 3, BLACK);
  cube.line(0, 1, 2, 2, 3, 2, theColour);
  delay(theDelay);

  cube.line(0, 0, 1, 3, 3, 1, BLACK);
  cube.line(0, 0, 0, 3, 3, 0, theColour);
  cube.line(0, 1, 2, 2, 3, 2, BLACK);
  cube.line(0, 1, 1, 2, 3, 1, theColour);
  cube.line(0, 2, 3, 1, 3, 3, BLACK);
  cube.line(0, 2, 2, 1, 3, 2, theColour);
  delay(theDelay);

  cube.line(0, 1, 1, 2, 3, 1, BLACK);
  cube.line(0, 1, 0, 2, 3, 0, theColour);
  cube.line(0, 2, 2, 1, 3, 2, BLACK);
  cube.line(0, 2, 1, 1, 3, 1, theColour);
  cube.set(0, 3, 3, BLACK);
  cube.set(0, 3, 2, theColour);
  delay(theDelay);

  cube.line(0, 2, 1, 1, 3, 1, BLACK);
  cube.line(0, 2, 0, 1, 3, 0, theColour);
  cube.set(0, 3, 2, BLACK);
  cube.set(0, 3, 1, theColour);
  delay(theDelay);

  cube.set(0, 3, 1, BLACK);
  cube.set(0, 3, 0, theColour);
  delay(theDelay);

  // Wipe the bottom
  faceDraw(0, 0, 0, 3, 3, 0, BLACK, theDelay);

  delay(1000);
}

void faceDraw(byte x1, byte y1, byte z1, byte x2, byte y2, byte z2, rgb_t theColour, int theDelay)
{
  // 8 Corners to the cube. Determine which ones to use
  byte startPosition;
  byte stopPosition;

  if (x1 == 0 && y1 == 0 && z1 == 0) {
    startPosition = 1;
  } else if (x1 == 0 && y1 == 3 && z1 == 0) {
    startPosition = 2;
  } else if (x1 == 3 && y1 == 3 && z1 == 0) {
    startPosition = 3;
  } else if (x1 == 3 && y1 == 0 && z1 == 0) {
    startPosition = 4;
  } else if (x1 == 0 && y1 == 0 && z1 == 3) {
    startPosition = 5;
  } else if (x1 == 0 && y1 == 3 && z1 == 3) {
    startPosition = 6;
  } else if (x1 == 3 && y1 == 3 && z1 == 3) {
    startPosition = 7;
  } else if (x1 == 3 && y1 == 0 && z1 == 3) {
    startPosition = 8;
  }

  if (x2 == 0 && y2 == 0 && z2 == 0) {
    stopPosition = 1;
  } else if (x2 == 0 && y2 == 3 && z2 == 0) {
    stopPosition = 2;
  } else if (x2 == 3 && y2 == 3 && z2 == 0) {
    stopPosition = 3;
  } else if (x2 == 3 && y2 == 0 && z2 == 0) {
    stopPosition = 4;
  } else if (x2 == 0 && y2 == 0 && z2 == 3) {
    stopPosition = 5;
  } else if (x2 == 0 && y2 == 3 && z2 == 3) {
    stopPosition = 6;
  } else if (x2 == 3 && y2 == 3 && z2 == 3) {
    stopPosition = 7;
  } else if (x2 == 3 && y2 == 0 && z2 == 3) {
    stopPosition = 8;
  }

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
        startPoint.X > endPoint.X && startPoint.Y == endPoint.Y
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
  byte startPosition;
  byte stopPosition;

  if (x1 == 0 && y1 == 0 && z1 == 0) {
    startPosition = 1;
  } else if (x1 == 0 && y1 == 3 && z1 == 0) {
    startPosition = 2;
  } else if (x1 == 3 && y1 == 3 && z1 == 0) {
    startPosition = 3;
  } else if (x1 == 3 && y1 == 0 && z1 == 0) {
    startPosition = 4;
  } else if (x1 == 0 && y1 == 0 && z1 == 3) {
    startPosition = 5;
  } else if (x1 == 0 && y1 == 3 && z1 == 3) {
    startPosition = 6;
  } else if (x1 == 3 && y1 == 3 && z1 == 3) {
    startPosition = 7;
  } else if (x1 == 3 && y1 == 0 && z1 == 3) {
    startPosition = 8;
  }

  if (x2 == 0 && y2 == 0 && z2 == 0) {
    stopPosition = 1;
  } else if (x2 == 0 && y2 == 3 && z2 == 0) {
    stopPosition = 2;
  } else if (x2 == 3 && y2 == 3 && z2 == 0) {
    stopPosition = 3;
  } else if (x2 == 3 && y2 == 0 && z2 == 0) {
    stopPosition = 4;
  } else if (x2 == 0 && y2 == 0 && z2 == 3) {
    stopPosition = 5;
  } else if (x2 == 0 && y2 == 3 && z2 == 3) {
    stopPosition = 6;
  } else if (x2 == 3 && y2 == 3 && z2 == 3) {
    stopPosition = 7;
  } else if (x2 == 3 && y2 == 0 && z2 == 3) {
    stopPosition = 8;
  }

  // Figure out where the lines to move are
  struct aLine line1;  
  struct aLine line2;
  struct aLine line3;
  struct aLine line4;
  struct aLine line5;
  struct aLine line6;
  struct aLine line7;

  if(startPosition == 8 && stopPosition == 6) {
    line1.startPoint.X = x1;
    line1.startPoint.Y = y1;
    line1.startPoint.Z = z1;
    line1.endPoint.X = x1;
    line1.endPoint.Y = y1;
    line1.endPoint.Z = z1;

    line2.startPoint.X = x1 - 1;
    line2.startPoint.Y = y1;
    line2.startPoint.Z = z1;
    line2.endPoint.X = x1;
    line2.endPoint.Y = y1 + 1;
    line2.endPoint.Z = z1;
  
    line3.startPoint.X = x1 - 2;
    line3.startPoint.Y = y1;
    line3.startPoint.Z = z1;
    line3.endPoint.X = x1;
    line3.endPoint.Y = y1 + 2;
    line3.endPoint.Z = z1;

    line4.startPoint.X = x1 - 3;
    line4.startPoint.Y = y1;
    line4.startPoint.Z = z1;
    line4.endPoint.X = x1;
    line4.endPoint.Y = y1 + 3;
    line4.endPoint.Z = z1;

    line5.startPoint.X = x1 - 3;
    line5.startPoint.Y = y1 + 1;
    line5.startPoint.Z = z1;
    line5.endPoint.X = x1 - 1;
    line5.endPoint.Y = y1 + 3;
    line5.endPoint.Z = z1;

    line6.startPoint.X = x1 - 3;
    line6.startPoint.Y = y1 + 2;
    line6.startPoint.Z = z1;
    line6.endPoint.X = x1 - 2;
    line6.endPoint.Y = y1 + 3;
    line6.endPoint.Z = z1;

    line7.startPoint.X = x1 - 3;
    line7.startPoint.Y = y1 + 3;
    line7.startPoint.Z = z1;
    line7.endPoint.X = x1 - 3;
    line7.endPoint.Y = y1 + 3;
    line7.endPoint.Z = z1;
  }

  // Move 1
  // Line 1
  drawLine(line1.startPoint, line1.endPoint, BLACK, 0);
  line1.startPoint.Z--;
  line1.endPoint.Z--;
  drawLine(line1.startPoint, line1.endPoint, theColour, theDelay);
  
  // Move 2
  // Line 1
  drawLine(line1.startPoint, line1.endPoint, BLACK, 0);
  line1.startPoint.Z--;
  line1.endPoint.Z--;
  drawLine(line1.startPoint, line1.endPoint, theColour, 0);
  // Line 2
  drawLine(line2.startPoint, line2.endPoint, BLACK, 0);
  line2.startPoint.Z--;
  line2.endPoint.Z--;
  drawLine(line2.startPoint, line2.endPoint, theColour, theDelay);
  
  // Move 3
  // Line 1
  drawLine(line1.startPoint, line1.endPoint, BLACK, 0);
  line1.startPoint.Z--;
  line1.endPoint.Z--;
  drawLine(line1.startPoint, line1.endPoint, theColour, 0);
  // Line 2
  drawLine(line2.startPoint, line2.endPoint, BLACK, 0);
  line2.startPoint.Z--;
  line2.endPoint.Z--;
  drawLine(line2.startPoint, line2.endPoint, theColour, 0);
  // Line 3
  drawLine(line3.startPoint, line3.endPoint, BLACK, 0);
  line3.startPoint.Z--;
  line3.endPoint.Z--;
  drawLine(line3.startPoint, line3.endPoint, theColour, theDelay);

  // Move 4
  // Line 2
  drawLine(line2.startPoint, line2.endPoint, BLACK, 0);
  line2.startPoint.Z--;
  line2.endPoint.Z--;
  drawLine(line2.startPoint, line2.endPoint, theColour, 0);
  // Line 3
  drawLine(line3.startPoint, line3.endPoint, BLACK, 0);
  line3.startPoint.Z--;
  line3.endPoint.Z--;
  drawLine(line3.startPoint, line3.endPoint, theColour, 0);
  // Line 4
  drawLine(line4.startPoint, line4.endPoint, BLACK, 0);
  line4.startPoint.Z--;
  line4.endPoint.Z--;
  drawLine(line4.startPoint, line4.endPoint, theColour, theDelay);

  // Move 5
  // Line 3
  drawLine(line3.startPoint, line3.endPoint, BLACK, 0);
  line3.startPoint.Z--;
  line3.endPoint.Z--;
  drawLine(line3.startPoint, line3.endPoint, theColour, 0);
  // Line 4
  drawLine(line4.startPoint, line4.endPoint, BLACK, 0);
  line4.startPoint.Z--;
  line4.endPoint.Z--;
  drawLine(line4.startPoint, line4.endPoint, theColour, 0);
  // Line 5
  drawLine(line5.startPoint, line5.endPoint, BLACK, 0);
  line5.startPoint.Z--;
  line5.endPoint.Z--;
  drawLine(line5.startPoint, line5.endPoint, theColour, theDelay);

  // Move 6
  // Line 4
  drawLine(line4.startPoint, line4.endPoint, BLACK, 0);
  line4.startPoint.Z--;
  line4.endPoint.Z--;
  drawLine(line4.startPoint, line4.endPoint, theColour, 0);
  // Line 5
  drawLine(line5.startPoint, line5.endPoint, BLACK, 0);
  line5.startPoint.Z--;
  line5.endPoint.Z--;
  drawLine(line5.startPoint, line5.endPoint, theColour, 0);
  // Line 6
  drawLine(line6.startPoint, line6.endPoint, BLACK, 0);
  line6.startPoint.Z--;
  line6.endPoint.Z--;
  drawLine(line6.startPoint, line6.endPoint, theColour, theDelay);

  // Move 7
  // Line 5
  drawLine(line5.startPoint, line5.endPoint, BLACK, 0);
  line5.startPoint.Z--;
  line5.endPoint.Z--;
  drawLine(line5.startPoint, line5.endPoint, theColour, 0);
  // Line 6
  drawLine(line6.startPoint, line6.endPoint, BLACK, 0);
  line6.startPoint.Z--;
  line6.endPoint.Z--;
  drawLine(line6.startPoint, line6.endPoint, theColour, 0);
  // Line 7
  drawLine(line7.startPoint, line7.endPoint, BLACK, 0);
  line7.startPoint.Z--;
  line7.endPoint.Z--;
  drawLine(line7.startPoint, line7.endPoint, theColour, theDelay);

  // Move 8
  // Line 6
  drawLine(line6.startPoint, line6.endPoint, BLACK, 0);
  line6.startPoint.Z--;
  line6.endPoint.Z--;
  drawLine(line6.startPoint, line6.endPoint, theColour, 0);
  // Line 7
  drawLine(line7.startPoint, line7.endPoint, BLACK, 0);
  line7.startPoint.Z--;
  line7.endPoint.Z--;
  drawLine(line7.startPoint, line7.endPoint, theColour, theDelay);

  // Move 9
  // Line 7
  drawLine(line7.startPoint, line7.endPoint, BLACK, 0);
  line7.startPoint.Z--;
  line7.endPoint.Z--;
  drawLine(line7.startPoint, line7.endPoint, theColour, theDelay);  
}
