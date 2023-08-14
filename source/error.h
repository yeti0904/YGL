#ifndef YGL_ERROR_H
#define YGL_ERROR_H

#include "components.h"

bool  YGL_InitError(void);
void  YGL_FreeError(void);
void  YGL_SetError(const char* str);
char* YGL_GetError(void);

#endif
