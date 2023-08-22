#include "YGL.h"

bool YGL_Init(void) {
	if (!YGL_InitError()) {
		return false;
	}

	#if defined(YGL_USE_SDL) || defined(YGL_USE_SDL1)
		int res = SDL_Init(SDL_INIT_VIDEO);

		if (res < 0) {
			YGL_SetError("SDL error");
		}

		return res == 0;
	#endif
}

void YGL_Quit(void) {
	YGL_FreeError();

	#if defined(YGL_USE_SDL) || defined(YGL_USE_SDL1)
		SDL_Quit();
	#endif
}
