/*
 *  File:		Utils.cpp
 *  Purpose:	Helper functions for Freetronics 4x4x4 RGB LED Cube
 *  Author:		Adam Reed (adam@secretcode.ninja)
 *  Licence:	BSD 3-Clause Licence
 */

// Include for Arduino Library
#include "Arduino.h"

// Include for Cube Library
#include "Cube.h"

// Include the header file for these functions
#include "Utils.h"

/* Functions to convert from RGB to HSV and back, adapted from the accepted
 * answer to http://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
 */

// rgb2hsv: Convert a RGB colour, into HSV
struct hsv rgb2hsv(rgb_t in)
{
  struct hsv out;
  double min, max, delta;

  min = in.color[0] < in.color[1] ? in.color[0] : in.color[1];
  min = min  < in.color[2] ? min  : in.color[2];

  max = in.color[0] > in.color[1] ? in.color[0] : in.color[1];
  max = max  > in.color[2] ? max  : in.color[2];

  out.v = max;                                // v
  delta = max - min;
  if (delta < 0.00001)
  {
    out.s = 0;
    out.h = 0; // undefined, maybe nan?
    return out;
  }
  if ( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
    out.s = (delta / max);                  // s
  } else {
    // if max is 0, then r = g = b = 0
    // s = 0, v is undefined
    out.s = 0.0;
    out.h = NAN;                            // its now undefined
    return out;
  }
  if ( in.color[0] >= max )                          // > is bogus, just keeps compilor happy
    out.h = ( in.color[1] - in.color[2] ) / delta;        // between yellow & magenta
  else if ( in.color[1] >= max )
    out.h = 2.0 + ( in.color[2] - in.color[0] ) / delta;  // between cyan & yellow
  else
    out.h = 4.0 + ( in.color[0] - in.color[1] ) / delta;  // between magenta & cyan

  out.h *= 60.0;                              // degrees

  if ( out.h < 0.0 )
    out.h += 360.0;

  return out;
}

// hsv2rgb: Convert a HSV colour, into RGB
rgb_t hsv2rgb(struct hsv in)
{
  double      hh, p, q, t, ff;
  long        i;
  rgb_t         out;

  if (in.s <= 0.0) {      // < is bogus, just shuts up warnings
    out.color[0] = in.v;
    out.color[1] = in.v;
    out.color[2] = in.v;
    return out;
  }
  hh = in.h;
  if (hh >= 360.0) hh = 0.0;
  hh /= 60.0;
  i = (long)hh;
  ff = hh - i;
  p = in.v * (1.0 - in.s);
  q = in.v * (1.0 - (in.s * ff));
  t = in.v * (1.0 - (in.s * (1.0 - ff)));

  switch (i) {
    case 0:
      out.color[0] = in.v;
      out.color[1] = t;
      out.color[2] = p;
      break;
    case 1:
      out.color[0] = q;
      out.color[1] = in.v;
      out.color[2] = p;
      break;
    case 2:
      out.color[0] = p;
      out.color[1] = in.v;
      out.color[2] = t;
      break;

    case 3:
      out.color[0] = p;
      out.color[1] = q;
      out.color[2] = in.v;
      break;
    case 4:
      out.color[0] = t;
      out.color[1] = p;
      out.color[2] = in.v;
      break;
    case 5:
    default:
      out.color[0] = in.v;
      out.color[1] = p;
      out.color[2] = q;
      break;
  }
  return out;
}
