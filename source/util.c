#include "util.h"

char* YGL_DupString(const char* str) {
	char* ret = malloc(strlen(str) + 1);

	if (ret == NULL) {
		return NULL;
	}
	
	strcpy(ret, str);

	return ret;
}
