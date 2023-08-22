#include "window.h"
#include "error.h"

YGL_Window* YGL_CreateWindow(const char* name, int w, int h) {
	YGL_Window* ret = (YGL_Window*) malloc(sizeof(YGL_Window));

	if (ret == NULL) {
		YGL_SetError("malloc failed");
		return NULL;
	}

	#if defined(YGL_USE_SDL)
		ret->sdlWindow = SDL_CreateWindow(
			name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h,
			SDL_WINDOW_RESIZABLE
		);

		if (ret->sdlWindow == NULL) {
			YGL_SetError("Failed to create SDL window");
			free(ret);
			return NULL;
		}

		ret->sdlRenderer = SDL_CreateRenderer(
			ret->sdlWindow, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
		);

		if (ret->sdlRenderer == NULL) {
			YGL_SetError("Failed to create SDL renderer");
			free(ret);
			return NULL;
		}

		ret->sdlTexture = SDL_CreateTexture(
			ret->sdlRenderer, SDL_PIXELFORMAT_ABGR8888,
			SDL_TEXTUREACCESS_STREAMING, w, h
		);

		if (ret->sdlTexture == NULL) {
			YGL_SetError("Failed to create SDL texture");
			free(ret);
			return NULL;
		}
	#elif defined(YGL_USE_SDL1)
		ret->sdlSurface = SDL_SetVideoMode(
			w, h, 24, SDL_SWSURFACE | SDL_RESIZABLE
		);

		if (ret->sdlSurface == NULL) {
			YGL_SetError("Failed to set SDL video mode");
			free(ret);
			return NULL;
		}
		
		SDL_WM_SetCaption(name, "");
	#endif

	ret->canvas = YGL_CreateCanvas(w, h);

	if (ret->canvas == NULL) {
		free(ret);
		return NULL;
	}

	return ret;
}

void YGL_FreeWindow(YGL_Window* window) {
	#if defined(YGL_USE_SDL)
		SDL_DestroyTexture(window->sdlTexture);
		SDL_DestroyWindow(window->sdlWindow);
		SDL_DestroyRenderer(window->sdlRenderer);
	#elif defined(YGL_USE_SDL1)
		SDL_FreeSurface(window->sdlSurface);
	#endif
	
	YGL_FreeCanvas(window->canvas);
	free(window);
}

bool YGL_DrawWindow(YGL_Window* window) {
	#if defined(YGL_USE_SDL)
		// check if canvas size has changed
		YGL_Vec2 textureSize;
		SDL_QueryTexture(
			window->sdlTexture, NULL, NULL, &textureSize.x, &textureSize.y
		);

		if (!YGL_CompareVec2(textureSize, window->canvas->size)) {
			// create a new texture
			SDL_DestroyTexture(window->sdlTexture);

			window->sdlTexture = SDL_CreateTexture(
				window->sdlRenderer, SDL_PIXELFORMAT_ABGR8888,
				SDL_TEXTUREACCESS_STREAMING, window->canvas->size.x,
				window->canvas->size.y
			);

			if (window->sdlTexture == NULL) {
				YGL_SetError("Failed to create SDL texture");
				return false;
			}
		}
	
		SDL_UpdateTexture(
			window->sdlTexture, NULL, window->canvas->pixels,
			window->canvas->size.x * 4
		);
		SDL_RenderCopy(window->sdlRenderer, window->sdlTexture, NULL, NULL);
		SDL_RenderPresent(window->sdlRenderer);
	#elif defined(YGL_USE_SDL1)
		if (SDL_MUSTLOCK(window->sdlSurface)) {
			if (SDL_LockSurface(window->sdlSurface) < 0) {
				YGL_SetError("Failed to lock SDL surface");
				return false;
			}
		}
		
		for (int x = 0; x < window->canvas->size.x; ++ x) {
			for (int y = 0; y < window->canvas->size.y; ++ y) {
				uint8_t* pixels = (uint8_t*) window->sdlSurface->pixels;
				uint8_t* pixel  =
					pixels + y * window->sdlSurface->pitch + x * 3;

				uint32_t colour = *YGL_GetCanvasPixel(
					window->canvas, (YGL_Vec2) {x, y}
				);
				YGL_Colour rgb = YGL_PixelToColour(colour);
				uint32_t sdlPixel = SDL_MapRGB(
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
	#endif

	return true;
}
