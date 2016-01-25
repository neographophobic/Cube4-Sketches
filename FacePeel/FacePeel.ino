/*
   File:      FacePeel.ino
   Purpose:   FacePeel pattern for the Freetronics 4x4x4 Cube
   Author:    Adam Reed (adam@secretcode.ninja)
   Licence:   BSD 3-Clause Licence
*/

// Include required libraries
#include <SPI.h>
#include "Cube.h"
#include "Cube4_ARUtils.h"

/*
   User editable variables
*/


/*
   Don't edit these variables
*/
// Create an instance of the cube class
Cube cube;

struct aLine
{
  struct coordinate startPoint;
  struct coordinate endPoint;
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

  //  test();
}

void loop(void) {
  rgb_t theColour = BLUE;
  int theDelay = 100;

  faceDraw(0, 0, 3, 3, 3, 3, theColour, theDelay);
  peel(3, 0, 3, 0, 3, 3, theColour, theDelay);
  faceDraw(0, 0, 0, 3, 3, 0, BLACK, theDelay);

  faceDraw(3, 0, 0, 0, 0, 3, theColour, theDelay);
  peel(3, 0, 3, 0, 0, 0, theColour, theDelay);
  faceDraw(3, 3, 0, 0, 3, 3, BLACK, theDelay);

  faceDraw(3, 3, 3, 3, 0, 0, theColour, theDelay);
  peel(3, 0, 3, 3, 3, 0, theColour, theDelay);
  faceDraw(0, 3, 3, 0, 0, 0, BLACK, theDelay);
}

