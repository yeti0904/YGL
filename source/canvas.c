#include "canvas.h"
#include "error.h"

YGL_Pixel YGL_ColourToPixel(YGL_Colour colour) {
	return colour.r | (colour.g << 8) | (colour.b << 16) | (colour.a << 24);
}

YGL_Colour YGL_PixelToColour(YGL_Pixel pixel) {
	return (YGL_Colour) {
		 pixel & 0x000000FF,
		(pixel & 0x0000FF00) >> 8,
		(pixel & 0x00FF0000) >> 16,
		(pixel & 0xFF000000) >> 24
	};
}

YGL_Colour YGL_InvertColour(YGL_Colour colour) {
	return (YGL_Colour) {
		255 - colour.r,
		255 - colour.g,
		255 - colour.b,
		255
	};
}

YGL_Colour YGL_AndColour(YGL_Colour colour1, YGL_Colour colour2) {
	return (YGL_Colour) {
		colour1.r & colour2.r,
		colour1.g & colour2.g,
		colour1.b & colour2.b,
		255
	};
}

YGL_Canvas* YGL_CreateCanvas(int w, int h) {
	YGL_Canvas* ret = (YGL_Canvas*) malloc(sizeof(YGL_Canvas));

	if (ret == NULL) {
		YGL_SetError("malloc failed");
		YGL_SetErrorSource(YGL_ERRORSOURCE_INTERNAL);
		return NULL;
	}

	ret->size   = (YGL_Vec2) {w, h};
	ret->pixels = (YGL_Pixel*) malloc(w * h * sizeof(YGL_Pixel));

	if (ret->pixels == NULL) {
		YGL_SetError("malloc failed");
		YGL_SetErrorSource(YGL_ERRORSOURCE_INTERNAL);
		free(ret);
		return NULL;
	}

	return ret;
}

void YGL_FreeCanvas(YGL_Canvas* canvas) {
	free(canvas->pixels);
	free(canvas);
}

YGL_Pixel* YGL_GetCanvasPixel(YGL_Canvas* canvas, YGL_Vec2 pos) {
	if (
		(pos.x < 0) ||
		(pos.y < 0) ||
		(pos.x >= canvas->size.x) ||
		(pos.y >= canvas->size.y)
	) {
		YGL_SetError("pixel out of bounds");
		YGL_SetErrorSource(YGL_ERRORSOURCE_INTERNAL);
		return NULL;
	}

	return &canvas->pixels[(pos.y * canvas->size.x) + pos.x];
}

bool YGL_ResizeCanvas(YGL_Canvas* canvas, YGL_Vec2 size) {
	YGL_Pixel* pixels = (YGL_Pixel*) malloc(size.x * size.y * sizeof(YGL_Pixel));

	if (pixels == NULL) {
		YGL_SetError("malloc failed");
		YGL_SetErrorSource(YGL_ERRORSOURCE_INTERNAL);
		return false;
	}

	for (int x = 0; x < canvas->size.x; ++ x) {
		if (x >= size.x) {
			break;
		}
	
		for (int y = 0; y < canvas->size.y; ++ y) {
			if (y >= size.y) {
				break;
			}

			pixels[(y * size.x) + x] = canvas->pixels[(y * canvas->size.x) + x];
		}
	}

	free(canvas->pixels);
	canvas->pixels = pixels;
	canvas->size   = size;

	return true;
}

void YGL_ClearCanvas(YGL_Canvas* canvas, YGL_Colour colour) {
	size_t    area  = canvas->size.x * canvas->size.y;
	YGL_Pixel pixel = YGL_ColourToPixel(colour);

	for (size_t i = 0; i < area; ++ i) {
		canvas->pixels[i] = pixel;
	}
}

void YGL_DrawPixel(YGL_Canvas* canvas, YGL_Vec2 pos, YGL_Colour colour) {
	YGL_DrawRawPixel(canvas, pos, YGL_ColourToPixel(colour));
}

