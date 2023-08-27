#ifndef YGL_IMAGE_H
#define YGL_IMAGE_H

#include "canvas.h"

#if defined(YGL_USE_SDL) || (YGL_USE_SDL1)
	YGL_Canvas* YGL_LoadBMP(const char* path);
#endif

#endif
