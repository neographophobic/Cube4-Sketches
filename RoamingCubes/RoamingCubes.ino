/*
 * File:    RoamingCubes.ino
 * Version: 1.0
 * Author:  Adam Reed (adam@secretcode.ninja)
 * License: BSD 3-Clause Licence
 *
 * Inspired by Trilobyte Projects "4x4x4 Led cube demo"
 * at https://www.youtube.com/watch?v=adXXSitxPdo&t=18
 */

/*
 * There are 3 2x2x2 mini cubes that roam around the larger 4x4x4 cube. The
 * mini cubes move in a random direction either left, right, back, forward,
 * up, or down.
 *
 * The movement is only allowed if there are not already 2 cubes in the
 * destination plane, and that the destination location isn't occupied.
 *
 * There are 24 valid moves in total. The cube broken into 4 quadrants on
 * the bottom, and another 4 on the top. Each of the quadrants is assigned a
 * number which is used to determine where the mini cubes are, and where
 * they can move to. From any location, there are three possible moves, but
 * due to the above, some of these locations may not be allowed.
 *
 * The Layout of the locations is as follows:-
 * Top
 *   -------------------
 *   |        |        |
 *   | 5 (T1) | 6 (T2) |
 *   |        |        |
 *   -------------------
 *   |        |        |
 *   | 7 (T3) | 8 (T4) |
 *   |        |        |
 *   -------------------
 *
 * Bottom
 * -------------------
 * |        |        |
 * | 1 (B1) | 2 (B2) |
 * |        |        |
 * -------------------
 * |        |        |
 * | 3 (B3) | 4 (B4) |
 * |        |        |
 * -------------------
 *
 */

#include "SPI.h"
#include "Cube.h"

Cube cube;

/*
 * User editable variables
 */

// Uncomment to enable debug mode, which prints information about the moves
// to the serial console.
// #define DEBUG

// Define the 3 colours to use. You can use any three colours you like.
rgb_t colours[3] = {RED, GREEN, BLUE};

// Define delays in the animations
unsigned int duringMoveDelay = 100;    // Delay during the move of a cube
unsigned int betweenMovesDelay = 200;  // Delay between moving two cubes

/*
 * Don't change the following variables
 */

// Track how many cubes are currently located on a given plane
byte leftPlane   = 0;
byte rightPlane  = 0;
byte topPlane    = 0;
byte bottomPlane = 0;
byte frontPlane  = 0;
byte backPlane   = 0;

// Track the location of each cube
byte cube1Loc = 0;
byte cube2Loc = 0;
byte cube3Loc = 0;

// Count how many times we have moved a cube
unsigned int count = 1;

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

  // Random Seed
  // Set this to a static number to get the same sequence each time it starts,
  // otherwise set it to analogRead(Unused Pin) to run a difference sequence
  // each time it starts (where Unised Pin is an unused analog pin).
  int theRandomSeed = analogRead(0);

  // Print Debug Info if a serial interface is present
  if (Serial) 
  {
    serial->println("RoamingCubes v1.0");
    serial->print("Sequence: ");
    serial->println(theRandomSeed);
#ifndef DEBUG
    serial->println("DEBUG Mode off");
#endif
  }

  // Seed the random number generator
  randomSeed(theRandomSeed);

  // Create the small cubes, and flag / track where they are
  // Cube 1
  cube.box(0, 2, 0, 1, 3, 1, colours[0]);
  leftPlane++;
  bottomPlane++;
  backPlane++;
  cube1Loc = 1;

  // Cube 2
  cube.box(0, 0, 2, 1, 1, 3, colours[1]);
  leftPlane++;
  topPlane++;
  frontPlane++;
  cube2Loc = 7;

  // Cube 3
  cube.box(2, 0, 0, 3, 1, 1, colours[2]);
  rightPlane++;
  bottomPlane++;
  frontPlane++;
  cube3Loc = 4;

  // Initial delay before we start moving the cubes
  delay(betweenMovesDelay);
}

/**
 */
