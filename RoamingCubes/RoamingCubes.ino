/*
 * File:    RoamingCubes.ino
 * Version: 1.0
 * Author:  Adam Reed (adam@secretcode.ninja)
 * License: BSD 3-Clause Licence
 * 
 * Inspired by Trilobyte Projects "4x4x4 Led cube demo"
 * at https://www.youtube.com/watch?v=adXXSitxPdo&t=18
 */

#include "SPI.h"
#include "Cube.h"

Cube cube;

rgb_t colours[3] = {RED, GREEN, BLUE};
int theDelay = 100;

int leftPlane   = 0;
int rightPlane  = 0;
int topPlane    = 0;
int bottomPlane = 0;
int frontPlane  = 0;
int backPlane   = 0;

int rLoc = 0;
int gLoc = 0;
int bLoc = 0;

int count = 1;

void setup(void) {
  // Serial port options for control of the Cube using serial commands are:
  // 0: Control via the USB connector (most common).
  // 1: Control via the RXD and TXD pins on the main board.
  // -1: Don't attach any serial port to interact with the Cube.
  cube.begin(0, 115200); // Start on serial port 0 (USB) at 115200 baud
  while(!Serial) {
  }
  randomSeed(1);

  // Create the small cubes, and flag where they are
  cube.box(0, 2, 0, 1, 3, 1, RED);
  leftPlane++;
  bottomPlane++;
  backPlane++;
  rLoc = 1;

  cube.box(0, 0, 2, 1, 1, 3, GREEN);
  leftPlane++;
  topPlane++;
  frontPlane++;
  gLoc = 7;

  cube.box(2, 0, 0, 3, 1, 1, BLUE);
  rightPlane++;
  bottomPlane++;
  frontPlane++;
  bLoc = 4;

  // Initial delay before random movement loop
  delay(theDelay);
}

/**
 */
void loop(void) {
  smallCubesInMotion();
}

void smallCubesInMotion()
{
  // Declare tracking variables
  int i = 0;
  int validMoves[3];

  // Constantly loop through each of the colours,
  // and move the matching cube
  while (i < 3)
  {

    // Determine which cube to move, and where it is
    int cubeToMove = 0;
    switch (i)
    {
      case 0: // Red
        cubeToMove = rLoc;
        break;
      case 1: // Green
        cubeToMove = gLoc;
        break;
      case 2: // Blue
        cubeToMove = bLoc;
        break;
    }

    //
    switch (cubeToMove)
    {
      case 1:
        // Define valid moves from this location
        validMoves[0] = 2;
        validMoves[1] = 3;
        validMoves[2] = 5;
        moveBox(cubeToMove, validMoves, colours[i], i);
        break;
      case 2:
        validMoves[0] = 1;
        validMoves[1] = 4;
        validMoves[2] = 6;
        moveBox(cubeToMove, validMoves, colours[i], i);
        break;
      case 3:
        validMoves[0] = 1;
        validMoves[1] = 4;
        validMoves[2] = 7;
        moveBox(cubeToMove, validMoves, colours[i], i);
        break;
      case 4:
        validMoves[0] = 2;
        validMoves[1] = 3;
        validMoves[2] = 8;
        moveBox(cubeToMove, validMoves, colours[i], i);
        break;
      case 5:
        validMoves[0] = 1;
        validMoves[1] = 6;
        validMoves[2] = 7;
        moveBox(cubeToMove, validMoves, colours[i], i);
        break;
      case 6:
        validMoves[0] = 2;
        validMoves[1] = 5;
        validMoves[2] = 8;
        moveBox(cubeToMove, validMoves, colours[i], i);
        break;
      case 7:
        validMoves[0] = 3;
        validMoves[1] = 5;
        validMoves[2] = 8;
        moveBox(cubeToMove, validMoves, colours[i], i);
        break;
      case 8:
        validMoves[0] = 4;
        validMoves[1] = 6;
        validMoves[2] = 7;
        moveBox(cubeToMove, validMoves, colours[i], i);
        break;
    }

    i++;
    if (i == 3) {
      i = 0;
    }
  }
}

