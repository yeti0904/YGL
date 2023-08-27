#ifndef YGL_COMPONENTS_H
#define YGL_COMPONENTS_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <sys/param.h>

#if defined(YGL_USE_SDL)
	#include <SDL2/SDL.h>
#elif defined(YGL_USE_SDL1)
	#include <SDL/SDL.h>
#endif

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

#endif
