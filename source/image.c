#include "image.h"
#include "error.h"

#define STB_IMAGE_IMPLEMENTATION
//#define STBI_FAILURE_USERMSG
#include <stb/stb_image.h>

YGL_Canvas* YGL_LoadImage(const char* filename) {
	YGL_Canvas* ret;
	YGL_Vec2    size;
	int         components;

	uint8_t* data = stbi_load(filename, &size.x, &size.y, &components, 4);

	if (data == NULL) {
		YGL_SetError("stbi_load failed");
		YGL_SetErrorSource(YGL_ERRORSOURCE_STB_IMAGE);
		return NULL;
	}

	ret = YGL_CreateCanvas(size.x, size.y);

	if (ret == NULL) {
		stbi_image_free(data);
		return NULL;
	}

	uint8_t* pixel = data;
	for (int y = 0; y < size.y; ++ y) {
		for (int x = 0; x < size.x; ++ x, pixel += 4) {
			YGL_Colour colour = {pixel[0], pixel[1], pixel[2], pixel[3]};
			YGL_DrawPixel(ret, (YGL_Vec2) {x, y}, colour);
		}
	}

	stbi_image_free(data);
	return ret;
}
