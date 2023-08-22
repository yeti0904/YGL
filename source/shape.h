#ifndef YGL_SHAPE_H
#define YGL_SHAPE_H

#include "components.h"
#include "canvas.h"

typedef struct YGL_Shape {
	YGL_FVec2* points;
	size_t     n;
} YGL_Shape;

typedef struct YGL_3DShape {
	YGL_FVec3* points;
	size_t     n;
} YGL_3DShape;

YGL_Shape* YGL_CreateShape(size_t n);
YGL_Shape  YGL_CreateStaticShape(size_t n, YGL_FVec2* points);
void       YGL_FreeShape(YGL_Shape* shape);
void       YGL_DrawShape(
	YGL_Canvas* canvas, YGL_Shape* shape, YGL_Colour colour
);
YGL_Shape*  YGL_RectToShape(YGL_Rect rect);
YGL_Shape*  YGL_CreateTriangle(YGL_FVec2 p1, YGL_FVec2 p2, YGL_FVec2 p3);
YGL_FVec2   YGL_GetTriangleCenter(YGL_Shape* shape);
void        YGL_MoveShape(YGL_Shape* shape, YGL_FVec2 offset);
void        YGL_RotateShape(YGL_Shape* shape, YGL_FVec2 origin, double deg);

// dont use this stuff!!
YGL_3DShape* YGL_Create3DShape(size_t n);
void         YGL_Free3DShape(YGL_Shape* shape);
void         YGL_Draw3DPlane(
	YGL_Canvas* canvas, YGL_3DShape* shape, YGL_Colour colour
);
void YGL_Move3DShape(YGL_3DShape* shape, YGL_FVec3 offset);
void YGL_Spin3DShape(YGL_3DShape* shape, YGL_FVec2 origin, double deg);

#endif
