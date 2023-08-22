#include "window.h"
#include "error.h"

YGL_Window* YGL_CreateWindow(const char* name, int w, int h) {
	YGL_Window* ret = (YGL_Window*) malloc(sizeof(YGL_Window));

	if (ret == NULL) {
		YGL_SetError("malloc failed");
		return NULL;
	}

	#ifdef YGL_USE_SDL
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
	#endif

	ret->canvas = YGL_CreateCanvas(w, h);

	if (ret->canvas == NULL) {
		free(ret);
		return NULL;
	}

	return ret;
}

void YGL_FreeWindow(YGL_Window* window) {
	#ifdef YGL_USE_SDL
		SDL_DestroyTexture(window->sdlTexture);
		SDL_DestroyWindow(window->sdlWindow);
		SDL_DestroyRenderer(window->sdlRenderer);
	#endif
	
	YGL_FreeCanvas(window->canvas);
	free(window);
}

bool YGL_DrawWindow(YGL_Window* window) {
	#ifdef YGL_USE_SDL
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
	#endif

	return true;
}