void YGL_DrawRawPixel(YGL_Canvas* canvas, YGL_Vec2 pos, YGL_Pixel pixel) {
	if (
		(pos.x < 0) ||
		(pos.y < 0) ||
		(pos.x >= canvas->size.x) ||
		(pos.y >= canvas->size.y)
	) {
		return;
	}

	uint8_t alpha = (pixel & 0xFF000000) >> 24;
	if (alpha != 255) {
		if (alpha == 0) {
			return;
		}

		double t = ((double) alpha) / 255.0;

		YGL_Colour old = YGL_PixelToColour(
			canvas->pixels[(pos.y * canvas->size.x) + pos.x]
		);
		YGL_Colour colour = YGL_PixelToColour(pixel);
		colour.r = YGL_Lerp(old.r, colour.r, t);
		colour.g = YGL_Lerp(old.g, colour.g, t);
		colour.b = YGL_Lerp(old.b, colour.b, t);

		pixel = YGL_ColourToPixel(colour);
	}

	canvas->pixels[(pos.y * canvas->size.x) + pos.x] = pixel;
}

void YGL_FillRect(YGL_Canvas* canvas, YGL_Rect rect, YGL_Colour colour) {
	YGL_Pixel pixel = YGL_ColourToPixel(colour);

	for (int x = rect.x; x < rect.x + rect.w; ++ x) {
		for (int y = rect.y; y < rect.y + rect.h; ++ y) {
			YGL_DrawRawPixel(canvas, (YGL_Vec2) {x, y}, pixel);
		}
	}
}

void YGL_DrawLine(
	YGL_Canvas* canvas, YGL_Vec2 start, YGL_Vec2 end, YGL_Colour colour
) {
	YGL_Pixel pixel  = YGL_ColourToPixel(colour);
	int       length = YGL_GetDistance(start, end) + 10;

	start.x = MAX(start.x, 0);
	start.y = MAX(start.y, 0);
	end.x   = MIN(end.x,   canvas->size.x);
	end.y   = MIN(end.y,   canvas->size.y);

	for (int i = 0; i < length; ++ i) {
		float     t            = i == 0? 0.0 : (float) i / (float) length;
		YGL_FVec2 interpolated = YGL_LerpVec2(start, end, t);
		
		YGL_Vec2 point = (YGL_Vec2) {
			round(interpolated.x), round(interpolated.y)
		};

		YGL_DrawRawPixel(canvas, point, pixel);
	}
}

void YGL_BlitCanvas(
	YGL_Canvas* canvas, YGL_Rect* psrc, YGL_Rect* pdest, YGL_Canvas* from
) {
	YGL_Rect src;

	if (psrc == NULL) {
		src = (YGL_Rect) {0, 0, from->size.x, from->size.y};
	}
	else {
		src = *psrc;
	}

	YGL_Rect dest;

	if (pdest == NULL) {
		dest = (YGL_Rect) {0, 0, canvas->size.x, canvas->size.y};
	}
	else {
		dest = *pdest;
	}

	for (int y = 0; y < dest.h; ++ y) {
		YGL_Rect pos;
		pos.y = dest.y + y;
		
		if (pos.y < 0) {
			continue;
		}
		else if (pos.y >= canvas->size.x) {
			break;
		}

		for (int x = 0; x < dest.w; ++ x) {
			pos.x = dest.x + x;
			
			if (pos.x < 0) {
				continue;
			}
			if (pos.x >= canvas->size.x) {
				break;
			}

			YGL_Vec2 srcPos = (YGL_Vec2) {
				floor((float) x / dest.w * src.w + src.x),
				floor((float) y / dest.h * src.h + src.y)
			};

			uint32_t pixel = *YGL_GetCanvasPixel(
				from, (YGL_Vec2) {srcPos.x, srcPos.y}
			);
			if ((pixel & 0xFF000000) >> 24 == 0) {
				continue;
			}

			YGL_DrawRawPixel(canvas, (YGL_Vec2) {pos.x, pos.y}, pixel);
		}
	}
}
