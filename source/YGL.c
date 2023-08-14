#include "YGL.h"

bool YGL_Init(void) {
	if (!YGL_InitError()) {
		return false;
	}

	#ifdef YGL_USE_SDL
		int res = SDL_Init(SDL_INIT_VIDEO);

		if (res < 0) {
			YGL_SetError("SDL error");
		}

		return res == 0;
	#endif
}

void YGL_Quit(void) {
	YGL_FreeError();

	#ifdef YGL_USE_SDL
		SDL_Quit();
	#endif
}