void loop(void) {
  // Declare tracking variables
  byte i = 0;
  byte validMoves[3];

  // Constantly loop through each of the colours, and move the matching
  // cube
  while (i < 3)
  {
    // Determine which cube to move, and where it is
    byte cubeToMove = 0;
    switch (i)
    {
      case 0: // Cube 1
        cubeToMove = cube1Loc;
        break;
      case 1: // Cube 2
        cubeToMove = cube2Loc;
        break;
      case 2: // Cube 3
        cubeToMove = cube3Loc;
        break;
    }

    // Determine the valid moves based on the cubes location
    switch (cubeToMove)
    {
      case 1:
        validMoves[0] = 2;
        validMoves[1] = 3;
        validMoves[2] = 5;
        break;
      case 2:
        validMoves[0] = 1;
        validMoves[1] = 4;
        validMoves[2] = 6;
        break;
      case 3:
        validMoves[0] = 1;
        validMoves[1] = 4;
        validMoves[2] = 7;
        break;
      case 4:
        validMoves[0] = 2;
        validMoves[1] = 3;
        validMoves[2] = 8;
        break;
      case 5:
        validMoves[0] = 1;
        validMoves[1] = 6;
        validMoves[2] = 7;
        break;
      case 6:
        validMoves[0] = 2;
        validMoves[1] = 5;
        validMoves[2] = 8;
        break;
      case 7:
        validMoves[0] = 3;
        validMoves[1] = 5;
        validMoves[2] = 8;
        break;
      case 8:
        validMoves[0] = 4;
        validMoves[1] = 6;
        validMoves[2] = 7;
        break;
    }

    // Move the cube
    moveCube(cubeToMove, validMoves, colours[i], i);

    // Increment counter so that we move the next cube
    i++;
    if (i == 3) {
      // At the end of the cubes, so set the counter back to the first cube
      i = 0;
    }
  }
}

void moveCube(byte startLocation, byte moves[], rgb_t theColour, byte theCube)
{
  /*
   * Move theCube from it's startLocation, to a valid location within the moves
   * array ensuring it keeps theColour that was provided.
   */

  // Define a variable to hold the index within the moves array that we will try
  byte randomIndex;

#ifdef DEBUG
  // Define a variable that we use mainly for debugging that stops trying to find
  // a valid move
  byte loopKiller = 0;

  // Print Debug info, including which move this is, and for which cube
  serial->print("Move: ");
  serial->print(count);
  serial->print(" Cube: ");
  serial->println(theCube);
#endif

  // Pick the location to move to, ensuring it's a valid move
  do
  {
    // Pick a random number between 0 and 2 to use as the index in the moves
    // array
    randomIndex = random(0, 3);

#ifdef DEBUG
    // Sanity checker that will stop the sketch if we haven't managed to find
    // a valid move after 100 attempts.
    loopKiller++;
    if (loopKiller > 100) {
      serial->println("Endless Loop - Killing...");
      while (true) {
        // Do nothing and just loop endlessly.
      }
    }
#endif

    // Keep looping until we have found a move that is a valid move according to
    // our rules.
  } while (isThisAValidMove(startLocation, moves[randomIndex], theCube) == false);

  // Move to the new location. The code looks firstly at the startLocation, then
  // at the destination, and calls the appropriate function to make the move.
  switch (startLocation)
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

  // Track where the cube moved to
  switch (theCube)
  {
    case 0: // Cube 1
      cube1Loc = moves[randomIndex];
      break;
    case 1: // Cube 2
      cube2Loc = moves[randomIndex];
      break;
    case 2: // Cube 3
      cube3Loc = moves[randomIndex];
      break;
  }

  // Increment the moves counter
  count++;
}

