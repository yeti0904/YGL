#ifndef YGL_PALETTE_H
#define YGL_PALETTE_H

#include "canvas.h"
#include "components.h"

// idk if this works

typedef struct YGL_Palette {
	YGL_Colour* colours;
	size_t      n;
} YGL_Palette;

YGL_Palette* YGL_CreatePalette(size_t n);
void         YGL_FreePalette(YGL_Palette* palette);
YGL_Colour   YGL_PaletteIndexToColour(uint32_t index);
bool         YGL_PalettedCanvasToRGB(YGL_Canvas* canvas, YGL_Palette* palette);
void         YGL_RGBCanvasToPaletted(YGL_Canvas* canvas, YGL_Palette* palette);

#endif
