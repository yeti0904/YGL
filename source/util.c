#include "util.h"

char* YGL_DupString(const char* str) {
	char* ret = malloc(strlen(str) + 1);

	if (ret == NULL) {
		return NULL;
	}
	
	strcpy(ret, str);

	return ret;
}

const char* YGL_GetExtension(const char* path) {
	char* ret = strrchr(path, '.');

	if (ret == NULL) {
		return path + strlen(path); // empty string
	}

	return ret + 1;
}
