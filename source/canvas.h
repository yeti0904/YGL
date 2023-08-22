#ifndef YGL_CANVAS_H
#define YGL_CANVAS_H

#include "types.h"
#include "components.h"

typedef struct YGL_Colour {
	uint8_t r, g, b, a;
} YGL_Colour;

typedef uint32_t YGL_Pixel;

YGL_Pixel  YGL_ColourToPixel(YGL_Colour colour);
YGL_Colour YGL_PixelToColour(YGL_Pixel pixel);
YGL_Colour YGL_InvertColour(YGL_Colour colour);
YGL_Colour YGL_AndColour(YGL_Colour colour1, YGL_Colour colour2);

typedef struct YGL_Canvas {
	YGL_Pixel* pixels;
	YGL_Vec2   size;
} YGL_Canvas;

YGL_Canvas* YGL_CreateCanvas(int w, int h);
void        YGL_FreeCanvas(YGL_Canvas* canvas);

// misc
YGL_Pixel* YGL_GetCanvasPixel(YGL_Canvas* canvas, YGL_Vec2 pos);
bool       YGL_ResizeCanvas(YGL_Canvas* canvas, YGL_Vec2 size);

// drawing functions
void YGL_ClearCanvas(YGL_Canvas* canvas, YGL_Colour colour);
void YGL_DrawPixel(YGL_Canvas* canvas, YGL_Vec2 pos, YGL_Colour colour);
void YGL_DrawRawPixel(YGL_Canvas* canvas, YGL_Vec2 pos, YGL_Pixel pixel);
void YGL_FillRect(YGL_Canvas* canvas, YGL_Rect rect, YGL_Colour colour);
void YGL_DrawLine(
	YGL_Canvas* canvas, YGL_Vec2 start, YGL_Vec2 end, YGL_Colour colour
);
void YGL_BlitCanvas(
	YGL_Canvas* canvas, YGL_Rect* psrc, YGL_Rect* pdest, YGL_Canvas* from
);

#endif