boolean isThisAValidMove(byte startLocation, byte destination, byte theCube)
{
  /*
   * Compares the startLocationto the destination for theCube and determines
   * whether it is a valid move according to the rules. If it is we return
   * true, otherwise we return false.
   */

  // Default to it being an invalid move
  boolean result = false;

  // Determine if the move would not result in more than 2 cubes on any plane.
  // The code looks firstly at the startLocation, then at the destination, and
  // if the destination plane based of the direction of movement will have less
  // than 3 cubes, allow the move.
  switch (startLocation)
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

  // Ensure that where we plan on moving a cube to isn't already used by
  // a different cube. If so, don't allow the move.
  switch (theCube)
  {
    case 0: // Cube 1
      if (cube2Loc == destination || cube3Loc == destination)
      {
        result = false;
      }
      break;
    case 1: // Cube 2
      if (cube1Loc == destination || cube3Loc == destination)
      {
        result = false;
      }
      break;
    case 2: // Cube 3
      if (cube2Loc == destination || cube1Loc == destination)
      {
        result = false;
      }
      break;
  }

#ifdef DEBUG
  /*
   * Print Debug Information including:-
   *   - Start Location and Destination Location
   *   - Plane Counts for all planes (this is the start locations details)
   *   - Whether the move is allowed or not
   */
  serial->print(startLocation);
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
#endif

  // Return whether the move should be allowed or not
  return (result);
}

/*
 * The following set of 24 functions handle the actual movement of cubes.
 * Each function is named after the quadrant that the move starts from,
 * and the quadrant that the move finishes at.
 *
 * They all have the same basic structure. It is:-
 *   - Hide one part of the cube, and show the next part (the "half move")
 *   - delay for the duringMoveDelay time
 *   - Hide the last part of the original cube and show the final part of the
 *     destination cube (completing the move)
 *   - delay for the betweenMovesDelay time
 *   - update the plane counts by subtracting 1 from the plane we moved from,
 *     and adding 1 to the plane we moved to
 */

void t1t2(rgb_t theColour)
{
  cube.box(0, 2, 2, 0, 3, 3, BLACK);
  cube.box(2, 2, 2, 2, 3, 3, theColour);
  delay(duringMoveDelay);
  cube.box(1, 2, 2, 1, 3, 3, BLACK);
  cube.box(3, 2, 2, 3, 3, 3, theColour);
  delay(betweenMovesDelay);

  leftPlane--;
  rightPlane++;
}

void t1t3(rgb_t theColour)
{
  cube.box(0, 3, 2, 1, 3, 3, BLACK);
  cube.box(0, 1, 2, 1, 1, 3, theColour);
  delay(duringMoveDelay);
  cube.box(0, 2, 2, 1, 2, 3, BLACK);
  cube.box(0, 0, 2, 1, 0, 3, theColour);
  delay(betweenMovesDelay);

  backPlane--;
  frontPlane++;
}

void t1b1(rgb_t theColour)
{
  cube.box(0, 2, 3, 1, 3, 3, BLACK);
  cube.box(0, 2, 1, 1, 3, 1, theColour);
  delay(duringMoveDelay);
  cube.box(0, 2, 2, 1, 3, 2, BLACK);
  cube.box(0, 2, 0, 1, 3, 0, theColour);
  delay(betweenMovesDelay);

  topPlane--;
  bottomPlane++;
}

void t2t1(rgb_t theColour)
{
  cube.box(3, 2, 2, 3, 3, 3, BLACK);
  cube.box(1, 2, 2, 1, 3, 3, theColour);
  delay(duringMoveDelay);
  cube.box(2, 2, 2, 2, 3, 3, BLACK);
  cube.box(0, 2, 2, 0, 3, 3, theColour);
  delay(betweenMovesDelay);

  rightPlane--;
  leftPlane++;
}

void t2t4(rgb_t theColour)
{
  cube.box(2, 3, 2, 3, 3, 3, BLACK);
  cube.box(2, 1, 2, 3, 1, 3, theColour);
  delay(duringMoveDelay);
  cube.box(2, 2, 2, 3, 2, 3, BLACK);
  cube.box(2, 0, 2, 3, 0, 3, theColour);
  delay(betweenMovesDelay);

  backPlane--;
  frontPlane++;
}

void t2b2(rgb_t theColour)
{
  cube.box(2, 2, 3, 3, 3, 3, BLACK);
  cube.box(2, 2, 1, 3, 3, 1, theColour);
  delay(duringMoveDelay);
  cube.box(2, 2, 2, 3, 3, 2, BLACK);
  cube.box(2, 2, 0, 3, 3, 0, theColour);
  delay(betweenMovesDelay);

  topPlane--;
  bottomPlane++;
}

