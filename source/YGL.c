#include "YGL.h"
#include "backend.h"

bool YGL_Init(void) {
	if (!YGL_InitError()) {
		return false;
	}
	
	YGL_InitBackend();
	YGL_Backend backend = YGL_GetBackend();

	if (!backend.null) {
		if (!backend.init()) {
			YGL_SetError("Backend error");
			YGL_SetErrorSource(YGL_ERRORSOURCE_BACKEND);
			return false;
		}
	}

	return true;
}

void YGL_Quit(void) {
	YGL_FreeError();

	YGL_Backend backend = YGL_GetBackend();
	if (!backend.null) {
		backend.free();
	}
}
