/*
 * File: Letters.ino
 * Version:
 * Author: Adam Reed (adam@secretcode.ninja)
 * License: BSD 3-Clause Licence
 */

#include "SPI.h"
#include "Cube.h"

Cube cube;

void setup() {
  // Serial port options for control of the Cube using serial commands are:
  // 0: Control via the USB connector (most common).
  // 1: Control via the RXD and TXD pins on the main board.
  // -1: Don't attach any serial port to interact with the Cube.
  cube.begin(0, 115200); // Start on serial port 0 (USB) at 115200 baud
}

void loop() {
  // Display a message
  displayText("Hello World", BLUE, 750, 100);
  cube.all(BLACK);
  delay(1000);
  
  // Display all of the supported characters
  displayText("abcdefghijklmnopqrstuvwxyz", GREEN, 750, 100);
  displayText("0123456789", RED, 750, 100);
}

void displayText(char message[], rgb_t theColour, int theDelay, int betweenCharDelay) {
  char letter;
  bool useRandomColour = 0;
  byte randomColour = 0;
  byte lastRandomColour = 0;
  rgb_t colours[8] = {BLUE, GREEN, ORANGE, PINK, PURPLE, RED, WHITE, YELLOW};
  int i = 0;

  // If the user set the colour to BLACK, pick a random colour for each letter
  if (theColour.color[0] == 0 && theColour.color[1] == 0 && theColour.color[2] == 0) {
    useRandomColour = 1;
  }
  
  while (message[i]) {
    // Get the next letter to display, and convert to upper case
    letter = toupper(message[i]);

    if (useRandomColour) {
      // Use a random colour, so pick from one of the predefined 
      // colours.
      while(randomColour == lastRandomColour) {
        randomColour = random(0,8);
      }
      theColour = colours[randomColour];
      lastRandomColour = randomColour;
    }

    // Turn all LEDs off
    cube.all(BLACK);
    delay(betweenCharDelay);
    
    // Draw the character
    if (letter == 'A') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(1, 0, 3, 2, 0, 3, theColour);
      cube.line(1, 0, 1, 2, 0, 1, theColour);
      cube.line(3, 0, 0, 3, 0, 3, theColour);
    } else if (letter == 'B') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(0, 0, 3, 2, 0, 3, theColour);
      cube.line(1, 0, 0, 3, 0, 0, theColour);
      cube.set(2, 0, 2, theColour);
      cube.set(1, 0, 1, theColour);
      cube.set(3, 0, 1, theColour);
    } else if (letter == 'C') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(1, 0, 0, 3, 0, 0, theColour);
      cube.line(1, 0, 3, 3, 0, 3, theColour);
    } else if (letter == 'D') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(1, 0, 0, 2, 0, 0, theColour);
      cube.line(1, 0, 3, 2, 0, 3, theColour);
      cube.line(3, 0, 1, 3, 0, 2, theColour);
    } else if (letter == 'E') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(1, 0, 0, 3, 0, 0, theColour);
      cube.line(1, 0, 2, 2, 0, 2, theColour);
      cube.line(0, 0, 3, 3, 0, 3, theColour);
    } else if (letter == 'F') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(1, 0, 1, 2, 0, 1, theColour);
      cube.line(0, 0, 3, 3, 0, 3, theColour);
    } else if (letter == 'G') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(0, 0, 3, 3, 0, 3, theColour);
      cube.line(0, 0, 0, 3, 0, 0, theColour);
      cube.set(3, 0, 1, theColour);
    } else if (letter == 'H') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(3, 0, 0, 3, 0, 3, theColour);
      cube.line(1, 0, 1, 2, 0, 1, theColour);
    } else if (letter == 'I') {
      cube.line(0, 0, 3, 3, 0, 3, theColour);
      cube.line(0, 0, 0, 3, 0, 0, theColour);
      cube.line(1, 0, 1, 1, 0, 2, theColour);
    } else if (letter == 'J') {
      cube.line(0, 0, 3, 3, 0, 3, theColour);
      cube.line(3, 0, 2, 3, 0, 0, theColour);
      cube.line(0, 0, 0, 2, 0, 0, theColour);
      cube.set(0, 0, 1, theColour);
    } else if (letter == 'K') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(2, 0, 3, 3, 0, 3, theColour);
      cube.line(1, 0, 2, 3, 0, 0, theColour);
    } else if (letter == 'L') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(1, 0, 0, 3, 0, 0, theColour);
    } else if (letter == 'M') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(1, 0, 3, 3, 0, 3, theColour);
      cube.line(3, 0, 2, 3, 0, 0, theColour);
      cube.set(2, 0, 2, theColour);
    } else if (letter == 'N') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(3, 0, 3, 3, 0, 0, theColour);
      cube.line(1, 0, 2, 2, 0, 1, theColour);
    } else if (letter == 'O') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(1, 0, 3, 3, 0, 3, theColour);
      cube.line(3, 0, 2, 3, 0, 0, theColour);
      cube.line(1, 0, 0, 2, 0, 0, theColour);
    } else if (letter == 'P') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(1, 0, 3, 3, 0, 3, theColour);
      cube.line(3, 0, 1, 3, 0, 2, theColour);
      cube.line(1, 0, 1, 2, 0, 1, theColour);
    } else if (letter == 'Q') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(1, 0, 3, 3, 0, 3, theColour);
      cube.line(3, 0, 0, 3, 0, 2, theColour);
      cube.line(1, 0, 0, 2, 0, 0, theColour);
      cube.set(2, 0, 1, theColour);
    } else if (letter == 'R') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(1, 0, 3, 3, 0, 3, theColour);
      cube.line(3, 0, 1, 3, 0, 2, theColour);
      cube.line(1, 0, 1, 2, 0, 1, theColour);
      cube.set(2, 0, 0, theColour);
    } else if (letter == 'S') {
      cube.line(0, 0, 3, 3, 0, 3, theColour);
      cube.line(0, 0, 2, 1, 0, 2, theColour);
      cube.line(2, 0, 1, 3, 0, 1, theColour);
      cube.line(0, 0, 0, 3, 0, 0, theColour);
    } else if (letter == 'T') {
      cube.line(0, 0, 3, 3, 0, 3, theColour);
      cube.line(1, 0, 2, 1, 0, 0, theColour);
    } else if (letter == 'U') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(1, 0, 0, 2, 0, 0, theColour);
      cube.line(3, 0, 0, 3, 0, 3, theColour);
    } else if (letter == 'V') {
      cube.line(0, 0, 1, 0, 0, 3, theColour);
      cube.line(1, 0, 0, 2, 0, 0, theColour);
      cube.line(3, 0, 1, 3, 0, 3, theColour);
    } else if (letter == 'W') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(1, 0, 0, 2, 0, 0, theColour);
      cube.line(3, 0, 0, 3, 0, 3, theColour);
      cube.set(2, 0, 1, theColour);
    } else if (letter == 'X') {
      cube.line(0,0,2, 0,0,3, theColour);
      cube.line(3,0,2, 3,0,3, theColour);
      cube.line(1,0,1, 2,0,1, theColour);
      cube.set(0,0,0, theColour);
      cube.set(3,0,0, theColour);
    } else if (letter == 'Y') {
      cube.line(0, 0, 1, 0, 0, 3, theColour);
      cube.line(3, 0, 1, 3, 0, 3, theColour);
      cube.line(1, 0, 1, 2, 0, 1, theColour);
      cube.line(1, 0, 0, 2, 0, 0, theColour);
    } else if (letter == 'Z') {
      cube.line(0, 0, 3, 2, 0, 3, theColour);
      cube.line(3, 0, 3, 0, 0, 0, theColour);
      cube.line(1, 0, 0, 3, 0, 0, theColour);
    } else if (letter == '0') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(1, 0, 3, 3, 0, 3, theColour);
      cube.line(3, 0, 2, 3, 0, 0, theColour);
      cube.line(1, 0, 0, 2, 0, 0, theColour);
    } else if (letter == '1') {
      cube.set(0, 0, 2, theColour);
      cube.line(1, 0, 3, 2, 0, 3, theColour);
      cube.line(2, 0, 1, 2, 0, 2, theColour);
      cube.line(0, 0, 0, 3, 0, 0, theColour);
    } else if (letter == '2') {
      cube.line(0, 0, 3, 2, 0, 3, theColour);
      cube.line(1, 0, 1, 2, 0, 2, theColour);
      cube.line(1, 0, 0, 3, 0, 0, theColour);
    } else if (letter == '3') {
      cube.line(0, 0, 0, 3, 0, 0, theColour);
      cube.line(3, 0, 1, 3, 0, 2, theColour);
      cube.line(1, 0, 2, 2, 0, 2, theColour);
      cube.line(0, 0, 3, 3, 0, 3, theColour);
    } else if (letter == '4') {
      cube.line(0, 0, 1, 0, 0, 3, theColour);
      cube.line(3, 0, 0, 3, 0, 3, theColour);
      cube.line(1, 0, 1, 2, 0, 1, theColour);
    } else if (letter == '5') {
      cube.line(0, 0, 3, 3, 0, 3, theColour);
      cube.line(0, 0, 2, 1, 0, 2, theColour);
      cube.line(2, 0, 1, 3, 0, 1, theColour);
      cube.line(0, 0, 0, 3, 0, 0, theColour);
    } else if (letter == '6') {
      cube.line(0, 0, 0, 0, 0, 3, theColour);
      cube.line(1, 0, 2, 3, 0, 2, theColour);
      cube.line(1, 0, 0, 3, 0, 0, theColour);
      cube.set(3, 0, 1, theColour);
    } else if (letter == '7') {
      cube.line(0, 0, 3, 3, 0, 3, theColour);
      cube.line(3, 0, 0, 3, 0, 2, theColour);
    } else if (letter == '8') {
      cube.line(1, 0, 0, 3, 0, 0, theColour);
      cube.line(0, 0, 1, 1, 0, 1, theColour);
      cube.line(2, 0, 2, 3, 0, 2, theColour);
      cube.line(0, 0, 3, 2, 0, 3, theColour);
      cube.set(3, 0, 1, theColour);
      cube.set(0, 0, 2, theColour);
     } else if (letter == '9') {
      cube.line(0, 0, 3, 3, 0, 3, theColour);
      cube.line(0, 0, 1, 0, 0, 2, theColour);
      cube.line(1, 0, 1, 2, 0, 1, theColour);
      cube.line(3, 0, 0, 3, 0, 2, theColour);
    } else if (letter == ' ') {
      cube.all(BLACK);
    } else {
      // Unknown Letter
      cube.all(RED);
    }

    // Increment the possition in the message, so that
    // we get the next character to display
    i++;

    // Wait for the period the user selected before showing
    // the next character
    delay(theDelay);
  }
}