void moveBox(int location, int moves[], rgb_t theColour, int box)
{
  // replaced moves[randomIndex] with destination
  int randomIndex;
  // Pick the location to move to, ensuring it's a valid move
  serial->print("Move: ");
  serial->print(count);
  serial->print(" Box: ");
  serial->println(box);

  int loopKiller = 0;
  do
  {
    randomIndex = random(0, 3);
    loopKiller++;
    if(loopKiller > 100) {
      serial->println("Endless Loop - Killing...");
      while(true) {
        
      }
    }
    
  } while (isThisAValidMove(location, moves[randomIndex], box) == false);

  // Move to the new location
  switch (location)
  {
    case 1:
      switch (moves[randomIndex])
      {
        case 2:
          b1b2(theColour);
          break;
        case 3:
          b1b3(theColour);
          break;
        case 5:
          b1t1(theColour);
          break;
      }
      break;
    case 2:
      switch (moves[randomIndex])
      {
        case 1:
          b2b1(theColour);
          break;
        case 4:
          b2b4(theColour);
          break;
        case 6:
          b2t2(theColour);
          break;
      }
      break;
    case 3:
      switch (moves[randomIndex])
      {
        case 1:
          b3b1(theColour);
          break;
        case 4:
          b3b4(theColour);
          break;
        case 7:
          b3t3(theColour);
          break;
      }
      break;
    case 4:
      switch (moves[randomIndex])
      {
        case 2:
          b4b2(theColour);
          break;
        case 3:
          b4b3(theColour);
          break;
        case 8:
          b4t4(theColour);
          break;
      }
      break;
    case 5:
      switch (moves[randomIndex])
      {
        case 1:
          t1b1(theColour);
          break;
        case 6:
          t1t2(theColour);
          break;
        case 7:
          t1t3(theColour);
          break;
      }
      break;
    case 6:
      switch (moves[randomIndex])
      {
        case 2:
          t2b2(theColour);
          break;
        case 5:
          t2t1(theColour);
          break;
        case 8:
          t2t4(theColour);
          break;
      }
      break;
    case 7:
      switch (moves[randomIndex])
      {
        case 3:
          t3b3(theColour);
          break;
        case 5:
          t3t1(theColour);
          break;
        case 8:
          t3t4(theColour);
          break;
      }
      break;
    case 8:
      switch (moves[randomIndex])
      {
        case 4:
          t4b4(theColour);
          break;
        case 6:
          t4t2(theColour);
          break;
        case 7:
          t4t3(theColour);
          break;
      }
      break;
  }

  switch (box)
  {
    case 0: // Red
      rLoc = moves[randomIndex];
      break;
    case 1: // Green
      gLoc = moves[randomIndex];
      break;
    case 2: // Blue
      bLoc = moves[randomIndex];
      break;
  }

  count++;
}

