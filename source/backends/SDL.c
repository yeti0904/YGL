#include "SDL.h"
#include "../error.h"

#ifdef YGL_USE_SDL

static bool YGL_SDL_Init(void) {
	int res = SDL_Init(SDL_INIT_VIDEO);

	if (res < 0) {
		YGL_SetError("SDL error");
		YGL_SetErrorSource(YGL_ERRORSOURCE_BACKEND);
	}

	return res == 0;
}

static void YGL_SDL_Free(void) {
	SDL_Quit();
}

static YGL_BackendWindow YGL_SDL_InitWindow(const char* name, int w, int h) {
	YGL_BackendWindow ret;
	ret.null = true;

	ret.sdlWindow = SDL_CreateWindow(
		name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h,
		SDL_WINDOW_RESIZABLE
	);

	if (ret.sdlWindow == NULL) {
		YGL_SetError("Failed to create SDL window");
		YGL_SetErrorSource(YGL_ERRORSOURCE_BACKEND);
		return ret;
	}

	ret.sdlRenderer = SDL_CreateRenderer(
		ret.sdlWindow, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (ret.sdlRenderer == NULL) {
		YGL_SetError("Failed to create SDL renderer");
		YGL_SetErrorSource(YGL_ERRORSOURCE_BACKEND);
		return ret;
	}

	ret.sdlTexture = SDL_CreateTexture(
		ret.sdlRenderer, SDL_PIXELFORMAT_ABGR8888,
		SDL_TEXTUREACCESS_STREAMING, w, h
	);

	if (ret.sdlTexture == NULL) {
		YGL_SetError("Failed to create SDL texture");
		YGL_SetErrorSource(YGL_ERRORSOURCE_BACKEND);
		return ret;
	}

	ret.null = false;
	return ret;
}

static void YGL_SDL_FreeWindow(YGL_BackendWindow* window) {
	SDL_DestroyTexture(window->sdlTexture);
	SDL_DestroyWindow(window->sdlWindow);
	SDL_DestroyRenderer(window->sdlRenderer);
}

static bool YGL_SDL_DrawWindow(YGL_Canvas* canvas, YGL_BackendWindow* window) {
	YGL_Vec2 textureSize;
	SDL_QueryTexture(
		window->sdlTexture, NULL, NULL, &textureSize.x, &textureSize.y
	);

	if (!YGL_CompareVec2(textureSize, canvas->size)) {
		// create a new texture
		SDL_DestroyTexture(window->sdlTexture);

		window->sdlTexture = SDL_CreateTexture(
			window->sdlRenderer, SDL_PIXELFORMAT_ABGR8888,
			SDL_TEXTUREACCESS_STREAMING, canvas->size.x, canvas->size.y
		);

		if (window->sdlTexture == NULL) {
			YGL_SetError("Failed to create SDL texture");
			YGL_SetErrorSource(YGL_ERRORSOURCE_BACKEND);
			return false;
		}
	}

	SDL_UpdateTexture(
		window->sdlTexture, NULL, canvas->pixels, canvas->size.x * 4
	);
	SDL_RenderCopy(window->sdlRenderer, window->sdlTexture, NULL, NULL);
	SDL_RenderPresent(window->sdlRenderer);
	return true;
}

YGL_Backend YGL_CreateSDLBackend(void) {
	YGL_Backend backend;

	backend.null       = false;
	backend.init       = YGL_SDL_Init;
	backend.free       = YGL_SDL_Free;
	backend.initWindow = YGL_SDL_InitWindow;
	backend.freeWindow = YGL_SDL_FreeWindow;
	backend.drawWindow = YGL_SDL_DrawWindow;

	return backend;
}

#endif
