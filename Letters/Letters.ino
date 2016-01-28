/*
   File:      Letters.ino
   Purpose:   Letters pattern for the Freetronics 4x4x4 Cube
   Author:    Adam Reed (adam@secretcode.ninja)
   Licence:   BSD 3-Clause Licence
*/

// Include required libraries
#include "Cube.h"

/*
   User editable variables
*/


/*
   Don't edit these variables
*/
// Create an instance of the cube class
Cube cube;

void setup() {
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
    serial->println("Letters v1.1");
  }

  // Random Seed
  // Set this to a static number to get the same sequence each time it starts,
  // otherwise set it to analogRead(Unused Pin) to run a difference sequence
  // each time it starts (where Unused Pin is an unused analog pin).
  int theRandomSeed = analogRead(0);

  // Seed the random number generator
  randomSeed(theRandomSeed);
}

void loop() {
  // Display a message
  displayText("Hello World", BLUE, 750, 100);
  cube.all(BLACK);
  delay(1000);

  // Display all of the supported characters
  displayText("abcdefghijklmnopqrstuvwxyz", GREEN, 750, 100);
  displayText("0123456789", BLACK, 750, 100);
}

void displayText(char message[], rgb_t theColour, int theDelay, int betweenCharDelay) {
  /*
     displayText will print letters on the Y0 plane of the cube
       message          = Message to display one character at
                          a time.
                            - Allowed characters are A-Z, 0-9,
                              and a space
                            - Invalid characters show all RED
       theColour        = Colour to display the message in.
                          If set to BLACK, then a random colour
                          is picked for each character
       theDelay         = Time in milliseconds to show each
                          character
       betweenCharDelay = Time in milliseconds to show black
                          between each character
  */

  // Define variables used by the function
  char letter;
  bool useRandomColour = 0;
  byte randomColour = 0;
  byte lastRandomColour = 0;
  int i = 0;
  // List of colours to pick from if BLACK (random) is selected
  rgb_t colours[8] = {BLUE, GREEN, ORANGE, PINK, PURPLE, RED, WHITE, YELLOW};

  // If the user set the colour to BLACK, pick a random colour for each letter
  if (theColour.color[0] == 0 && theColour.color[1] == 0 && theColour.color[2] == 0) {
    useRandomColour = 1;
  }

  while (message[i]) {
    // Get the next letter to display, and convert to upper case
    letter = toupper(message[i]);

    if (useRandomColour) {
      // Use a random colour, so pick from one of the predefined
      // colours
      while (randomColour == lastRandomColour) {
        randomColour = random(0, 8);
      }
      theColour = colours[randomColour];
      lastRandomColour = randomColour;
    }

    // Turn all LEDs off, and pause.
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
      cube.line(0, 0, 2, 0, 0, 3, theColour);
      cube.line(3, 0, 2, 3, 0, 3, theColour);
      cube.line(1, 0, 1, 2, 0, 1, theColour);
      cube.set(0, 0, 0, theColour);
      cube.set(3, 0, 0, theColour);
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
      // Space character, so show all black for the
      // time a normal character is shown
      cube.all(BLACK);
    } else {
      // Unknown Letter, so show all red as an error
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
