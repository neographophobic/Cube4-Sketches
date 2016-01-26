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
  struct coordinate start;
  struct coordinate end;
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
  byte startCorner = getCorner(x1, y1, z1);
  byte stopCorner = getCorner(x2, y2, z2);

  // From each of the 8 corners there are 3 valid directions
  // broken into 2 sections (start -> middle -> end)

  struct coordinate start;
  struct coordinate end;
  start.x = x1;
  start.y = y1;
  start.z = z1;
  end = start;

  // First part of the move
  cube.set(start.x, start.y, start.z, theColour);
  delay(theDelay);

  // Next 3 steps
  for (byte i = 1; i <= 3; i++) {
    if (startCorner == 1 && stopCorner == 3) {
      start.y++;
      end.x++;
    } else if (startCorner == 1 && stopCorner == 6) {
      start.y++;
      end.z++;
    } else if (startCorner == 1 && stopCorner == 8) {
      start.z++;
      end.x++;
    }
    if (startCorner == 2 && stopCorner == 4) {
      start.y--;
      end.x++;
    } else if (startCorner == 2 && stopCorner == 5) {
      start.y--;
      end.z++;
    } else if (startCorner == 2 && stopCorner == 7) {
      start.z++;
      end.x++;
    }
    if (startCorner == 3 && stopCorner == 1) {
      start.x--;
      end.y--;
    } else if (startCorner == 3 && stopCorner == 6) {
      start.x--;
      end.z++;
    } else if (startCorner == 3 && stopCorner == 8) {
      start.y--;
      end.z++;
    }
    if (startCorner == 4 && stopCorner == 2) {
      start.x--;
      end.y++;
    } else if (startCorner == 4 && stopCorner == 5) {
      start.x--;
      end.z++;
    } else if (startCorner == 4 && stopCorner == 7) {
      start.z++;
      end.y++;
    }
    if (startCorner == 5 && stopCorner == 2) {
      start.z--;
      end.y++;
    } else if (startCorner == 5 && stopCorner == 4) {
      start.z--;
      end.x++;
    } else if (startCorner == 5 && stopCorner == 7) {
      start.x++;
      end.y++;
    }
    if (startCorner == 6 && stopCorner == 1) {
      start.y--;
      end.z--;
    } else if (startCorner == 6 && stopCorner == 3) {
      start.x++;
      end.z--;
    } else if (startCorner == 6 && stopCorner == 8) {
      start.y--;
      end.x++;
    }
    if (startCorner == 7 && stopCorner == 2) {
      start.x--;
      end.z--;
    } else if (startCorner == 7 && stopCorner == 4) {
      start.y--;
      end.z--;
    } else if (startCorner == 7 && stopCorner == 5) {
      start.x--;
      end.y--;
    }
    if (startCorner == 8 && stopCorner == 1) {
      start.x--;
      end.z--;
    } else if (startCorner == 8 && stopCorner == 3) {
      start.z--;
      end.y++;
    } else if (startCorner == 8 && stopCorner == 6) {
      start.x--;
      end.y++;
    }

    drawLine(start, end, theColour, theDelay);
  }

  // Final 3 steps
  for (byte i = 1; i <= 3; i++) {
    if (startCorner == 1 && stopCorner == 3) {
      start.x++;
      end.y++;
    } else if (startCorner == 1 && stopCorner == 6) {
      start.z++;
      end.y++;
    } else if (startCorner == 1 && stopCorner == 8) {
      start.x++;
      end.z++;
    }
    if (startCorner == 2 && stopCorner == 4) {
      start.x++;
      end.y--;
    } else if (startCorner == 2 && stopCorner == 5) {
      start.z++;
      end.y--;
    } else if (startCorner == 2 && stopCorner == 7) {
      start.x++;
      end.z++;
    }
    if (startCorner == 3 && stopCorner == 1) {
      start.y--;
      end.x--;
    } else if (startCorner == 3 && stopCorner == 6) {
      start.z++;
      end.x--;
    } else if (startCorner == 3 && stopCorner == 8) {
      start.z++;
      end.y--;
    }
    if (startCorner == 4 && stopCorner == 2) {
      start.y++;
      end.x--;
    } else if (startCorner == 4 && stopCorner == 5) {
      start.z++;
      end.x--;
    } else if (startCorner == 4 && stopCorner == 7) {
      start.y++;
      end.z++;
    }
    if (startCorner == 5 && stopCorner == 2) {
      start.y++;
      end.z--;
    } else if (startCorner == 5 && stopCorner == 4) {
      start.x++;
      end.z--;
    } else if (startCorner == 5 && stopCorner == 7) {
      start.y++;
      end.x++;
    }
    if (startCorner == 6 && stopCorner == 1) {
      start.z--;
      end.y--;
    } else if (startCorner == 6 && stopCorner == 3) {
      start.z--;
      end.x++;
    } else if (startCorner == 6 && stopCorner == 8) {
      start.x++;
      end.y--;
    }
    if (startCorner == 7 && stopCorner == 2) {
      start.z--;
      end.x--;
    } else if (startCorner == 7 && stopCorner == 4) {
      start.z--;
      end.y--;
    } else if (startCorner == 7 && stopCorner == 5) {
      start.y--;
      end.x--;
    }
    if (startCorner == 8 && stopCorner == 1) {
      start.z--;
      end.x--;
    } else if (startCorner == 8 && stopCorner == 3) {
      start.y++;
      end.z--;
    } else if (startCorner == 8 && stopCorner == 6) {
      start.y++;
      end.x--;
    }

    drawLine(start, end, theColour, theDelay);
  }
}

