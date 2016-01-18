/*
 *  File:		Utils.h
 *  Purpose:	Header file for helper functions for Freetronics 4x4x4 RGB LED Cube
 *  Author:		Adam Reed (adam@secretcode.ninja)
 *  Licence:	BSD 3-Clause Licence
 */

// Ensure that this header file is only processed once, regardless of how
// many time it is included
#ifndef Utils_h
#define Utils_h

// Include for Arduino Library
#include "Arduino.h"

// Include for Cube Library
#include "Cube.h"

/* Functions to convert from RGB to HSV and back, adapted from the accepted
 * answer to http://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
 */
struct hsv {
  double h;       // angle in degrees
  double s;       // percent
  double v;       // percent
};
struct hsv rgb2hsv(rgb_t in);
rgb_t hsv2rgb(struct hsv in);


#endif
