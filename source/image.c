#include "util.h"
#include "image.h"
#include "error.h"
#include "stb.h"

static int jpegQuality = 50;

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

bool YGL_SaveImage(const char* filename, YGL_Canvas* canvas) {
	const char* ext = YGL_GetExtension(filename);

	uint8_t* data = (uint8_t*) malloc(canvas->size.x * canvas->size.y * 4);

	if (data == NULL) {
		YGL_SetError("malloc failed");
		YGL_SetErrorSource(YGL_ERRORSOURCE_INTERNAL);
		return false;
	}

	// serialise canvas
	uint8_t* currentPixel = data;
	for (int y = 0; y < canvas->size.y; ++ y) {
		for (int x = 0; x < canvas->size.x; ++ x, currentPixel += 4) {
			YGL_Pixel  pixel  = *YGL_GetCanvasPixel(canvas, (YGL_Vec2) {x, y});
			YGL_Colour colour = YGL_PixelToColour(pixel);

			currentPixel[0] = colour.r;
			currentPixel[1] = colour.g;
			currentPixel[2] = colour.b;
			currentPixel[3] = colour.a;
		}
	}

	if (strcmp(ext, "png") == 0) {
		int res = stbi_write_png(
			filename, canvas->size.x, canvas->size.y, 4, data, canvas->size.x * 4
		);

		if (res == 0) {
			YGL_SetError("stbi_write_png failed");
			YGL_SetErrorSource(YGL_ERRORSOURCE_STB_IMAGE_WRITE);
			free(data);
			return false;
		}
	}
	else if (strcmp(ext, "bmp") == 0) {
		int res = stbi_write_bmp(
			filename, canvas->size.x, canvas->size.y, 4, data
		);

		if (res == 0) {
			YGL_SetError("stbi_write_bmp failed");
			YGL_SetErrorSource(YGL_ERRORSOURCE_STB_IMAGE_WRITE);
			free(data);
			return false;
		}
	}
	else if (strcmp(ext, "tga") == 0) {
		int res = stbi_write_tga(
			filename, canvas->size.x, canvas->size.y, 4, data
		);

		if (res == 0) {
			YGL_SetError("stbi_write_tga failed");
			YGL_SetErrorSource(YGL_ERRORSOURCE_STB_IMAGE_WRITE);
			free(data);
			return false;
		}
	}
	else if ((strcmp(ext, "jpg") == 0) || (strcmp(ext, "jpeg") == 0)) {
		int res = stbi_write_jpg(
			filename, canvas->size.x, canvas->size.y, 4, data, jpegQuality
		);

		if (res == 0) {
			YGL_SetError("stbi_write_jpg failed");
			YGL_SetErrorSource(YGL_ERRORSOURCE_STB_IMAGE_WRITE);
			free(data);
			return false;
		}
	}

	return true;
}

void YGL_SetJPEGQuality(int quality) {
	jpegQuality = quality;
}
