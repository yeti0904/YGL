#ifndef YGL_TYPES_H
#define YGL_TYPES_H

#include "math.h"
#include "components.h"

typedef struct YGL_Vec2 {
	int x, y;
} YGL_Vec2;

typedef struct YGL_Vec3 {
	int x, y, z;
} YGL_Vec3;

typedef struct YGL_FVec2 {
	double x, y;
} YGL_FVec2;

typedef struct YGL_FVec3 {
	double x, y, z;
} YGL_FVec3;

typedef struct YGL_Rect {
	int x, y, w, h;
} YGL_Rect;

typedef struct YGL_FRect {
	double x, y, w, h;
} YGL_FRect;

int       YGL_GetDistance(YGL_Vec2 start, YGL_Vec2 end);
YGL_FVec2 YGL_LerpVec2(YGL_Vec2 start, YGL_Vec2 end, double t);
double    YGL_GetAngle(YGL_Vec2 p1, YGL_Vec2 p2);
YGL_FVec2 YGL_Vec2ToFloat(YGL_Vec2 vec2);
YGL_Vec2  YGL_FVec2ToInt(YGL_FVec2 vec2);
bool      YGL_CompareVec2(YGL_Vec2 v1, YGL_Vec2 v2);
YGL_FVec2 YGL_RotatePoint(YGL_FVec2 point, YGL_FVec2 center, double angle);
YGL_Rect  YGL_FRectToRect(YGL_FRect rect);
bool      YGL_FRectCollides(YGL_FRect rect1, YGL_FRect rect2);
bool      YGL_RectCollides(YGL_Rect rect1, YGL_Rect rect2);

#endif
