#include "backend.h"
#include "window.h"
#include "error.h"

YGL_Window* YGL_CreateWindow(const char* name, int w, int h) {
	YGL_Window* ret = (YGL_Window*) malloc(sizeof(YGL_Window));

	if (ret == NULL) {
		YGL_SetError("malloc failed");
		YGL_SetErrorSource(YGL_ERRORSOURCE_INTERNAL);
		return NULL;
	}

	YGL_Backend backend = YGL_GetBackend();

	if (backend.null) {
		YGL_SetError("A backend is required to create a window");
		YGL_SetErrorSource(YGL_ERRORSOURCE_INTERNAL);
		free(ret);
		return NULL;
	}
	
	ret->windowBackend = backend.initWindow(name, w, h);
	if (ret->windowBackend.null) {
		free(ret);
		return NULL;
	}

	ret->canvas = YGL_CreateCanvas(w, h);

	if (ret->canvas == NULL) {
		free(ret);
		return NULL;
	}

	return ret;
}

void YGL_FreeWindow(YGL_Window* window) {
	YGL_Backend backend = YGL_GetBackend();
	backend.freeWindow(&window->windowBackend);
	
	YGL_FreeCanvas(window->canvas);
	free(window);
}

bool YGL_DrawWindow(YGL_Window* window) {
	YGL_Backend backend = YGL_GetBackend();
	return backend.drawWindow(window->canvas, &window->windowBackend);
}
