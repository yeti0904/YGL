#ifndef YGL_TYPES_H
#define YGL_TYPES_H

#include "components.h"

typedef struct YGL_Vec2 {
	int x, y;
} YGL_Vec2;

typedef struct YGL_FVec2 {
	float x, y;
} YGL_FVec2;

int       YGL_GetDistance(YGL_Vec2 start, YGL_Vec2 end);
float     YGL_Lerp(int start, int end, float t);
YGL_FVec2 YGL_LerpVec2(YGL_Vec2 start, YGL_Vec2 end, float t);

typedef struct YGL_Rect {
	int x, y, w, h;
} YGL_Rect;

#endif