boolean isThisAValidMove(int location, int destination, int box)
{
  boolean result = false;
  switch (location)
  {
    case 1:
      switch (destination)
      {
        case 2:
          if (rightPlane < 2) {
            result = true;
          }
          break;
        case 3:
          if (frontPlane < 2) {
            result = true;
          }
          break;
        case 5:
          if (topPlane < 2) {
            result = true;
          }
          break;
      }
      break;
    case 2:
      switch (destination)
      {
        case 1:
          if (leftPlane < 2) {
            result = true;
          }
          break;
        case 4:
          if (frontPlane < 2) {
            result = true;
          }
          break;
        case 6:
          if (topPlane < 2) {
            result = true;
          }
          break;
      }
      break;
    case 3:
      switch (destination)
      {
        case 1:
          if (backPlane < 2) {
            result = true;
          }
          break;
        case 4:
          if (rightPlane < 2) {
            result = true;
          }
          break;
        case 7:
          if (topPlane < 2) {
            result = true;
          }
          break;
      }
      break;
    case 4:
      switch (destination)
      {
        case 2:
          if (backPlane < 2) {
            result = true;
          }
          break;
        case 3:
          if (leftPlane < 2) {
            result = true;
          }
          break;
        case 8:
          if (topPlane < 2) {
            result = true;
          }
          break;
      }
      break;
    case 5:
      switch (destination)
      {
        case 6:
          if (rightPlane < 2) {
            result = true;
          }
          break;
        case 7:
          if (frontPlane < 2) {
            result = true;
          }
          break;
        case 1:
          if (bottomPlane < 2) {
            result = true;
          }
          break;
      }
      break;
    case 6:
      switch (destination)
      {
        case 5:
          if (leftPlane < 2) {
            result = true;
          }
          break;
        case 8:
          if (frontPlane < 2) {
            result = true;
          }
          break;
        case 2:
          if (bottomPlane < 2) {
            result = true;
          }
          break;
      }
      break;
    case 7:
      switch (destination)
      {
        case 5:
          if (backPlane < 2) {
            result = true;
          }
          break;
        case 8:
          if (rightPlane < 2) {
            result = true;
          }
          break;
        case 3:
          if (bottomPlane < 2) {
            result = true;
          }
          break;
      }
      break;
    case 8:
      switch (destination)
      {
        case 6:
          if (backPlane < 2) {
            result = true;
          }
          break;
        case 7:
          if (leftPlane < 2) {
            result = true;
          }
          break;
        case 4:
          if (bottomPlane < 2) {
            result = true;
          }
          break;
      }
      break;
  }

  switch(box)
  {
    case 0: //Red
      if(gLoc == destination || bLoc == destination)
      {
        result = false;
      }
      break;
    case 1: //Green
      if(rLoc == destination || bLoc == destination)
      {
        result = false;
      }
      break;
    case 2: //Blue
      if(gLoc == destination || rLoc == destination)
      {
        result = false;
      }
      break;
  }

  serial->print(location);
  serial->print(" -> ");
  serial->print(destination);
  serial->print(" | leftPlane: ");
  serial->print(leftPlane);
  serial->print(" rightPlane: ");
  serial->print(rightPlane);
  serial->print(" topPlane: ");
  serial->print(topPlane);
  serial->print(" bottomPlane: ");
  serial->print(bottomPlane);
  serial->print(" frontPlane: ");
  serial->print(frontPlane);
  serial->print(" backPlane: ");
  serial->print(backPlane);
  serial->print(" | Result: ");
  serial->println(result);

  return (result);
}

/*
 * 24 Valid moves in total. Cube broken into 4 quadrants, on the bottom, and
 * another 4 on the top. Valid moves are left, right, forward, backwards, up
 * and down.
 *
 *   -----------------
 *   | T1(5) | T2(6) |
 *   -----------------
 *   | T3(7) | T4(8) |
 *   -----------------
 * -----------------
 * | B1(1) | B2(2) |
 * -----------------
 * | B3(3) | B4(4) |
 * -----------------
 *
 */
void t1t2(rgb_t theColour)
{
  cube.box(0, 2, 2, 0, 3, 3, BLACK);
  cube.box(2, 2, 2, 2, 3, 3, theColour);
  delay(theDelay);
  cube.box(1, 2, 2, 1, 3, 3, BLACK);
  cube.box(3, 2, 2, 3, 3, 3, theColour);
  delay(theDelay);

  leftPlane--;
  rightPlane++;
}

void t1t3(rgb_t theColour)
{
  cube.box(0, 3, 2, 1, 3, 3, BLACK);
  cube.box(0, 1, 2, 1, 1, 3, theColour);
  delay(theDelay);
  cube.box(0, 2, 2, 1, 2, 3, BLACK);
  cube.box(0, 0, 2, 1, 0, 3, theColour);
  delay(theDelay);

  backPlane--;
  frontPlane++;
}

