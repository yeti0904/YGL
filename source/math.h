#ifndef YGL_MATH_H
#define YGL_MATH_H

#include "components.h"

double YGL_Lerp(int start, int end, double t);
double YGL_RadiansToDegrees(double rad);
double YGL_DegreesToRadians(double deg);
double YGL_ClampFloat(double start, double end, double value);
double YGL_CosDeg(double deg);
double YGL_SinDeg(double deg);

#endif
