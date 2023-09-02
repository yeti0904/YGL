#include "math.h"

double YGL_Lerp(int start, int end, double t) {
	return (int) ((double) start + t * ((double) end - (double) start));
}

double YGL_RadiansToDegrees(double rad) {
	return rad * 180 / M_PI;
}

double YGL_DegreesToRadians(double deg) {
	return deg * (M_PI / 180);
}

double YGL_ClampFloat(double start, double end, double value) {
	// https://stackoverflow.com/a/16659263/12577005
	const double t = value < start? start : value;
	return t > end? end : t;
}