void drawLine(struct coordinate start, struct coordinate end, rgb_t theColour, int theDelay)
{
  if (start.y > end.y && start.z < end.z ||
      start.x > end.x && start.z == end.z ||
      start.x > end.x && start.y == end.y ||
      start.y > end.y && start.x == end.x
     ) {
    // Work around bug in line drawing code by swapping start and
    // end point if particular condiations are meet
    cube.line(end.x, end.y, end.z,
              start.x, start.y, start.z, theColour);
  } else {
    cube.line(start.x, start.y, start.z,
              end.x, end.y, end.z, theColour);
  }
  delay(theDelay);
}

void peel(byte x1, byte y1, byte z1, byte x2, byte y2, byte z2, rgb_t theColour, int theDelay)
{
  // 8 Corners to the cube. Determine which ones to use
  byte startCorner = getCorner(x1, y1, z1);
  byte stopCorner = getCorner(x2, y2, z2);

  aLine lines[7];

  // Figure out where the lines to move are
  lines[0].start.x = x1;
  lines[0].start.y = y1;
  lines[0].start.z = z1;
  lines[0].end = lines[0].start;

  for (byte i = 1; i <= 3; i++) {
    lines[i].start.x = lines[i - 1].start.x;
    lines[i].start.y = lines[i - 1].start.y;
    lines[i].start.z = lines[i - 1].start.z;
    lines[i].end.x = lines[i - 1].end.x;
    lines[i].end.y = lines[i - 1].end.y;
    lines[i].end.z = lines[i - 1].end.z;

    if (startCorner == 1 && stopCorner == 3) {
      lines[i].start.y++;
      lines[i].end.x++;
    }
    if (startCorner == 1 && stopCorner == 6) {
      lines[i].start.z++;
      lines[i].end.y++;
    }
    if (startCorner == 1 && stopCorner == 8) {
      lines[i].start.z++;
      lines[i].end.x++;
    }
    if (startCorner == 2 && stopCorner == 4) {
      lines[i].start.x++;
      lines[i].end.y--;
    }
    if (startCorner == 2 && stopCorner == 5) {
      lines[i].start.y--;
      lines[i].end.z++;
    }
    if (startCorner == 2 && stopCorner == 7) {
      lines[i].start.z++;
      lines[i].end.x++;
    }
    if (startCorner == 3 && stopCorner == 1) {
      lines[i].start.x--;
      lines[i].end.y--;
    }
    if (startCorner == 3 && stopCorner == 6) {
      lines[i].start.x--;
      lines[i].end.z++;
    }
    if (startCorner == 3 && stopCorner == 8) {
      lines[i].start.z++;
      lines[i].end.y--;
    }
    if (startCorner == 4 && stopCorner == 2) {
      lines[i].start.x--;
      lines[i].end.y++;
    }
    if (startCorner == 4 && stopCorner == 5) {
      lines[i].start.x--;
      lines[i].end.z++;
    }
    if (startCorner == 4 && stopCorner == 7) {
      lines[i].start.z++;
      lines[i].end.y++;
    }
    if (startCorner == 5 && stopCorner == 2) {
      lines[i].start.z--;
      lines[i].end.y++;
    }
    if (startCorner == 5 && stopCorner == 4) {
      lines[i].start.z--;
      lines[i].end.x++;
    }
    if (startCorner == 5 && stopCorner == 7) {
      lines[i].start.x++;
      lines[i].end.y++;
    }
    if (startCorner == 6 && stopCorner == 1) {
      lines[i].start.z--;
      lines[i].end.y--;
    }
    if (startCorner == 6 && stopCorner == 3) {
      lines[i].start.z--;
      lines[i].end.x++;
    }
    if (startCorner == 6 && stopCorner == 8) {
      lines[i].start.y--;
      lines[i].end.x++;
    }
    if (startCorner == 7 && stopCorner == 2) {
      lines[i].start.x--;
      lines[i].end.z--;
    }
    if (startCorner == 7 && stopCorner == 4) {
      lines[i].start.y--;
      lines[i].end.z--;
    }
    if (startCorner == 7 && stopCorner == 5) {
      lines[i].start.x--;
      lines[i].end.y--;
    }
    if (startCorner == 8 && stopCorner == 1) {
      lines[i].start.x--;
      lines[i].end.z--;
    }
    if (startCorner == 8 && stopCorner == 3) {
      lines[i].start.y++;
      lines[i].end.z--;
    }
    if (startCorner == 8 && stopCorner == 6) {
      lines[i].start.x--;
      lines[i].end.y++;
    }
  }

  for (byte i = 4; i <= 6; i++) {
    lines[i].start.x = lines[i - 1].start.x;
    lines[i].start.y = lines[i - 1].start.y;
    lines[i].start.z = lines[i - 1].start.z;
    lines[i].end.x = lines[i - 1].end.x;
    lines[i].end.y = lines[i - 1].end.y;
    lines[i].end.z = lines[i - 1].end.z;


    if (startCorner == 1 && stopCorner == 3) {
      lines[i].start.x++;
      lines[i].end.y++;
    }
    if (startCorner == 1 && stopCorner == 6) {
      lines[i].start.y++;
      lines[i].end.z++;
    }
    if (startCorner == 1 && stopCorner == 8) {
      lines[i].start.x++;
      lines[i].end.z++;
    }
    if (startCorner == 2 && stopCorner == 4) {
      lines[i].start.y--;
      lines[i].end.x++;
    }
    if (startCorner == 2 && stopCorner == 5) {
      lines[i].start.z++;
      lines[i].end.y--;
    }
    if (startCorner == 2 && stopCorner == 7) {
      lines[i].start.x++;
      lines[i].end.z++;
    }
    if (startCorner == 3 && stopCorner == 1) {
      lines[i].start.y++;
      lines[i].end.x--;
    }
    if (startCorner == 3 && stopCorner == 6) {
      lines[i].start.z++;
      lines[i].end.x--;
    }
    if (startCorner == 3 && stopCorner == 8) {
      lines[i].start.y--;
      lines[i].end.z++;
    }
    if (startCorner == 4 && stopCorner == 2) {
      lines[i].start.y++;
      lines[i].end.x--;
    }
    if (startCorner == 4 && stopCorner == 5) {
      lines[i].start.z++;
      lines[i].end.x--;
    }
    if (startCorner == 4 && stopCorner == 7) {
      lines[i].start.y++;
      lines[i].end.z++;
    }
    if (startCorner == 5 && stopCorner == 2) {
      lines[i].start.y++;
      lines[i].end.z--;
    }
    if (startCorner == 5 && stopCorner == 4) {
      lines[i].start.x++;
      lines[i].end.z--;
    }
    if (startCorner == 5 && stopCorner == 7) {
      lines[i].start.y++;
      lines[i].end.x++;
    }
    if (startCorner == 6 && stopCorner == 1) {
      lines[i].start.y--;
      lines[i].end.z--;
    }
    if (startCorner == 6 && stopCorner == 3) {
      lines[i].start.x++;
      lines[i].end.z--;
    }
    if (startCorner == 6 && stopCorner == 8) {
      lines[i].start.x++;
      lines[i].end.y--;
    }
    if (startCorner == 7 && stopCorner == 2) {
      lines[i].start.z--;
      lines[i].end.x--;
    }
    if (startCorner == 7 && stopCorner == 4) {
      lines[i].start.z--;
      lines[i].end.y--;
    }
    if (startCorner == 7 && stopCorner == 5) {
      lines[i].start.y--;
      lines[i].end.x--;
    }
    if (startCorner == 8 && stopCorner == 1) {
      lines[i].start.z--;
      lines[i].end.x--;
    }
    if (startCorner == 8 && stopCorner == 3) {
      lines[i].start.z--;
      lines[i].end.y++;
    }
    if (startCorner == 8 && stopCorner == 6) {
      lines[i].start.y++;
      lines[i].end.x--;
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
        drawLine(lines[j].start, lines[j].end, BLACK, 0);
        if (startCorner >= 5 && stopCorner >= 5) {
          lines[j].start.z--;
          lines[j].end.z--;
        }
        if (startCorner <= 4 && stopCorner <= 4) {
          lines[j].start.z++;
          lines[j].end.z++;
        }
        if ((startCorner == 1 && stopCorner == 8) ||
            (startCorner == 5 && stopCorner == 4) ||
            (startCorner == 8 && stopCorner == 1) ||
            (startCorner == 4 && stopCorner == 5)) {
          lines[j].start.y++;
          lines[j].end.y++;
        }
        if ((startCorner == 2 && stopCorner == 7) ||
            (startCorner == 6 && stopCorner == 3) ||
            (startCorner == 7 && stopCorner == 2) ||
            (startCorner == 3 && stopCorner == 6)) {
          lines[j].start.y--;
          lines[j].end.y--;
        }
        if ((startCorner == 1 && stopCorner == 6) ||
            (startCorner == 2 && stopCorner == 5) ||
            (startCorner == 5 && stopCorner == 2) ||
            (startCorner == 6 && stopCorner == 1)) {
          lines[j].start.x++;
          lines[j].end.x++;
        }
        if ((startCorner == 3 && stopCorner == 8) ||
            (startCorner == 4 && stopCorner == 7) ||
            (startCorner == 7 && stopCorner == 4) ||
            (startCorner == 8 && stopCorner == 3)) {
          lines[j].start.x--;
          lines[j].end.x--;
        }
        drawLine(lines[j].start, lines[j].end, theColour, 0);
      }

      count[j]++;
    }
    delay(theDelay);
  }
}

