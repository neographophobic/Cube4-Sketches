# Acknowledgments

The following lists sources for sketches, inspiration, and artefacts that I have used in creating the sketches.

## Freetronics 4x4x4 RGB Cube Forum
The [Freetronics 4x4x4 RGB Cube Forum](http://forum.freetronics.com/viewforum.php?f=32) has been a great source of ideas and sample sketches.

## Freetronics Cube4 Matrix
Original version created by user **ponch58**, and posted to [http://forum.freetronics.com/viewtopic.php?f=32&t=5562](). I've modified this version to include the position of each LED and the corners, as I use these features in a number of my sketches.

## Videos
Numerous videos have been posted that show animations running on a 4x4x4 cube. I used these as inspiration for many of my sketches. Three particularly useful videos are:-

* [4x4x4 Led cube demo](https://www.youtube.com/watch?v=adXXSitxPdo)
* [Arduino Uno 4x4x4 LED Cube](https://www.youtube.com/watch?v=XplWwPg8Blk)
* [https://www.youtube.com/watch?v=-jpL6jEuulk](4x4x4 LED Cube Light Show  Tutorial HD)

# Sketches
Sketches located within the **3rd Party** folder were created by other people. I have modified them in some form, but wish to acknowledge their original authors below.

## Colour Fader
Part of the example sketches from the Cube4 Library. The original source of the sketch is by user **sparky-nz** on the Freetronics forums at http://forum.freetronics.com/viewtopic.php?f=32&t=5577&p=11085.

My modification was to make a non blocking version.

## Random Colours
Part of the example sketches from the Cube4 Library. The original source is from the RandomColours, RandomPastels, and RandomPrimaries sketches by Jonathan Oxer (jon@freetronics.com) released under the GPLv3.

My modification was to combine the three sketches and make that into a non blocking version. I've also completed minor modifications to how the randomness is generated so that all sketches used the same approach, and that the random number generator was properly seeded on board startup.

## Cubes
Part of the example sketches from the Cube4 Library. The original source is from the Cubes by Blake Kus (blakekus@gmail.com) released under the GPLv3.

## DoubleCube
Part of the example sketches from the Cube4 Library. The original source of the sketch is by user **sparky-nz** on the Freetronics forums at [http://forum.freetronics.com/viewtopic.php?f=32&t=5579](http://forum.freetronics.com/viewtopic.php?f=32&t=5579). 

I've modified the original to simplify the drawing, and to ensure the random number generator is seeded so that different patterns happen.

## Heartbeat
Part of the example sketches from the Cube4 Library. The original source is from the Heartbeat sketch by Jonathan Oxer (jon@freetronics.com) released under the GPLv3.

My modification was to change the drawing of the rise and fall motion from using while loops to using the buildLEDsArray coordinates approach from my library, and to then just use the appropriate index within that array to turn on or off the appropriate LED. This has then allowed me to make it into a non blocking version.
