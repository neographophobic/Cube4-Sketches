# Cube4 Sketches

This repository is a place for me to publish sketches that I have worked on for the [Freetronics 4x4x4 RGB LED Cube](http://www.freetronics.com.au/collections/kits/products/cube4-4x4x4-rgb-led-cube).

All sketches have been tested using the Arduino IDE v1.6.7 on MacOS X 10.10.

Click on any of the thumbnails to view a video of the animation.

## Non Blocking Versions
Typically sketches use delay() to add a pause between frames in an animation. The problem with this is that while the sketch is running, and particularly during a delay no other pieces of code run. This is problematic with things like serial input, as the cube will not respond to it while in a delay, meaning that the command is missed.

A different approach is to use a state machine, that is called roughly every millisecond, but only does actions if it is in the correct state, and if an appropriate amount of time has passed. This approach removes the need for a delay, and allows items like serial input to still occur.

A number of the following sketches include both the "traditional" approach using delay(), and versions that are built using a state machine.

# Installation
## Libraries
These sketches require the [Cube4 Library](https://github.com/neographophobic/Cube4) (that link is to my modified version of the library). The original version can be found at [Freetronics Cube4 Library](https://github.com/freetronics/Cube4). 

Some sketches also require a helper library that I've written. The library is available from [Cube4_ARUtils](https://github.com/neographophobic/Cube4_ARUtils).

Instructions on installing these libraries are available at the above links.

## Sketches
### Step 1: Download
* To get the latest released version, goto the [Releases](https://github.com/neographophobic/Cube4-Sketches/releases) page, and then click the "Source Code (zip)" link for the latest release.
![Download Releases Link](http://secretcode.ninja/github_readme_resources/Cube4-Sketches/Step1-Download_Release.png)

* To get the latest development version, click on the "Download ZIP" button on the Github page for this [library](https://github.com/neographophobic/Cube4-Sketches). If you are unsure which version to get, get the one from the "Releases" page as it is the latest stable release.
![Download Link](http://secretcode.ninja/github_readme_resources/Cube4-Sketches/Step1-Download.png)

### Step 2: Unzip
Once the file has downloaded, browse to it on your computer and unzip it.
![Unzip](http://secretcode.ninja/github_readme_resources/Cube4-Sketches/Step2-Unzip.png)

### Step 3: Rename and Move
Feel free to rename the newly unzipped folder to whatever you would like, and to move it to any appropriate location. From here you can double click on any of the sketches to open them in the Arduino IDE.

# Sketches
## Blank
A template I use as a starting point for new sketches. There is also a non blocking version available. To use it do a "Find and Replace" on "Blank", and then modify each occurrence as appropriate.

*There is a non blocking version of this template, and it includes the Cube4_ARUtils library (which can be removed if not required).*

## Colour Pulse
[![Colour Pulse Video](https://i.ytimg.com/s_vi/u5nLpMrX5ck/2.jpg?sqp=CKz127UF&rs=AOn4CLCInfmBBG-x3zsayztbIiBJQXqIBA&time=1454832559358)](https://youtu.be/u5nLpMrX5ck "Colour Pulse Video")

Given a colour, it will fade it out to black, and then back to the given colour. You can also control the increments that it fades in and out by.

*There is a non blocking version of this sketch. Both versions require the Cube4_ARUtils library.*

## Cube Edge
[![Colour Pulse Video](https://i.ytimg.com/s_vi/NAcZ7mlFAVk/3.jpg?sqp=CIT627UF&rs=AOn4CLCaqtHnGEmGSQrqmQhSDA_C0-9Gew&time=1454832994439)](https://youtu.be/NAcZ7mlFAVk "Cube Edge Video")

This sketch takes a starting point in one of the corners, and then branches out to the diagonally opposite corner around the edges of the cube. From each corner it reaches it goes in the three possible directions.

While I've used three points for the sketch, the code supports starting from any of the 8 corners of the cube.

*This sketch requires the Cube4_ARUtils library.*

## Expanding
[![Expanding Video](https://i.ytimg.com/s_vi/swnLhp95bLE/2.jpg?sqp=CIT627UF&rs=AOn4CLDMHyZ_o4Y-NG3vE5Q4NSiAbipxpg&time=1454833073430)](https://youtu.be/swnLhp95bLE "Expanding Video")

Starting in one of the corners, the sketch will expand out until it reaches the far corners, and then contract back to the starting point. It supports starting at any of the corners of the cube.

*This sketch requires the Cube4_ARUtils library.*

## Face Expanding
[![Face Expanding Video](https://i.ytimg.com/s_vi/5qblQ5_-b58/3.jpg?sqp=CIT627UF&rs=AOn4CLCeJa-blh4QAc0hw9MzAKlAA9Obpg&time=1454833135423)](https://youtu.be/5qblQ5_-b58 "Face Expanding Video")

This sketch is similar to the "Expanding" sketch above, but it only expands along the face of the cube. The code demonstrates the left to right movement, but also supports moving right to left, by changing the "5" to "1" in the call to faceExpand().

*This sketch requires the Cube4_ARUtils library.*

## Face Peel
[![Face Peel Video](https://i.ytimg.com/s_vi/xFN2sNZ1Xp8/3.jpg?sqp=CIT627UF&rs=AOn4CLDHR8B-sO8ypoOciI_JrJgYpR5V9w&time=1454833184929)](https://youtu.be/xFN2sNZ1Xp8 "Face Peel Video")

This sketch will diagonally fill in a face of the cube, then pull it, again diagonally to the face opposite.

*This sketch requires the Cube4_ARUtils library.*

## Face Sweep
[![Face Sweep Video](https://i.ytimg.com/s_vi/n6-5_mIZ0yU/2.jpg?sqp=CLD827UF&rs=AOn4CLCBYIXJQynI-VoyBbVvqnP_Lopajg&time=1454833233598)](https://youtu.be/n6-5_mIZ0yU "Face Sweep Video")

In this sketch, we illuminate a face, and then sweep it from that face, to another face that is connected to it like it was swinging on a hinge. 

*There is a non blocking version of this sketch.*

## Flashing Cubes
[![Flashing Cubes Video](https://i.ytimg.com/s_vi/vNLTxzmsADM/1.jpg?sqp=CLD827UF&rs=AOn4CLD5A90l7TJ4bvZssSSnQTZet-fIkw&time=1454833270652)](https://youtu.be/vNLTxzmsADM "Flashing Cubes Video")

This sketch will flash the "inner" and "outer" cubes.

*There is a non blocking version of this sketch.*

## Letters
[![Letters Video](https://i.ytimg.com/s_vi/hJnIUHWSm1Q/3.jpg?sqp=CLD827UF&rs=AOn4CLDCZiWvKlta3EPGWXig0JJEjV140w&time=1454833339424)](https://youtu.be/hJnIUHWSm1Q "Letters Video")

This sketch will attempt to draw letters or numbers on the Y 0 plane of the cube. A 4x4 grid is limiting, so some of the text isn't the clearest but it works as a proof of concept.

If you set the colour of the letters to BLACK, the sketch will pick a random colour to use for each letter of a given message.

## Looping Boxes
[![Looping Boxes Video](https://i.ytimg.com/s_vi/dJm4NXJt7sg/2.jpg?sqp=CLD827UF&rs=AOn4CLBWrltKDvSpYvCHqAkw3EG8fyydbQ&time=1454833379513)](https://youtu.be/dJm4NXJt7sg "Looping Boxes Video")

This sketch has a small inner square, and a larger outer square that is hollow. The inner square passes through the outer square, and then the squares move along a face and then the process repeats.

*There is a non blocking version of this sketch.*

## Plane Move
[![Plane Move Video](https://i.ytimg.com/s_vi/HedzrolmXtU/1.jpg?sqp=CLD827UF&rs=AOn4CLAJ9FFAvLYHUgtOPXigE0ipb9VqiQ&time=1454833418839)](https://youtu.be/HedzrolmXtU "Plane Move Video")

This sketch moves each plane from the 0 face to the 3 face and then back again.

## Random Fill
[![Random Fill Video](https://i.ytimg.com/s_vi/ATWBFI3YCsU/2.jpg?sqp=CLD827UF&rs=AOn4CLDmZ_GX0jlcKJJoUv2R9Xgb9R5t-g&time=1454833466587)](https://youtu.be/ATWBFI3YCsU "Random Fill Video")

Randomly fills the cube, one LED at a time randomly picking 1 of eight colours. It then turns the LEDS  off in the same order.

*This sketch requires the Cube4_ARUtils library.*

## Random Pull
[![Random Pull Video](https://i.ytimg.com/s_vi/Vt0Cw0ps900/1.jpg?sqp=CNz-27UF&rs=AOn4CLCMwqHd74YAXtdvFk2b90PjTHmerw&time=1454833503932)](https://youtu.be/Vt0Cw0ps900 "Random Pull Video")

This sketch lights up a face, then randomly picks LEDs and "pulls" them to the opposite face.

*This sketch requires the Cube4_ARUtils library.*

## Roaming Cubes
[![Roaming Cubes Video](https://i.ytimg.com/s_vi/vrTNoXFZjVQ/3.jpg?sqp=CNz-27UF&rs=AOn4CLC42KtTIJBEn1x9ieJzLOG6oFmFiw&time=1454833557439)](https://youtu.be/vrTNoXFZjVQ "Roaming Cubes Video")

There are 3 2x2x2 mini cubes that roam around the larger 4x4x4 cube. The mini cubes move in a random direction either left, right, back, forward, up, or down.

The movement is only allowed if there are not already 2 cubes in the destination plane, and that the destination location isn't occupied.

## Rotate Plane
[![Rotate Plane Video](https://i.ytimg.com/s_vi/fEEtLnGrUO8/1.jpg?sqp=CNz-27UF&rs=AOn4CLAlEOFGDaVEua3WdGC2xKrmYRBdnQ&time=1454833598241)](https://youtu.be/fEEtLnGrUO8 "Rotate Plane Video")

This sketch rotates a plane either horizontally or vertically in either a clockwise or anti-clockwise direction.

## Snake
[![Snake Video](https://i.ytimg.com/s_vi/xNMZk3fg6Ds/2.jpg?sqp=CNz-27UF&rs=AOn4CLBrwVXVH3sJpypyddCbNh2lqK_BfQ&time=1454833641339)](https://youtu.be/xNMZk3fg6Ds "Snake Video")

Fill the entire cube in a "snake" like pattern.

## Spiral
[![Spiral Video](https://i.ytimg.com/s_vi/9nCHRiPDjIo/2.jpg?sqp=CNz-27UF&rs=AOn4CLAxgy0tW7qbNsoheaxNwjaGBdHNwA&time=1454833690743)](https://youtu.be/9nCHRiPDjIo "Spiral Video")

This sketch draws around the outside of the cube. It supports starting on each face and working one LED at a time to the opposite face.

*There is a non blocking version of this sketch. Both versions require the Cube4_ARUtils library.*

## Splat
[![Splat Video](https://i.ytimg.com/s_vi/BCdrJ8AcWNI/2.jpg?sqp=CNz-27UF&rs=AOn4CLCaJmzC-E5tsef2L3wItaKuSQ0t0g&time=1454833733350)](https://youtu.be/BCdrJ8AcWNI "Splat Video")

This is a hard pattern to describe. It's as if there are two blobs that get thrown together in the middle, then slide down a wall to the bottom of the cube and get thrown back together. If you have a better name let me know.

*There is a non blocking version of this sketch.*

## Sweep
[![Sweep Video](https://i.ytimg.com/s_vi/7Nb7zDHjRS8/2.jpg?sqp=CNz-27UF&rs=AOn4CLDZ5FzOm040g4fFUWfmFAGhDbdc5g&time=1454833773371)](https://youtu.be/7Nb7zDHjRS8 "Sweep Video")

This sketch is a simpler version of "Rotate Plane" that only support horizontal rotation in a clockwise direction.

*There is a non blocking version of this sketch.*

## Wave
[![Wave Video](https://i.ytimg.com/s_vi/fMA8I8sZeZ4/3.jpg?sqp=CIiB3LUF&rs=AOn4CLDy4P3XkYdg4KdZjdVDdyLfwV0jyQ&time=1454833807369)](https://youtu.be/fMA8I8sZeZ4 "Wave Video")

This sketch creates a wave style motion.

*There is a non blocking version of this sketch.*

## ZigZag
[![ZigZag Video](https://i.ytimg.com/s_vi/5vz3igTS1mo/2.jpg?sqp=CIiB3LUF&rs=AOn4CLD1EXGzhCcwRPpL1WAnX4HUKkQYtA&time=1454833842605)](https://youtu.be/5vz3igTS1mo "ZigZag Video")

Creates a Zig / Zag style pattern.

*There is a non blocking version of this sketch.*

# 3rd Party Sketches
Please see the **Acknowledgments.txt** file for information on where I have sourced these from.

## Colour Fader
[![Colour Fader Video](https://i.ytimg.com/s_vi/tEd51R9H99M/2.jpg?sqp=CIiB3LUF&rs=AOn4CLAWmerd0XLLo4uxVZJevm52dHZhIQ&time=1454833937973)](https://youtu.be/tEd51R9H99M "Colour Fader Video")

Fades the cube through a series of colours. 

*This sketch is a non blocking version of the original sketch.*

## Cubes
[![Cubes Video](https://i.ytimg.com/s_vi/Ynik0h8-lxw/3.jpg?sqp=CIiB3LUF&rs=AOn4CLChGSd894xroTa49b7am8TstNvg4Q&time=1454833980150)](https://youtu.be/Ynik0h8-lxw "Cubes Video")

Demonstrates different cube styles.

*This sketch is a non blocking version of the original sketch.*

## DoubleCube
[![DoubleCube Video](https://i.ytimg.com/s_vi/CY8Hvar-fxY/1.jpg?sqp=CIiB3LUF&rs=AOn4CLAjcf0IxIdIEvBRetM3ri6VgUkNCw&time=1454834007655)](https://youtu.be/CY8Hvar-fxY "DoubleCube Video")

Places a 2x2x2 cube within the larger 4x4x4 cube, and picks random colours for both.

*This sketch is a non blocking version of the original sketch.*

## Emergency Flashing
[![Emergency Flashing Video](https://i.ytimg.com/s_vi/eIduTTMDglI/2.jpg?sqp=CIiB3LUF&rs=AOn4CLBdP2OumxEL8VPl92WRIczQdfeEIA&time=1454834058578)](https://youtu.be/eIduTTMDglI "Emergency Flashing Video")

Simulates the red / blue flashing lights of an emergency vehicle.

*There is a "traditional" and non blocking version of the original sketch.*

## Heartbeat
[![Heartbeat Video](https://i.ytimg.com/s_vi/zVYgmBottPg/2.jpg?sqp=CIiB3LUF&rs=AOn4CLBsZryiK4CbHgdnQaC2Y15UlZwLnQ&time=1454834096559)](https://youtu.be/zVYgmBottPg "Heartbeat Video")

Simulates a heart beat.

*This sketch is a non blocking version of the original sketch, and requires the Cube4_ARUtils library.*

## LaserShow
[![LaserShow Video](https://i.ytimg.com/s_vi/0yZ59lE_d4Q/2.jpg?sqp=CLSD3LUF&rs=AOn4CLDyBxxOXTsUaTd5k7JpMNstexncnw&time=1454834132631)](https://youtu.be/0yZ59lE_d4Q "LaserShow Video")

Draw a series of laser lights from the bottom corners, then from the top corners. I've removed the second part of the original sketch that resulted in a solid red cube.

*This sketch is a non blocking version of the original sketch.*

## RainStorm
[![RainStorm Video](https://i.ytimg.com/s_vi/MEfSjLcVV6k/2.jpg?sqp=CLSD3LUF&rs=AOn4CLC_M35h1N0wSuidBRoXfjVph8rZ1w&time=1454834175182)](https://youtu.be/MEfSjLcVV6k "RainStorm Video")

Simulates a rain storm, with the option of clouds and lightning.

*This sketch is a non blocking version of the original sketch.*

## Random Colours
[![Random Colour Video](https://i.ytimg.com/s_vi/LN4DCuBSfx0/2.jpg?sqp=CLSD3LUF&rs=AOn4CLB17U_snwPntm81HfAprL3lHQg9_Q&time=1454834215349)](https://youtu.be/LN4DCuBSfx0 "Random Colour Video") [![Random Pastels Video](https://i.ytimg.com/s_vi/yDMl6RwojzI/2.jpg?sqp=CLSD3LUF&rs=AOn4CLCc2pBcMrBWtAbe6QdVx8LUJZxygw&time=1454834253180)](https://youtu.be/yDMl6RwojzI "Random Pastels Video") [![Random Primaries Video](https://i.ytimg.com/s_vi/GsypDmS23kE/2.jpg?sqp=CLSD3LUF&rs=AOn4CLB56W4Ikq0w3Tz9y7txT0HSdNOE8A&time=1454834283813)](https://youtu.be/GsypDmS23kE "Random Primaries Video")

Set each LED in the cube to a constantly changing random colour. There are three different options (due to combining the 3 Random Colour example sketches). Only one option can be used at a time.

* Random Colour = Any possible colour
* Random Pastels = Any pastel colour
* Random Primaries = Red, Green, or Blue

*This sketch is a non blocking version of the original sketches.*

## Test Pattern
[![Step Through LEDs Video](https://i.ytimg.com/s_vi/fW_JzTfJDvk/3.jpg?sqp=CLSD3LUF&rs=AOn4CLBB7EX2xrW-VDEUQbnbK-7tWIdK8Q&time=1454834373227)](https://youtu.be/fW_JzTfJDvk "Step Through LEDs Video") [![Cycle Cube Colours Video](https://i.ytimg.com/s_vi/0nJPBmKu3tc/2.jpg?sqp=COCF3LUF&rs=AOn4CLComKK4DKJNHPw9wGg1ubPExoxfaQ&time=1454834422388)](https://youtu.be/0nJPBmKu3tc "Cycle Cube Colours Video") [![Fade White Video](https://i.ytimg.com/s_vi/Taa_6GIyCm8/2.jpg?sqp=COCF3LUF&rs=AOn4CLBo0xSRXOdtDzBFya0HNG5vAGM6qQ&time=1454834461487)](https://youtu.be/Taa_6GIyCm8 "Fade White Video") [![Random Pastels Video](https://i.ytimg.com/s_vi/4Hy90WcWzXY/2.jpg?sqp=COCF3LUF&rs=AOn4CLA62P2DdMJUYZyPxPK39JLattuV_A&time=1454834506381)](https://youtu.be/4Hy90WcWzXY "Random Pastels Video")

The test pattern that ships with each cube, with each "stage" of it broken up into a different function. Only one option can be used at a time.

* Step Through LEDs
* Cycle Cube Colours
* Fade White
* Random Pastels (same as from Random Colours above)

*This sketch is a non blocking version of the original sketch, and requires the Cube4_ARUtils library.*
