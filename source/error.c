#include "util.h"
#include "error.h"

static char* error;

bool YGL_InitError(void) {
	error = malloc(1); // if this fails then you need a new computer

	if (error == NULL) {
		return false;
	}
	
	*error = 0;
	return true;
}

void YGL_FreeError(void) {
	free(error);
}

void YGL_SetError(const char* str) {
	error = YGL_DupString(str);

	if (error == NULL) {
		// lets pretend that didn't happen
		YGL_InitError();
	}
}

char* YGL_GetError(void) {
	return error;
}
