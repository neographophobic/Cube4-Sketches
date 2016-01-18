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

struct hsv {
  double h;       // angle in degrees
  double s;       // percent
  double v;       // percent
};

struct hsv convertHexToHSV(unsigned long theColour);
struct hsv rgb2hsv(rgb_t in);
rgb_t hsv2rgb(struct hsv in)


#endif
