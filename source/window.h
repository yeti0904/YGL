#ifndef YGL_WINDOW_H
#define YGL_WINDOW_H

#include "canvas.h"
#include "backend.h"

typedef struct YGL_Window {
	/*#if defined(YGL_USE_SDL)
		SDL_Window*   sdlWindow;
		SDL_Renderer* sdlRenderer;
		SDL_Texture*  sdlTexture;
	#elif defined(YGL_USE_SDL1)
		SDL_Surface* sdlSurface;
	#endif*/
	
	YGL_BackendWindow windowBackend;
	YGL_Canvas*       canvas;
} YGL_Window;

YGL_Window* YGL_CreateWindow(const char* name, int w, int h);
void        YGL_FreeWindow(YGL_Window* window);
bool        YGL_DrawWindow(YGL_Window* window);

#endif
