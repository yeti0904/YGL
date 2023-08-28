#include "types.h"

int YGL_GetDistance(YGL_Vec2 start, YGL_Vec2 end) {
	YGL_FVec2 difference = (YGL_FVec2) {
		fabsf(((float) start.x) - ((float) end.x)),
		fabsf(((float) start.y) - ((float) end.y))
	};

	return (int) sqrtf(powf(difference.x, 2) + powf(difference.y, 2));
}

float YGL_Lerp(int start, int end, double t) {
	return (int) ((double) start + t * ((double) end - (double) start));
}

YGL_FVec2 YGL_LerpVec2(YGL_Vec2 start, YGL_Vec2 end, double t) {
	return (YGL_FVec2) {
		YGL_Lerp(start.x, end.x, t),
		YGL_Lerp(start.y, end.y, t)
	};
}

double YGL_RadiansToDegrees(double rad) {
	return rad * 180 / M_PI;
}

double YGL_DegreesToRadians(double deg) {
	return deg * (M_PI / 180);
}

double YGL_GetAngle(YGL_Vec2 p1, YGL_Vec2 p2) {
	float angle = atan2(p1.y - p2.y, p1.x - p2.x);

	return YGL_RadiansToDegrees(angle);
}

YGL_FVec2 YGL_Vec2ToFloat(YGL_Vec2 vec2) {
	return (YGL_FVec2) {
		(float) vec2.x, (float) vec2.y
	};
}

YGL_Vec2 YGL_FVec2ToInt(YGL_FVec2 vec2) {
	return (YGL_Vec2) {
		(int) vec2.x, (int) vec2.y
	};
}

bool YGL_CompareVec2(YGL_Vec2 v1, YGL_Vec2 v2) {
	return (
		(v1.x == v2.x) &&
		(v1.y == v2.y)
	);
}

YGL_FVec2 YGL_RotatePoint(YGL_FVec2 point, YGL_FVec2 center, double angle) {
	YGL_FVec2 result;
	double cosA = cos(YGL_DegreesToRadians(angle));
	double sinA = sin(YGL_DegreesToRadians(angle));

	// Translate point so that center becomes the origin
	point.x -= center.x;
	point.y -= center.y;

	// Perform the rotation without rounding
	result.x = point.x * cosA - point.y * sinA;
	result.y = point.x * sinA + point.y * cosA;

	// Translate the point back to its original position
	result.x += center.x;
	result.y += center.y;

	return result;
}

YGL_Rect YGL_FRectToRect(YGL_FRect rect) {
	return (YGL_Rect) {
		(int) rect.x, (int) rect.y, (int) rect.w, (int) rect.h
	};
}

bool YGL_FRectCollides(YGL_FRect rect1, YGL_FRect rect2) {
	return
		(
			(rect1.x + rect1.w >= rect2.x) &&
			(rect2.x + rect2.w >= rect1.x)
		) &&
		(
			(rect1.y + rect1.h >= rect2.y) &&
			(rect2.y + rect2.h >= rect1.y)
		);
}

bool YGL_RectCollides(YGL_Rect rect1, YGL_Rect rect2) {
	return
		(
			(rect1.x + rect1.w >= rect2.x) &&
			(rect2.x + rect2.w >= rect1.x)
		) &&
		(
			(rect1.y + rect1.h >= rect2.y) &&
			(rect2.y + rect2.h >= rect1.y)
		);
}
