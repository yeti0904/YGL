#include "SDL.h"
#include "../error.h"

#ifdef YGL_USE_SDL1

static bool YGL_SDL1_Init(void) {
	int res = SDL_Init(SDL_INIT_VIDEO);

	if (res < 0) {
		YGL_SetError("SDL error");
		YGL_SetErrorSource(YGL_ERRORSOURCE_BACKEND);
	}

	return res == 0;
}

static void YGL_SDL1_Free(void) {
	SDL_Quit();
}

static YGL_BackendWindow YGL_SDL1_InitWindow(const char* name, int w, int h) {
	YGL_BackendWindow ret;
	ret.null = true;

	ret.sdlSurface = SDL_SetVideoMode(
		w, h, 24, SDL_SWSURFACE | SDL_RESIZABLE
	);

	if (ret.sdlSurface == NULL) {
		YGL_SetError("Failed to set SDL video mode");
		YGL_SetErrorSource(YGL_ERRORSOURCE_BACKEND);
		free(ret);
		return ret;
	}
	
	SDL_WM_SetCaption(name, "");

	ret.null = false;
	return ret;
}

static void YGL_SDL1_FreeWindow(YGL_BackendWindow* window) {
	SDL_FreeSurface(window->sdlSurface);
}

static bool YGL_SDL1_DrawWindow(YGL_Canvas* canvas, YGL_BackendWindow* window) {
	if (SDL_MUSTLOCK(window->sdlSurface)) {
		if (SDL_LockSurface(window->sdlSurface) < 0) {
			YGL_SetError("Failed to lock SDL surface");
			YGL_SetErrorSource(YGL_ERRORSOURCE_BACKEND);
			return false;
		}
	}
	
	for (int x = 0; x < window->canvas->size.x; ++ x) {
		for (int y = 0; y < window->canvas->size.y; ++ y) {
			uint8_t* pixels = (uint8_t*) window->sdlSurface->pixels;
			uint8_t* pixel  = pixels + y * window->sdlSurface->pitch + x * 3;

			uint32_t colour = *YGL_GetCanvasPixel(
				window->canvas, (YGL_Vec2) {x, y}
			);
			
			YGL_Colour rgb      = YGL_PixelToColour(colour);
			uint32_t   sdlPixel = SDL_MapRGB(
				window->sdlSurface->format, rgb.r, rgb.g, rgb.b
			);

			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				pixel[0] = (sdlPixel >> 16) & 0xff;
				pixel[1] = (sdlPixel >> 8) & 0xff;
				pixel[2] = sdlPixel & 0xff;
			}
			else {
				pixel[0] = sdlPixel & 0xff;
				pixel[1] = (sdlPixel >> 8) & 0xff;
				pixel[2] = (sdlPixel >> 16) & 0xff;
			}
		}
	}

	if (SDL_MUSTLOCK(window->sdlSurface)) {
		SDL_UnlockSurface(window->sdlSurface);
	}
}

static char* YGL_SDL1_GetError(void) {
	return (char*) SDL_GetError();
}

YGL_Backend YGL_CreateSDLBackend(void) {
	YGL_Backend backend;

	backend.null       = false;
	backend.init       = YGL_SDL1_Init;
	backend.free       = YGL_SDL1_Free;
	backend.initWindow = YGL_SDL1_InitWindow;
	backend.freeWindow = YGL_SDL1_FreeWindow;
	backend.drawWindow = YGL_SDL1_DrawWindow;
	backend.getError   = YGL_SDL1_GetError;

	return backend;
}

#endif
