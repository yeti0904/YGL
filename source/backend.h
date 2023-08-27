#ifndef YGL_BACKEND_H
#define YGL_BACKEND_H

#include "components.h"
#include "canvas.h"
#include "util.h"

#ifndef YGL_CUSTOM_BACKEND_COMPONENTS
	typedef struct YGL_BackendWindow {
		bool null;
		#if defined(YGL_USE_SDL)
			SDL_Window*   sdlWindow;
			SDL_Renderer* sdlRenderer;
			SDL_Texture*  sdlTexture;
		#elif defined(YGL_USE_SDL1)
			SDL_Surface* sdlSurface;
		#endif
	} YGL_BackendWindow;
#endif

typedef struct YGL_Backend {
	bool null; // sets if there is no backend
	YGL_FUNCTION_POINTER(bool,              init, void);
	YGL_FUNCTION_POINTER(void,              free, void);
	YGL_FUNCTION_POINTER(YGL_BackendWindow, initWindow, const char*, int, int);
	YGL_FUNCTION_POINTER(void,              freeWindow, YGL_BackendWindow*);
	YGL_FUNCTION_POINTER(
		bool, drawWindow, YGL_Canvas*, YGL_BackendWindow*
	);
	YGL_FUNCTION_POINTER(char*, getError, void);
} YGL_Backend;

void        YGL_InitBackend(void);
YGL_Backend YGL_GetBackend(void);
void        YGL_SetBackend(YGL_Backend pbackend);

#endif
