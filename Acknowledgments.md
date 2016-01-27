# Acknowledgments

The following lists sources for sketches, inspiration, and artefacts that I have used in creating the sketches.

## Freetronics Cube4 Matrix PDF
Original version created by user **ponch58**, and posted to [http://forum.freetronics.com/viewtopic.php?f=32&t=5562](http://forum.freetronics.com/viewtopic.php?f=32&t=5562). I've modified this version to include the position of each LED and the corners, as I use these features in a number of my sketches.


## Freetronics Cube4 Matrix
Original version created by user **ponch58**, and posted to [http://forum.freetronics.com/viewtopic.php?f=32&t=5562](). I've modified this version to include the position of each LED and the corners, as I use these features in a number of my sketches.

## Videos
Numerous videos have been posted that show animations running on a 4x4x4 cube. I used these as inspiration for many of my sketches. Three particularly useful videos are:-

* [4x4x4 Led cube demo](https://www.youtube.com/watch?v=adXXSitxPdo)
* [Arduino Uno 4x4x4 LED Cube](https://www.youtube.com/watch?v=XplWwPg8Blk)
* [4x4x4 LED Cube Light Show  Tutorial HD](https://www.youtube.com/watch?v=-jpL6jEuulk)


# Sketches
Sketches located within the **3rd Party** folder were created by other people. I have modified or adapted them in some form, but wish to acknowledge their original authors below.

## Colour Fader
Part of the example sketches from the Cube4 Library. The original source of the sketch is by user **sparky-nz** on the Freetronics forums at [http://forum.freetronics.com/viewtopic.php?f=32&t=5577&p=11085](http://forum.freetronics.com/viewtopic.php?f=32&t=5577&p=11085).

My modification was to make a non blocking version.

## Cubes
Part of the example sketches from the Cube4 Library. The original source is from the [Cubes](https://github.com/freetronics/Cube4/blob/master/examples/Cubes/Cubes.ino) sketch  **Blake Kus** (blakekus@gmail.com) released under the GPLv3.

My modification was to make a non blocking version.

## DoubleCube
Part of the example sketches from the Cube4 Library. The original source of the sketch is by user **sparky-nz** on the Freetronics forums at [http://forum.freetronics.com/viewtopic.php?f=32&t=5579](http://forum.freetronics.com/viewtopic.php?f=32&t=5579). 

I've modified the original to simplify the drawing, and to ensure the random number generator is seeded so that different patterns happen. In addition I made it non blocking.

## Emergency Flashing
Original sketch by user **yatto** on the Freetronics forums at [http://forum.freetronics.com/viewtopic.php?f=32&t=6507](http://forum.freetronics.com/viewtopic.php?f=32&t=6507). 

I've modified the original to simplify the code, and added a non blocking version.

## Heartbeat
Part of the example sketches from the Cube4 Library. The original source is from the [Heartbeat](https://github.com/freetronics/Cube4/blob/master/examples/Heartbeat/Heartbeat.ino) sketch by **Jonathan Oxer** (jon@freetronics.com) released under the GPLv3.

My modification was to change the drawing of the rise and fall motion from using while loops to using the buildLEDsArray coordinates approach from my library, and to then just use the appropriate index within that array to turn on or off the appropriate LED. This has then allowed me to make it into a non blocking version.

## LaserShow
Part of the example sketches from the Cube4 Library. The original source is from the [LaserShow](https://github.com/freetronics/Cube4/blob/master/examples/LaserShow/LaserShow.ino) sketch by **Blake Kus** (blakekus@gmail.com) released under the GPLv3.

I've modified the sketch to allow user defined colours, removed the second part of the animations (leaving only the lasers moving), and made it into a non blocking version.

## RainStorm
Part of the example sketches from the Cube4 Library. The original source is from the [RainStorm](https://github.com/freetronics/Cube4/blob/master/examples/RainStorm/RainStorm.ino) sketch by **Jonathan Oxer** (jon@freetronics.com) released under the GPLv3.

My modification was to make a non blocking version.

## Random Colours
Part of the example sketches from the Cube4 Library. The original source is from the [RandomColours](https://github.com/freetronics/Cube4/blob/master/examples/RandomColours/RandomColours.ino), [RandomPastels](https://github.com/freetronics/Cube4/blob/master/examples/RandomPastels/RandomPastels.ino), and [RandomPrimaries](https://github.com/freetronics/Cube4/blob/master/examples/RandomPrimaries/RandomPrimaries.ino) sketches by **Jonathan Oxer** (jon@freetronics.com) released under the GPLv3.

My modification was to combine the three sketches and make that into a non blocking version. I've also completed minor modifications to how the randomness is generated so that all sketches used the same approach, and that the random number generator was properly seeded.

## Test Pattern
Part of the example sketches from the Cube4 Library. The original source is from the [TestPattern](https://github.com/freetronics/Cube4/blob/master/examples/TestPattern/TestPattern.ino) sketch by **Jonathan Oxer** (jon@freetronics.com) released under the GPLv3.

I have made a non blocking version of this sketch. Unlike the original, my version doesn't move from one type of test to the next. It's up to the user to pick which pattern to run. I also modified the stepThroughLEDs function to use the buildLEDsArray coordinates approach from my library, which makes it easier to implement in a non blocking sketch.