void test(void) {
  rgb_t theColour = BLUE;
  int theDelay = 100;

  // 1 -> 3
  faceDraw(0, 0, 0, 3, 3, 0, theColour, theDelay);
  peel(0, 0, 0, 3, 3, 0, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 1 -> 6
  faceDraw(0, 0, 0, 0, 3, 3, theColour, theDelay);
  peel(0, 0, 0, 0, 3, 3, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 1 -> 8
  faceDraw(0, 0, 0, 3, 0, 3, theColour, theDelay);
  peel(0, 0, 0, 3, 0, 3, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 2 -> 4
  faceDraw(0, 3, 0, 3, 0, 0, theColour, theDelay);
  peel(0, 3, 0, 3, 0, 0, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 2 -> 5
  faceDraw(0, 3, 0, 0, 0, 3, theColour, theDelay);
  peel(0, 3, 0, 0, 0, 3, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 2 -> 7
  faceDraw(0, 3, 0, 3, 3, 3, theColour, theDelay);
  peel(0, 3, 0, 3, 3, 3, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 3 -> 1
  faceDraw(3, 3, 0, 0, 0, 0, theColour, theDelay);
  peel(3, 3, 0, 0, 0, 0, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 3 -> 6
  faceDraw(3, 3, 0, 0, 3, 3, theColour, theDelay);
  peel(3, 3, 0, 0, 3, 3, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 3 -> 8
  faceDraw(3, 3, 0, 3, 0, 3, theColour, theDelay);
  peel(3, 3, 0, 3, 0, 3, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 4 -> 2
  faceDraw(3, 0, 0, 0, 3, 0, theColour, theDelay);
  peel(3, 0, 0, 0, 3, 0, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 4 -> 5
  faceDraw(3, 0, 0, 0, 0, 3, theColour, theDelay);
  peel(3, 0, 0, 0, 0, 3, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 4 -> 7
  faceDraw(3, 0, 0, 3, 3, 3, theColour, theDelay);
  peel(3, 0, 0, 3, 3, 3, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 5 -> 2
  faceDraw(0, 0, 3, 0, 3, 0, theColour, theDelay);
  peel(0, 0, 3, 0, 3, 0, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 5 -> 4
  faceDraw(0, 0, 3, 3, 0, 0, theColour, theDelay);
  peel(0, 0, 3, 3, 0, 0, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 5 -> 7
  faceDraw(0, 0, 3, 3, 3, 3, theColour, theDelay);
  peel(0, 0, 3, 3, 3, 3, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 6 -> 1
  faceDraw(0, 3, 3, 0, 0, 0, theColour, theDelay);
  peel(0, 3, 3, 0, 0, 0, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 6 -> 3
  faceDraw(0, 3, 3, 3, 3, 0, theColour, theDelay);
  peel(0, 3, 3, 3, 3, 0, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 6 -> 8
  faceDraw(0, 3, 3, 3, 0, 3, theColour, theDelay);
  peel(0, 3, 3, 3, 0, 3, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 7 -> 2
  faceDraw(3, 3, 3, 0, 3, 0, theColour, theDelay);
  peel(3, 3, 3, 0, 3, 0, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 7 -> 4
  faceDraw(3, 3, 3, 3, 0, 0, theColour, theDelay);
  peel(3, 3, 3, 3, 0, 0, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 7 -> 5
  faceDraw(3, 3, 3, 0, 0, 3, theColour, theDelay);
  peel(3, 3, 3, 0, 0, 3, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 8 -> 1
  faceDraw(3, 0, 3, 0, 0, 0, theColour, theDelay);
  peel(3, 0, 3, 0, 0, 0, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 8 -> 3
  faceDraw(3, 0, 3, 3, 3, 0, theColour, theDelay);
  peel(3, 0, 3, 3, 3, 0, theColour, theDelay);
  cube.all(BLACK);
  delay(theDelay);

  // 8 -> 6
  faceDraw(3, 0, 3, 0, 3, 3, theColour, theDelay);
  peel(3, 0, 3, 0, 3, 3, theColour, theDelay);
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

  struct coordinate startPoint;
  struct coordinate endPoint;

  startPoint.x = x1;
  startPoint.y = y1;
  startPoint.z = z1;

  endPoint.x = x1;
  endPoint.y = y1;
  endPoint.z = z1;

  // First part of the move
  cube.set(startPoint.x, startPoint.y, startPoint.z, theColour);
  delay(theDelay);

  // Next 3 steps
  for (byte i = 1; i <= 3; i++) {
    if (startPosition == 1 && stopPosition == 3) {
      startPoint.y++;
      endPoint.x++;
    } else if (startPosition == 1 && stopPosition == 6) {
      startPoint.y++;
      endPoint.z++;
    } else if (startPosition == 1 && stopPosition == 8) {
      startPoint.z++;
      endPoint.x++;
    }
    if (startPosition == 2 && stopPosition == 4) {
      startPoint.y--;
      endPoint.x++;
    } else if (startPosition == 2 && stopPosition == 5) {
      startPoint.y--;
      endPoint.z++;
    } else if (startPosition == 2 && stopPosition == 7) {
      startPoint.z++;
      endPoint.x++;
    }
    if (startPosition == 3 && stopPosition == 1) {
      startPoint.x--;
      endPoint.y--;
    } else if (startPosition == 3 && stopPosition == 6) {
      startPoint.x--;
      endPoint.z++;
    } else if (startPosition == 3 && stopPosition == 8) {
      startPoint.y--;
      endPoint.z++;
    }
    if (startPosition == 4 && stopPosition == 2) {
      startPoint.x--;
      endPoint.y++;
    } else if (startPosition == 4 && stopPosition == 5) {
      startPoint.x--;
      endPoint.z++;
    } else if (startPosition == 4 && stopPosition == 7) {
      startPoint.z++;
      endPoint.y++;
    }
    if (startPosition == 5 && stopPosition == 2) {
      startPoint.z--;
      endPoint.y++;
    } else if (startPosition == 5 && stopPosition == 4) {
      startPoint.z--;
      endPoint.x++;
    } else if (startPosition == 5 && stopPosition == 7) {
      startPoint.x++;
      endPoint.y++;
    }
    if (startPosition == 6 && stopPosition == 1) {
      startPoint.y--;
      endPoint.z--;
    } else if (startPosition == 6 && stopPosition == 3) {
      startPoint.x++;
      endPoint.z--;
    } else if (startPosition == 6 && stopPosition == 8) {
      startPoint.y--;
      endPoint.x++;
    }
    if (startPosition == 7 && stopPosition == 2) {
      startPoint.x--;
      endPoint.z--;
    } else if (startPosition == 7 && stopPosition == 4) {
      startPoint.y--;
      endPoint.z--;
    } else if (startPosition == 7 && stopPosition == 5) {
      startPoint.x--;
      endPoint.y--;
    }
    if (startPosition == 8 && stopPosition == 1) {
      startPoint.x--;
      endPoint.z--;
    } else if (startPosition == 8 && stopPosition == 3) {
      startPoint.z--;
      endPoint.y++;
    } else if (startPosition == 8 && stopPosition == 6) {
      startPoint.x--;
      endPoint.y++;
    }

    drawLine(startPoint, endPoint, theColour, theDelay);
  }

  // Final 3 steps
  for (byte i = 1; i <= 3; i++) {
    if (startPosition == 1 && stopPosition == 3) {
      startPoint.x++;
      endPoint.y++;
    } else if (startPosition == 1 && stopPosition == 6) {
      startPoint.z++;
      endPoint.y++;
    } else if (startPosition == 1 && stopPosition == 8) {
      startPoint.x++;
      endPoint.z++;
    }
    if (startPosition == 2 && stopPosition == 4) {
      startPoint.x++;
      endPoint.y--;
    } else if (startPosition == 2 && stopPosition == 5) {
      startPoint.z++;
      endPoint.y--;
    } else if (startPosition == 2 && stopPosition == 7) {
      startPoint.x++;
      endPoint.z++;
    }
    if (startPosition == 3 && stopPosition == 1) {
      startPoint.y--;
      endPoint.x--;
    } else if (startPosition == 3 && stopPosition == 6) {
      startPoint.z++;
      endPoint.x--;
    } else if (startPosition == 3 && stopPosition == 8) {
      startPoint.z++;
      endPoint.y--;
    }
    if (startPosition == 4 && stopPosition == 2) {
      startPoint.y++;
      endPoint.x--;
    } else if (startPosition == 4 && stopPosition == 5) {
      startPoint.z++;
      endPoint.x--;
    } else if (startPosition == 4 && stopPosition == 7) {
      startPoint.y++;
      endPoint.z++;
    }
    if (startPosition == 5 && stopPosition == 2) {
      startPoint.y++;
      endPoint.z--;
    } else if (startPosition == 5 && stopPosition == 4) {
      startPoint.x++;
      endPoint.z--;
    } else if (startPosition == 5 && stopPosition == 7) {
      startPoint.y++;
      endPoint.x++;
    }
    if (startPosition == 6 && stopPosition == 1) {
      startPoint.z--;
      endPoint.y--;
    } else if (startPosition == 6 && stopPosition == 3) {
      startPoint.z--;
      endPoint.x++;
    } else if (startPosition == 6 && stopPosition == 8) {
      startPoint.x++;
      endPoint.y--;
    }
    if (startPosition == 7 && stopPosition == 2) {
      startPoint.z--;
      endPoint.x--;
    } else if (startPosition == 7 && stopPosition == 4) {
      startPoint.z--;
      endPoint.y--;
    } else if (startPosition == 7 && stopPosition == 5) {
      startPoint.y--;
      endPoint.x--;
    }
    if (startPosition == 8 && stopPosition == 1) {
      startPoint.z--;
      endPoint.x--;
    } else if (startPosition == 8 && stopPosition == 3) {
      startPoint.y++;
      endPoint.z--;
    } else if (startPosition == 8 && stopPosition == 6) {
      startPoint.y++;
      endPoint.x--;
    }

    drawLine(startPoint, endPoint, theColour, theDelay);
  }
}

void drawLine(struct coordinate startPoint, struct coordinate endPoint, rgb_t theColour, int theDelay)
{
  if (startPoint.y > endPoint.y && startPoint.z < endPoint.z ||
      startPoint.x > endPoint.x && startPoint.z == endPoint.z ||
      startPoint.x > endPoint.x && startPoint.y == endPoint.y ||
      startPoint.y > endPoint.y && startPoint.x == endPoint.x
     ) {
    // Work around bug in line drawing code by swapping start and
    // end point if particular condiations are meet
    cube.line(endPoint.x, endPoint.y, endPoint.z,
              startPoint.x, startPoint.y, startPoint.z, theColour);
  } else {
    cube.line(startPoint.x, startPoint.y, startPoint.z,
              endPoint.x, endPoint.y, endPoint.z, theColour);
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
  lines[0].startPoint.x = x1;
  lines[0].startPoint.y = y1;
  lines[0].startPoint.z = z1;
  lines[0].endPoint.x = x1;
  lines[0].endPoint.y = y1;
  lines[0].endPoint.z = z1;

  for (byte i = 1; i <= 3; i++) {
    lines[i].startPoint.x = lines[i - 1].startPoint.x;
    lines[i].startPoint.y = lines[i - 1].startPoint.y;
    lines[i].startPoint.z = lines[i - 1].startPoint.z;
    lines[i].endPoint.x = lines[i - 1].endPoint.x;
    lines[i].endPoint.y = lines[i - 1].endPoint.y;
    lines[i].endPoint.z = lines[i - 1].endPoint.z;

    if (startPosition == 1 && stopPosition == 3) {
      lines[i].startPoint.y++;
      lines[i].endPoint.x++;
    }
    if (startPosition == 1 && stopPosition == 6) {
      lines[i].startPoint.z++;
      lines[i].endPoint.y++;
    }
    if (startPosition == 1 && stopPosition == 8) {
      lines[i].startPoint.z++;
      lines[i].endPoint.x++;
    }
    if (startPosition == 2 && stopPosition == 4) {
      lines[i].startPoint.x++;
      lines[i].endPoint.y--;
    }
    if (startPosition == 2 && stopPosition == 5) {
      lines[i].startPoint.y--;
      lines[i].endPoint.z++;
    }
    if (startPosition == 2 && stopPosition == 7) {
      lines[i].startPoint.z++;
      lines[i].endPoint.x++;
    }
    if (startPosition == 3 && stopPosition == 1) {
      lines[i].startPoint.x--;
      lines[i].endPoint.y--;
    }
    if (startPosition == 3 && stopPosition == 6) {
      lines[i].startPoint.x--;
      lines[i].endPoint.z++;
    }
    if (startPosition == 3 && stopPosition == 8) {
      lines[i].startPoint.z++;
      lines[i].endPoint.y--;
    }
    if (startPosition == 4 && stopPosition == 2) {
      lines[i].startPoint.x--;
      lines[i].endPoint.y++;
    }
    if (startPosition == 4 && stopPosition == 5) {
      lines[i].startPoint.x--;
      lines[i].endPoint.z++;
    }
    if (startPosition == 4 && stopPosition == 7) {
      lines[i].startPoint.z++;
      lines[i].endPoint.y++;
    }
    if (startPosition == 5 && stopPosition == 2) {
      lines[i].startPoint.z--;
      lines[i].endPoint.y++;
    }
    if (startPosition == 5 && stopPosition == 4) {
      lines[i].startPoint.z--;
      lines[i].endPoint.x++;
    }
    if (startPosition == 5 && stopPosition == 7) {
      lines[i].startPoint.x++;
      lines[i].endPoint.y++;
    }
    if (startPosition == 6 && stopPosition == 1) {
      lines[i].startPoint.z--;
      lines[i].endPoint.y--;
    }
    if (startPosition == 6 && stopPosition == 3) {
      lines[i].startPoint.z--;
      lines[i].endPoint.x++;
    }
    if (startPosition == 6 && stopPosition == 8) {
      lines[i].startPoint.y--;
      lines[i].endPoint.x++;
    }
    if (startPosition == 7 && stopPosition == 2) {
      lines[i].startPoint.x--;
      lines[i].endPoint.z--;
    }
    if (startPosition == 7 && stopPosition == 4) {
      lines[i].startPoint.y--;
      lines[i].endPoint.z--;
    }
    if (startPosition == 7 && stopPosition == 5) {
      lines[i].startPoint.x--;
      lines[i].endPoint.y--;
    }
    if (startPosition == 8 && stopPosition == 1) {
      lines[i].startPoint.x--;
      lines[i].endPoint.z--;
    }
    if (startPosition == 8 && stopPosition == 3) {
      lines[i].startPoint.y++;
      lines[i].endPoint.z--;
    }
    if (startPosition == 8 && stopPosition == 6) {
      lines[i].startPoint.x--;
      lines[i].endPoint.y++;
    }
  }

  for (byte i = 4; i <= 6; i++) {
    lines[i].startPoint.x = lines[i - 1].startPoint.x;
    lines[i].startPoint.y = lines[i - 1].startPoint.y;
    lines[i].startPoint.z = lines[i - 1].startPoint.z;
    lines[i].endPoint.x = lines[i - 1].endPoint.x;
    lines[i].endPoint.y = lines[i - 1].endPoint.y;
    lines[i].endPoint.z = lines[i - 1].endPoint.z;


    if (startPosition == 1 && stopPosition == 3) {
      lines[i].startPoint.x++;
      lines[i].endPoint.y++;
    }
    if (startPosition == 1 && stopPosition == 6) {
      lines[i].startPoint.y++;
      lines[i].endPoint.z++;
    }
    if (startPosition == 1 && stopPosition == 8) {
      lines[i].startPoint.x++;
      lines[i].endPoint.z++;
    }
    if (startPosition == 2 && stopPosition == 4) {
      lines[i].startPoint.y--;
      lines[i].endPoint.x++;
    }
    if (startPosition == 2 && stopPosition == 5) {
      lines[i].startPoint.z++;
      lines[i].endPoint.y--;
    }
    if (startPosition == 2 && stopPosition == 7) {
      lines[i].startPoint.x++;
      lines[i].endPoint.z++;
    }
    if (startPosition == 3 && stopPosition == 1) {
      lines[i].startPoint.y++;
      lines[i].endPoint.x--;
    }
    if (startPosition == 3 && stopPosition == 6) {
      lines[i].startPoint.z++;
      lines[i].endPoint.x--;
    }
    if (startPosition == 3 && stopPosition == 8) {
      lines[i].startPoint.y--;
      lines[i].endPoint.z++;
    }
    if (startPosition == 4 && stopPosition == 2) {
      lines[i].startPoint.y++;
      lines[i].endPoint.x--;
    }
    if (startPosition == 4 && stopPosition == 5) {
      lines[i].startPoint.z++;
      lines[i].endPoint.x--;
    }
    if (startPosition == 4 && stopPosition == 7) {
      lines[i].startPoint.y++;
      lines[i].endPoint.z++;
    }
    if (startPosition == 5 && stopPosition == 2) {
      lines[i].startPoint.y++;
      lines[i].endPoint.z--;
    }
    if (startPosition == 5 && stopPosition == 4) {
      lines[i].startPoint.x++;
      lines[i].endPoint.z--;
    }
    if (startPosition == 5 && stopPosition == 7) {
      lines[i].startPoint.y++;
      lines[i].endPoint.x++;
    }
    if (startPosition == 6 && stopPosition == 1) {
      lines[i].startPoint.y--;
      lines[i].endPoint.z--;
    }
    if (startPosition == 6 && stopPosition == 3) {
      lines[i].startPoint.x++;
      lines[i].endPoint.z--;
    }
    if (startPosition == 6 && stopPosition == 8) {
      lines[i].startPoint.x++;
      lines[i].endPoint.y--;
    }
    if (startPosition == 7 && stopPosition == 2) {
      lines[i].startPoint.z--;
      lines[i].endPoint.x--;
    }
    if (startPosition == 7 && stopPosition == 4) {
      lines[i].startPoint.z--;
      lines[i].endPoint.y--;
    }
    if (startPosition == 7 && stopPosition == 5) {
      lines[i].startPoint.y--;
      lines[i].endPoint.x--;
    }
    if (startPosition == 8 && stopPosition == 1) {
      lines[i].startPoint.z--;
      lines[i].endPoint.x--;
    }
    if (startPosition == 8 && stopPosition == 3) {
      lines[i].startPoint.z--;
      lines[i].endPoint.y++;
    }
    if (startPosition == 8 && stopPosition == 6) {
      lines[i].startPoint.y++;
      lines[i].endPoint.x--;
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
          lines[j].startPoint.z--;
          lines[j].endPoint.z--;
        }
        if (startPosition <= 4 && stopPosition <= 4) {
          lines[j].startPoint.z++;
          lines[j].endPoint.z++;
        }
        if ((startPosition == 1 && stopPosition == 8) ||
            (startPosition == 5 && stopPosition == 4) ||
            (startPosition == 8 && stopPosition == 1) ||
            (startPosition == 4 && stopPosition == 5)) {
          lines[j].startPoint.y++;
          lines[j].endPoint.y++;
        }
        if ((startPosition == 2 && stopPosition == 7) ||
            (startPosition == 6 && stopPosition == 3) ||
            (startPosition == 7 && stopPosition == 2) ||
            (startPosition == 3 && stopPosition == 6)) {
          lines[j].startPoint.y--;
          lines[j].endPoint.y--;
        }
        if ((startPosition == 1 && stopPosition == 6) ||
            (startPosition == 2 && stopPosition == 5) ||
            (startPosition == 5 && stopPosition == 2) ||
            (startPosition == 6 && stopPosition == 1)) {
          lines[j].startPoint.x++;
          lines[j].endPoint.x++;
        }
        if ((startPosition == 3 && stopPosition == 8) ||
            (startPosition == 4 && stopPosition == 7) ||
            (startPosition == 7 && stopPosition == 4) ||
            (startPosition == 8 && stopPosition == 3)) {
          lines[j].startPoint.x--;
          lines[j].endPoint.x--;
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