void t1b1(rgb_t theColour)
{
  cube.box(0, 2, 3, 1, 3, 3, BLACK);
  cube.box(0, 2, 1, 1, 3, 1, theColour);
  delay(theDelay);
  cube.box(0, 2, 2, 1, 3, 2, BLACK);
  cube.box(0, 2, 0, 1, 3, 0, theColour);
  delay(theDelay);

  topPlane--;
  bottomPlane++;
}

void t2t1(rgb_t theColour)
{
  cube.box(3, 2, 2, 3, 3, 3, BLACK);
  cube.box(1, 2, 2, 1, 3, 3, theColour);
  delay(theDelay);
  cube.box(2, 2, 2, 2, 3, 3, BLACK);
  cube.box(0, 2, 2, 0, 3, 3, theColour);
  delay(theDelay);

  rightPlane--;
  leftPlane++;
}

void t2t4(rgb_t theColour)
{
  cube.box(2, 3, 2, 3, 3, 3, BLACK);
  cube.box(2, 1, 2, 3, 1, 3, theColour);
  delay(theDelay);
  cube.box(2, 2, 2, 3, 2, 3, BLACK);
  cube.box(2, 0, 2, 3, 0, 3, theColour);
  delay(theDelay);

  backPlane--;
  frontPlane++;
}

void t2b2(rgb_t theColour)
{
  cube.box(2, 2, 3, 3, 3, 3, BLACK);
  cube.box(2, 2, 1, 3, 3, 1, theColour);
  delay(theDelay);
  cube.box(2, 2, 2, 3, 3, 2, BLACK);
  cube.box(2, 2, 0, 3, 3, 0, theColour);
  delay(theDelay);

  topPlane--;
  bottomPlane++;
}

void t3t1(rgb_t theColour)
{
  cube.box(0, 0, 2, 1, 0, 3, BLACK);
  cube.box(0, 2, 2, 1, 2, 3, theColour);
  delay(theDelay);
  cube.box(0, 1, 2, 1, 1, 3, BLACK);
  cube.box(0, 3, 2, 1, 3, 3, theColour);
  delay(theDelay);

  frontPlane--;
  backPlane++;
}

void t3t4(rgb_t theColour)
{
  cube.box(0, 0, 2, 0, 1, 3, BLACK);
  cube.box(2, 0, 2, 2, 1, 3, theColour);
  delay(theDelay);
  cube.box(1, 0, 2, 1, 1, 3, BLACK);
  cube.box(3, 0, 2, 3, 1, 3, theColour);
  delay(theDelay);

  leftPlane--;
  rightPlane++;
}

void t3b3(rgb_t theColour)
{
  cube.box(0, 0, 3, 1, 1, 3, BLACK);
  cube.box(0, 0, 1, 1, 1, 1, theColour);
  delay(theDelay);
  cube.box(0, 0, 2, 1, 1, 2, BLACK);
  cube.box(0, 0, 0, 1, 1, 0, theColour);
  delay(theDelay);

  topPlane--;
  bottomPlane++;
}

void t4t3(rgb_t theColour)
{
  cube.box(3, 0, 2, 3, 1, 3, BLACK);
  cube.box(1, 0, 2, 1, 1, 3, theColour);
  delay(theDelay);
  cube.box(2, 0, 2, 2, 1, 3, BLACK);
  cube.box(0, 0, 2, 0, 1, 3, theColour);
  delay(theDelay);

  rightPlane--;
  leftPlane++;
}

void t4t2(rgb_t theColour)
{
  cube.box(2, 0, 2, 3, 0, 3, BLACK);
  cube.box(2, 2, 2, 3, 2, 3, theColour);
  delay(theDelay);
  cube.box(2, 1, 2, 3, 1, 3, BLACK);
  cube.box(2, 3, 2, 3, 3, 3, theColour);
  delay(theDelay);

  frontPlane--;
  backPlane++;
}

