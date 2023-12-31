#include "stb.h"
#include "util.h"
#include "error.h"
#include "backend.h"

// hi
// i put this comment here in an attempt to make git push this file
// because for some reason the old error system is on github despite git saying my local repo is up to date with the github repo
// silly github

static char*           error;
static YGL_ErrorSource errorSource;

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
	if (error != NULL) {
		free(error);
	}

	error = YGL_DupString(str);

	if (error == NULL) {
		// lets pretend that didn't happen
		YGL_InitError();
	}
}

char* YGL_GetError(void) {
	return error;
}

void YGL_SetErrorSource(YGL_ErrorSource source) {
	errorSource = source;
}

YGL_ErrorSource YGL_GetErrorSource(void) {
	return errorSource;
}

void YGL_PrintError(void) {
	const char* source;

	switch (errorSource) {
		case YGL_ERRORSOURCE_INTERNAL: {
			source = "internal";
			break;
		}
		case YGL_ERRORSOURCE_BACKEND: {
			source = "backend";
			break;
		}
		case YGL_ERRORSOURCE_STB_IMAGE: {
			source = "stb_image";
			break;
		}
		default: {
			source = "(error)";
			break;
		}
	}

	printf("[YGL Error from %s] %s", source, error);

	switch (errorSource) {
		case YGL_ERRORSOURCE_BACKEND: {
			YGL_Backend backend = YGL_GetBackend();

			if (backend.null) {
				printf(" (No backend, could be a bug)\n");
			}
			else {
				printf(" (%s)\n", backend.getError());
			}
			break;
		}
		case YGL_ERRORSOURCE_STB_IMAGE: {
			printf(" (%s)\n", stbi_failure_reason());
			break;
		}
		// TODO: does stb_image_write have error stuff
		default: {
			putchar('\n');
			break;
		}
	}
}
