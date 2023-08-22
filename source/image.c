#include "image.h"
#include "error.h"

static YGL_Canvas* YGL_CreateCanvasFromSurface(SDL_Surface* surface) {
	YGL_Canvas* ret = YGL_CreateCanvas(surface->w, surface->h);

	if (ret == NULL) {
		return NULL;
	}

	int area = surface->w * surface->h;

	for (int i = 0; i < area; ++ i) {
		uint32_t pixel = ((uint32_t*) surface->pixels)[i];

		int r = ((pixel & surface->format->Rmask) >> surface->format->Rshift);
		int g = ((pixel & surface->format->Gmask) >> surface->format->Gshift);
		int b = ((pixel & surface->format->Bmask) >> surface->format->Bshift);
		int a = ((pixel & surface->format->Amask) >> surface->format->Ashift);

		ret->pixels[i] = YGL_ColourToPixel((YGL_Colour) {r, g, b, a});
	}

	return ret;
}

YGL_Canvas* YGL_LoadBMP(const char* path) {
	YGL_Canvas* ret = NULL;

	#if defined(YGL_USE_SDL) || defined(YGL_USE_SDL1)
		SDL_Surface* surface = SDL_LoadBMP(path);
		
		if (surface == NULL) {
			YGL_SetError("Failed to create SDL surface");
			return NULL;
		}

		ret = YGL_CreateCanvasFromSurface(surface);
		SDL_FreeSurface(surface);
	#endif
	
	return ret;
}