void t4b4(rgb_t theColour)
{
  cube.box(2, 0, 3, 3, 1, 3, BLACK);
  cube.box(2, 0, 1, 3, 1, 1, theColour);
  delay(theDelay);
  cube.box(2, 0, 2, 3, 1, 2, BLACK);
  cube.box(2, 0, 0, 3, 1, 0, theColour);
  delay(theDelay);

  topPlane--;
  bottomPlane++;
}

void b1b2(rgb_t theColour)
{
  cube.box(0, 2, 0, 0, 3, 1, BLACK);
  cube.box(2, 2, 0, 2, 3, 1, theColour);
  delay(theDelay);
  cube.box(1, 2, 0, 1, 3, 1, BLACK);
  cube.box(3, 2, 0, 3, 3, 1, theColour);
  delay(theDelay);

  leftPlane--;
  rightPlane++;
}

void b1b3(rgb_t theColour)
{
  cube.box(0, 3, 0, 1, 3, 1, BLACK);
  cube.box(0, 1, 0, 1, 1, 1, theColour);
  delay(theDelay);
  cube.box(0, 2, 0, 1, 2, 1, BLACK);
  cube.box(0, 0, 0, 1, 0, 1, theColour);
  delay(theDelay);

  backPlane--;
  frontPlane++;
}

void b1t1(rgb_t theColour)
{
  cube.box(0, 2, 0, 1, 3, 0, BLACK);
  cube.box(0, 2, 2, 1, 3, 2, theColour);
  delay(theDelay);
  cube.box(0, 2, 1, 1, 3, 1, BLACK);
  cube.box(0, 2, 3, 1, 3, 3, theColour);
  delay(theDelay);

  bottomPlane--;
  topPlane++;
}

void b2b1(rgb_t theColour)
{
  cube.box(3, 2, 0, 3, 3, 1, BLACK);
  cube.box(1, 2, 0, 1, 3, 1, theColour);
  delay(theDelay);
  cube.box(2, 2, 0, 2, 3, 1, BLACK);
  cube.box(0, 2, 0, 0, 3, 1, theColour);
  delay(theDelay);

  rightPlane--;
  leftPlane++;
}

void b2b4(rgb_t theColour)
{
  cube.box(2, 3, 0, 3, 3, 1, BLACK);
  cube.box(2, 1, 0, 3, 1, 1, theColour);
  delay(theDelay);
  cube.box(2, 2, 0, 3, 2, 1, BLACK);
  cube.box(2, 0, 0, 3, 0, 1, theColour);
  delay(theDelay);

  backPlane--;
  frontPlane++;
}

void b2t2(rgb_t theColour)
{
  cube.box(2, 2, 0, 3, 3, 0, BLACK);
  cube.box(2, 2, 2, 3, 3, 2, theColour);
  delay(theDelay);
  cube.box(2, 2, 1, 3, 3, 1, BLACK);
  cube.box(2, 2, 3, 3, 3, 3, theColour);
  delay(theDelay);

  bottomPlane--;
  topPlane++;
}

void b3b1(rgb_t theColour)
{
  cube.box(0, 0, 0, 1, 0, 1, BLACK);
  cube.box(0, 2, 0, 1, 2, 1, theColour);
  delay(theDelay);
  cube.box(0, 1, 0, 1, 1, 1, BLACK);
  cube.box(0, 3, 0, 1, 3, 1, theColour);
  delay(theDelay);

  frontPlane--;
  backPlane++;
}

void b3b4(rgb_t theColour)
{
  cube.box(0, 0, 0, 0, 1, 1, BLACK);
  cube.box(2, 0, 0, 2, 1, 1, theColour);
  delay(theDelay);
  cube.box(1, 0, 0, 1, 1, 1, BLACK);
  cube.box(3, 0, 0, 3, 1, 1, theColour);
  delay(theDelay);

  leftPlane--;
  rightPlane++;
}

