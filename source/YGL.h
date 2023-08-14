#ifndef YGL_YGL_H
#define YGL_YGL_H

#ifdef YGL_USE_SDL
	#include <SDL2/SDL.h>
#endif

#include "image.h"
#include "window.h"
#include "canvas.h"
#include "error.h"

bool YGL_Init(void);
void YGL_Quit(void);

#endif
