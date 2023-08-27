#ifndef YGL_ERROR_H
#define YGL_ERROR_H

#include "components.h"

typedef enum {
	YGL_ERRORSOURCE_INTERNAL,
	YGL_ERRORSOURCE_BACKEND,
	YGL_ERRORSOURCE_STB_IMAGE
} YGL_ErrorSource;

bool            YGL_InitError(void);
void            YGL_FreeError(void);
void            YGL_SetError(const char* str);
char*           YGL_GetError(void);
void            YGL_SetErrorSource(YGL_ErrorSource source);
YGL_ErrorSource YGL_GetErrorSource(void);
void            YGL_PrintError(void);

#endif
