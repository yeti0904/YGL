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
int        YGL_ColourDifference(YGL_Colour colour1, YGL_Colour colour2);

typedef struct YGL_Canvas {
	YGL_Pixel* pixels;
	YGL_Vec2   size;
	bool       ignoreRGB; // set if you're using a paletted canvas
} YGL_Canvas;

YGL_Canvas* YGL_CreateCanvas(int w, int h);
void        YGL_FreeCanvas(YGL_Canvas* canvas);

// misc
YGL_Pixel* YGL_GetCanvasPixel(YGL_Canvas* canvas, YGL_Vec2 pos);
bool       YGL_ResizeCanvas(YGL_Canvas* canvas, YGL_Vec2 size);

// drawing functions
void YGL_ClearCanvas(YGL_Canvas* canvas, YGL_Colour colour);
bool YGL_DrawPixel(YGL_Canvas* canvas, YGL_Vec2 pos, YGL_Colour colour);
bool YGL_DrawRawPixel(YGL_Canvas* canvas, YGL_Vec2 pos, YGL_Pixel pixel);
void YGL_DrawRect(YGL_Canvas* canvas, YGL_Rect rect, YGL_Colour colour);
void YGL_FillRect(YGL_Canvas* canvas, YGL_Rect rect, YGL_Colour colour);
void YGL_DrawLine(
	YGL_Canvas* canvas, YGL_Vec2 start, YGL_Vec2 end, YGL_Colour colour
);
void YGL_DrawVLine(
	YGL_Canvas* canvas, YGL_Vec2 start, int length, YGL_Colour colour
);
void YGL_DrawHLine(
	YGL_Canvas* canvas, YGL_Vec2 start, int length, YGL_Colour colour
);
void YGL_BlitCanvas(
	YGL_Canvas* canvas, YGL_Rect* psrc, YGL_Rect* pdest, YGL_Canvas* from
);
int         YGL_CanvasArea(YGL_Canvas* canvas);
YGL_Canvas* YGL_CloneCanvas(YGL_Canvas* canvas);
YGL_Canvas* YGL_CropCanvas(YGL_Canvas* canvas, YGL_Rect crop);

#endif
