#ifndef YGL_IMAGE_H
#define YGL_IMAGE_H

#include "canvas.h"

YGL_Canvas* YGL_LoadImage(const char* filename);
bool        YGL_SaveImage(const char* filename, YGL_Canvas* canvas);
void        YGL_SetJPEGQuality(int quality);

#endif
