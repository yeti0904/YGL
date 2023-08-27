#ifndef YGL_UTIL_H
#define YGL_UTIL_H

#include "components.h"

#define YGL_FUNCTION_POINTER(TYPE, NAME, ...) TYPE (*NAME)(__VA_ARGS__)

char*       YGL_DupString(const char* str);
const char* YGL_GetExtension(const char* path);

#endif
