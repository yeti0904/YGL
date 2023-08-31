#include "error.h"
#include "palette.h"

YGL_Palette* YGL_CreatePalette(size_t n) {
	YGL_Palette* ret = malloc(sizeof(YGL_Palette));

	if (ret == NULL) {
		YGL_SetError("malloc failed");
		YGL_SetErrorSource(YGL_ERRORSOURCE_INTERNAL);
		return NULL;
	}

	ret->n       = n;
	ret->colours = calloc(n, sizeof(YGL_Colour));

	if (ret->colours == NULL) {
		free(ret);
		YGL_SetError("calloc failed");
		YGL_SetErrorSource(YGL_ERRORSOURCE_INTERNAL);
		return NULL;
	}
	
	return ret;
}

void YGL_FreePalette(YGL_Palette* palette) {
	free(palette->colours);
	free(palette);
}

YGL_Colour YGL_PaletteIndexToColour(uint32_t index) {
	return YGL_PixelToColour(index);
}

bool YGL_PalettedCanvasToRGB(YGL_Canvas* canvas, YGL_Palette* palette) {
	for (int x = 0; x < canvas->size.x; ++ x) {
		for (int y = 0; y < canvas->size.y; ++ y) {
			uint32_t* pixel = YGL_GetCanvasPixel(canvas, (YGL_Vec2) {x, y});

			if (*pixel >= palette->n) {
				YGL_SetError("Out of bounds palette index");
				YGL_SetErrorSource(YGL_ERRORSOURCE_INTERNAL);
				return false;
			}

			*pixel = YGL_ColourToPixel(palette->colours[*pixel]);
		}
	}

	return true;
}

void YGL_RGBCanvasToPaletted(YGL_Canvas* canvas, YGL_Palette* palette) {
	for (int x = 0; x < canvas->size.x; ++ x) {
		for (int y = 0; y < canvas->size.y; ++ y) {
			uint32_t closestColour      = 0;
			int      smallestDifference = 0xFFFF;

			YGL_Colour thisPixel = YGL_PixelToColour(
				*YGL_GetCanvasPixel(canvas, (YGL_Vec2) {x, y})
			);
			
			for (size_t i = 0; i < palette->n; ++ i) {
				int difference = YGL_ColourDifference(
					palette->colours[i], thisPixel
				);

				if (difference < smallestDifference) {
					smallestDifference = difference;
					closestColour      = i;
				}
			}

			*YGL_GetCanvasPixel(canvas, (YGL_Vec2) {x, y}) = closestColour;
		}
	}
}
