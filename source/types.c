#include "types.h"

int YGL_GetDistance(YGL_Vec2 start, YGL_Vec2 end) {
	YGL_FVec2 difference = (YGL_FVec2) {
		fabsf(((float) start.x) - ((float) end.x)),
		fabsf(((float) start.y) - ((float) end.y))
	};

	return (int) sqrtf(powf(difference.x, 2) + powf(difference.y, 2));
}

float YGL_Lerp(int start, int end, float t) {
	return (int) ((float) start + t * ((float) end - (float) start));
}

YGL_FVec2 YGL_LerpVec2(YGL_Vec2 start, YGL_Vec2 end, float t) {
	return (YGL_FVec2) {
		YGL_Lerp(start.x, end.x, t),
		YGL_Lerp(start.y, end.y, t)
	};
}