void b3t3(rgb_t theColour)
{
  cube.box(0, 0, 0, 1, 1, 0, BLACK);
  cube.box(0, 0, 2, 1, 1, 2, theColour);
  delay(theDelay);
  cube.box(0, 0, 1, 1, 1, 1, BLACK);
  cube.box(0, 0, 3, 1, 1, 3, theColour);
  delay(theDelay);

  bottomPlane--;
  topPlane++;
}

void b4b3(rgb_t theColour)
{
  cube.box(3, 0, 0, 3, 1, 1, BLACK);
  cube.box(1, 0, 0, 1, 1, 1, theColour);
  delay(theDelay);
  cube.box(2, 0, 0, 2, 1, 1, BLACK);
  cube.box(0, 0, 0, 0, 1, 1, theColour);
  delay(theDelay);

  rightPlane--;
  leftPlane++;
}

void b4b2(rgb_t theColour)
{
  cube.box(2, 0, 0, 3, 0, 1, BLACK);
  cube.box(2, 2, 0, 3, 2, 1, theColour);
  delay(theDelay);
  cube.box(2, 1, 0, 3, 1, 1, BLACK);
  cube.box(2, 3, 0, 3, 3, 1, theColour);
  delay(theDelay);

  frontPlane--;
  backPlane++;
}

void b4t4(rgb_t theColour)
{
  cube.box(2, 0, 0, 3, 1, 0, BLACK);
  cube.box(2, 0, 2, 3, 1, 2, theColour);
  delay(theDelay);
  cube.box(2, 0, 1, 3, 1, 1, BLACK);
  cube.box(2, 0, 3, 3, 1, 3, theColour);
  delay(theDelay);

  bottomPlane--;
  topPlane++;
}

/*
  b1b2(RED);
  b2b4(RED);
  b4b3(RED);
  b3b1(RED);
  b1t1(RED);
  t1b1(RED);
  b1b3(RED);
  b3t3(RED);
  t3b3(RED);
  b3b4(RED);
  b4t4(RED);
  t4b4(RED);
  b4b2(RED);
  b2t2(RED);
  t2b2(RED);
  b2b1(RED);
  b1t1(RED);
  t1t2(RED);
  t2t4(RED);
  t4t3(RED);
  t3t1(RED);
  t1t3(RED);
  t3t4(RED);
  t4t2(RED);
  t2t1(RED);
  t1b1(RED);

   moveBox(1, 2, BLUE, 0);
  moveBox(2, 1, BLUE, 0);
  moveBox(1, 3, BLUE, 0);
  moveBox(3, 1, BLUE, 0);
  moveBox(1, 5, BLUE, 0);
  moveBox(5, 1, BLUE, 0);

  moveBox(1, 2, BLUE, 0);
  moveBox(2, 4, BLUE, 0);
  moveBox(4, 2, BLUE, 0);
  moveBox(2, 6, BLUE, 0);
  moveBox(6, 2, BLUE, 0);

  moveBox(2, 4, BLUE, 0);
  moveBox(4, 3, BLUE, 0);
  moveBox(3, 4, BLUE, 0);
  moveBox(4, 8, BLUE, 0);
  moveBox(8, 4, BLUE, 0);
  
  moveBox(4, 3, BLUE, 0);
  moveBox(3, 7, BLUE, 0);
  moveBox(7, 3, BLUE, 0);
  
  moveBox(3, 7, BLUE, 0);
  moveBox(7, 5, BLUE, 0);
  moveBox(5, 6, BLUE, 0);
  moveBox(6, 5, BLUE, 0);  
  moveBox(5, 7, BLUE, 0);

  moveBox(7, 8, BLUE, 0);
  moveBox(8, 6, BLUE, 0);
  moveBox(6, 8, BLUE, 0);
  moveBox(8, 7, BLUE, 0);

  moveBox(7, 8, BLUE, 0);
  moveBox(8, 6, BLUE, 0);
  moveBox(6, 2, BLUE, 0);
  moveBox(2, 6, BLUE, 0);
  moveBox(6, 5, BLUE, 0);

 */