void t3t1(rgb_t theColour)
{
  cube.box(0, 0, 2, 1, 0, 3, BLACK);
  cube.box(0, 2, 2, 1, 2, 3, theColour);
  delay(duringMoveDelay);
  cube.box(0, 1, 2, 1, 1, 3, BLACK);
  cube.box(0, 3, 2, 1, 3, 3, theColour);
  delay(betweenMovesDelay);

  frontPlane--;
  backPlane++;
}

void t3t4(rgb_t theColour)
{
  cube.box(0, 0, 2, 0, 1, 3, BLACK);
  cube.box(2, 0, 2, 2, 1, 3, theColour);
  delay(duringMoveDelay);
  cube.box(1, 0, 2, 1, 1, 3, BLACK);
  cube.box(3, 0, 2, 3, 1, 3, theColour);
  delay(betweenMovesDelay);

  leftPlane--;
  rightPlane++;
}

void t3b3(rgb_t theColour)
{
  cube.box(0, 0, 3, 1, 1, 3, BLACK);
  cube.box(0, 0, 1, 1, 1, 1, theColour);
  delay(duringMoveDelay);
  cube.box(0, 0, 2, 1, 1, 2, BLACK);
  cube.box(0, 0, 0, 1, 1, 0, theColour);
  delay(betweenMovesDelay);

  topPlane--;
  bottomPlane++;
}

void t4t3(rgb_t theColour)
{
  cube.box(3, 0, 2, 3, 1, 3, BLACK);
  cube.box(1, 0, 2, 1, 1, 3, theColour);
  delay(duringMoveDelay);
  cube.box(2, 0, 2, 2, 1, 3, BLACK);
  cube.box(0, 0, 2, 0, 1, 3, theColour);
  delay(betweenMovesDelay);

  rightPlane--;
  leftPlane++;
}

void t4t2(rgb_t theColour)
{
  cube.box(2, 0, 2, 3, 0, 3, BLACK);
  cube.box(2, 2, 2, 3, 2, 3, theColour);
  delay(duringMoveDelay);
  cube.box(2, 1, 2, 3, 1, 3, BLACK);
  cube.box(2, 3, 2, 3, 3, 3, theColour);
  delay(betweenMovesDelay);

  frontPlane--;
  backPlane++;
}

void t4b4(rgb_t theColour)
{
  cube.box(2, 0, 3, 3, 1, 3, BLACK);
  cube.box(2, 0, 1, 3, 1, 1, theColour);
  delay(duringMoveDelay);
  cube.box(2, 0, 2, 3, 1, 2, BLACK);
  cube.box(2, 0, 0, 3, 1, 0, theColour);
  delay(betweenMovesDelay);

  topPlane--;
  bottomPlane++;
}

void b1b2(rgb_t theColour)
{
  cube.box(0, 2, 0, 0, 3, 1, BLACK);
  cube.box(2, 2, 0, 2, 3, 1, theColour);
  delay(duringMoveDelay);
  cube.box(1, 2, 0, 1, 3, 1, BLACK);
  cube.box(3, 2, 0, 3, 3, 1, theColour);
  delay(betweenMovesDelay);

  leftPlane--;
  rightPlane++;
}

void b1b3(rgb_t theColour)
{
  cube.box(0, 3, 0, 1, 3, 1, BLACK);
  cube.box(0, 1, 0, 1, 1, 1, theColour);
  delay(duringMoveDelay);
  cube.box(0, 2, 0, 1, 2, 1, BLACK);
  cube.box(0, 0, 0, 1, 0, 1, theColour);
  delay(betweenMovesDelay);

  backPlane--;
  frontPlane++;
}

void b1t1(rgb_t theColour)
{
  cube.box(0, 2, 0, 1, 3, 0, BLACK);
  cube.box(0, 2, 2, 1, 3, 2, theColour);
  delay(duringMoveDelay);
  cube.box(0, 2, 1, 1, 3, 1, BLACK);
  cube.box(0, 2, 3, 1, 3, 3, theColour);
  delay(betweenMovesDelay);

  bottomPlane--;
  topPlane++;
}

