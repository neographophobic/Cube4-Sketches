# Cube4 Sketches

This repository is a place for me to publish sketches that I worked on for the [Freetronics 4x4x4 RGB LED Cube](http://www.freetronics.com.au/collections/kits/products/cube4-4x4x4-rgb-led-cube).

All sketches have been tested using the Arduino IDE v1.6.7 on MacOS X 10.10.

## Non Blocking Versions
Typically sketches use delay() to add a pause between patters in an animation. The problem with this is that while the sketch is running, and particularly during a delay no other pieces of code run. This is problematic with things like serial input, as the cube will not respond to it while in a delay, meaning that the command is missed.

A different approach is to use a state machine, that is called roughly every millisecond, but only does actions if it is in the correct state, and if an appropriate amount of time has passed. This approach removes the need for a delay, and allows items like serial input to still occur.

A number of the following sketches include both the "traditional" approach using delay(), and versions that are built using a state machine.

# Installation
These sketches require a Freetronics 4x4x4 RGB LED Cube. In addition they all require the [Cube4 Library](https://github.com/neographophobic/Cube4) (that link is to my modified version of the library). The original version can be found at [Freetronics Cube4 Library](https://github.com/freetronics/Cube4). 

Some sketches also require a helper library that I've written. The library is available from [Cube4_ARUtils](https://github.com/neographophobic/Cube4_ARUtils).

To install these libraries, click on the "Download ZIP" link on the Github page, and then in the Arduino IDE, open a new blank sketch, then select "Sketch" -> "Include Library" -> "Add .ZIP Library".

# Sketches
## Blank
A template I use as a starting point for new sketches. There is also a non blocking version available. To use it do a Find and Replace on "Blank" to the name you wish, and then modify as appropriate.

*There is a non blocking version of this template, and it includes the Cube4_ARUtils library (which can be removed if not required).*


## Colour Pulse
Given a colour, it will fade it out to black, and then back to the given colour. You can also control the increments that it fades in and out by.

*There is a non blocking version of this sketch. Both versions require the Cube4_ARUtils library.*

## Cube Edge
This sketch takes a starting point in one of the corners, and then branches out to the diagonally opposite corner around the edges of the cube. From each corner it reaches it goes in the three possible directions.

While I've used three points for the sketch, the code supports starting from any of the 8 corners of the cube.

*This sketch requires the Cube4_ARUtils library.*

## Expanding
Starting in one of the corners, the sketch will expand out until it reaches the far corners, and then contract back to the starting point. It supports starting at any of the corners of the cube.

*This sketch requires the Cube4_ARUtils library.*

## Face Expanding
This sketch is similar to the "Expanding" sketch above, but it only expands along the face of the cube. The code demonstrates the left to right movement, but also supports moving right to left, by changing the "5" to "1" in the call to faceExpand().

*This sketch requires the Cube4_ARUtils library.*

## Face Peel
This sketch will diagonally fill in a face of the cube, then pull it, again diagonally to the face opposite.

*This sketch requires the Cube4_ARUtils library.*

## Face Sweep
In this sketch, we illuminate a face, and then sweep it from that face, to another face that is connected to it like it was swinging on a hinge. 

*There is a non blocking version of this sketch.*

## Flashing Cubes
This sketch will flash in "inner" and "outer" cube.

*There is a non blocking version of this sketch.*

## Letters
This sketch will attempt to draw letters or numbers on the Y 0 plane of the cube. A 4x4 grid is limiting, so some of the text isn't the clearest but it works as a proof of concept.

If you set the colour of the letters to BLACK, the sketch will pick a random colour colour to use for each letter of a given message.

## Looping Boxes
This sketch has a small inner square, and a larger outer square that is hollow. The inner square passes through the outer square, and then the squares move along a face and then process repeats.

*There is a non blocking version of this sketch.*

## Plane Move
This sketch moves each plane from the 0 face to the 3 face and then back again.

## Random Fill
Randomly fills the cube, one LED at a time randomly picking 1 of eight colours. It then turns the LEDS  off in the same order.

*This sketch requires the Cube4_ARUtils library.*

## Random Pull
This sketch lights up a face, then randomly picks LEDs and "pulls" them to the opposite face.

*This sketch requires the Cube4_ARUtils library.*

## Roaming Cubes
There are 3 2x2x2 mini cubes that roam around the larger 4x4x4 cube. The mini cubes move in a random direction either left, right, back, forward, up, or down.

The movement is only allowed if there are not already 2 cubes in the destination plane, and that the destination location isn't occupied.

## Rotate Plane
This sketch rotates a plane either horizontally or vertically in either a clockwise or anti-clockwise direction.

## Snake
Fill the entire cube in a "snake" like pattern.

## Spiral
This sketch draws around the outside of the cube. It supports starting on each face and working one LED at a time to the opposite face.

*There is a non blocking version of this sketch. Both versions require the Cube4_ARUtils library.*

## Splat
This is a hard pattern to describe. It's as if there are two blobs that get thrown together in the middle, then slide down a wall to the bottom of the cube and get thrown back together. If you have a better name let me know.

*There is a non blocking version of this sketch.*

## Sweep
This sketch is a simpler version of "Rotate Plane" that only support horizontal rotation in a clockwise direction.

*There is a non blocking version of this sketch.*

## Wave
This sketch creates a wave style motion.

*There is a non blocking version of this sketch.*

## ZigZag
Creates a Zig / Zag style pattern.

*There is a non blocking version of this sketch.*

# 3rd Party Sketches
Please see the **Acknowledgments.txt** file for information on where I have sourced these from.

## Colour Fader
Fades the cube through a series of colours. 

*This sketch is a non blocking version of the original sketch.*

## Cubes
Demonstrates different cube styles.

*This sketch is a non blocking version of the original sketch.*

## DoubleCube
Places a 2x2x2 cube within the larger 4x4x4 cube, and picks random colours for both.

*This sketch is a non blocking version of the original sketch.*

## Emergency Flashing
Simulates the red / blue flashing lights of an emergency vehicle.

*There is a "traditional" and non blocking version of the original sketch.*

## Heartbeat
Simulates a heart beat.

*This sketch is a non blocking version of the original sketch, and requires the Cube4_ARUtils library.*

## LaserShow
Draw a series of laser lights from the bottom corners, then from the top corners. I've removed the second part of the original sketch that resulted in a solid red cube.

*This sketch is a non blocking version of the original sketch.*

## RainStorm
Simulates a rain storm, with the option of clouds and lightning.

*This sketch is a non blocking version of the original sketch.*

## Random Colours
Set each LED in the cube to a constantly changing random colour. There are three different options (due to combining the 3 Random Colour example sketches). Only one option can be used at a time.

* Random Colour = Any possible colour
* Random Pastels = Any pastel colour
* Random Primaries = Red, Green, or Blue

*This sketch is a non blocking version of the original sketches.*

## Test Pattern
The test pattern that ships with each cube, with each "stage" of it broken up into a different function. Only one option can be used at a time.

* Step Through LEDs
* Cycle Cube Colours
* Fade White
* Random Pastels (same as from Random Colours above)

*This sketch is a non blocking version of the original sketch, and requires the Cube4_ARUtils library.*
