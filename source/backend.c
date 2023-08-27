#include "backend.h"
#include "backends/SDL.h"
#include "backends/SDL1.h"

static YGL_Backend backend;

void YGL_InitBackend(void) {
	#if defined(YGL_USE_SDL)
		backend = YGL_CreateSDLBackend();
	#elif defined(YGL_USE_SDL) 
		backend = YGL_CreateSDL1Backend();
	#else
		backend.null = true;
	#endif
}

YGL_Backend YGL_GetBackend(void) {
	return backend;
}

void YGL_SetBackend(YGL_Backend pbackend) {
	memcpy(&backend, &pbackend, sizeof(YGL_Backend));
}