void b2b1(rgb_t theColour)
{
  cube.box(3, 2, 0, 3, 3, 1, BLACK);
  cube.box(1, 2, 0, 1, 3, 1, theColour);
  delay(duringMoveDelay);
  cube.box(2, 2, 0, 2, 3, 1, BLACK);
  cube.box(0, 2, 0, 0, 3, 1, theColour);
  delay(betweenMovesDelay);

  rightPlane--;
  leftPlane++;
}

void b2b4(rgb_t theColour)
{
  cube.box(2, 3, 0, 3, 3, 1, BLACK);
  cube.box(2, 1, 0, 3, 1, 1, theColour);
  delay(duringMoveDelay);
  cube.box(2, 2, 0, 3, 2, 1, BLACK);
  cube.box(2, 0, 0, 3, 0, 1, theColour);
  delay(betweenMovesDelay);

  backPlane--;
  frontPlane++;
}

void b2t2(rgb_t theColour)
{
  cube.box(2, 2, 0, 3, 3, 0, BLACK);
  cube.box(2, 2, 2, 3, 3, 2, theColour);
  delay(duringMoveDelay);
  cube.box(2, 2, 1, 3, 3, 1, BLACK);
  cube.box(2, 2, 3, 3, 3, 3, theColour);
  delay(betweenMovesDelay);

  bottomPlane--;
  topPlane++;
}

void b3b1(rgb_t theColour)
{
  cube.box(0, 0, 0, 1, 0, 1, BLACK);
  cube.box(0, 2, 0, 1, 2, 1, theColour);
  delay(duringMoveDelay);
  cube.box(0, 1, 0, 1, 1, 1, BLACK);
  cube.box(0, 3, 0, 1, 3, 1, theColour);
  delay(betweenMovesDelay);

  frontPlane--;
  backPlane++;
}

void b3b4(rgb_t theColour)
{
  cube.box(0, 0, 0, 0, 1, 1, BLACK);
  cube.box(2, 0, 0, 2, 1, 1, theColour);
  delay(duringMoveDelay);
  cube.box(1, 0, 0, 1, 1, 1, BLACK);
  cube.box(3, 0, 0, 3, 1, 1, theColour);
  delay(betweenMovesDelay);

  leftPlane--;
  rightPlane++;
}

void b3t3(rgb_t theColour)
{
  cube.box(0, 0, 0, 1, 1, 0, BLACK);
  cube.box(0, 0, 2, 1, 1, 2, theColour);
  delay(duringMoveDelay);
  cube.box(0, 0, 1, 1, 1, 1, BLACK);
  cube.box(0, 0, 3, 1, 1, 3, theColour);
  delay(betweenMovesDelay);

  bottomPlane--;
  topPlane++;
}

void b4b3(rgb_t theColour)
{
  cube.box(3, 0, 0, 3, 1, 1, BLACK);
  cube.box(1, 0, 0, 1, 1, 1, theColour);
  delay(duringMoveDelay);
  cube.box(2, 0, 0, 2, 1, 1, BLACK);
  cube.box(0, 0, 0, 0, 1, 1, theColour);
  delay(betweenMovesDelay);

  rightPlane--;
  leftPlane++;
}

void b4b2(rgb_t theColour)
{
  cube.box(2, 0, 0, 3, 0, 1, BLACK);
  cube.box(2, 2, 0, 3, 2, 1, theColour);
  delay(duringMoveDelay);
  cube.box(2, 1, 0, 3, 1, 1, BLACK);
  cube.box(2, 3, 0, 3, 3, 1, theColour);
  delay(betweenMovesDelay);

  frontPlane--;
  backPlane++;
}

void b4t4(rgb_t theColour)
{
  cube.box(2, 0, 0, 3, 1, 0, BLACK);
  cube.box(2, 0, 2, 3, 1, 2, theColour);
  delay(duringMoveDelay);
  cube.box(2, 0, 1, 3, 1, 1, BLACK);
  cube.box(2, 0, 3, 3, 1, 3, theColour);
  delay(betweenMovesDelay);

  bottomPlane--;
  topPlane++;
}

