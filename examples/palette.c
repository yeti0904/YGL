#include <stdio.h>
#include <YGL.h>

int main(void) {
	if (!YGL_Init()) {
		YGL_PrintError();
		return 1;
	}

	YGL_Window* window = YGL_CreateWindow("YGL", 8, 8);

	if (window == NULL) {
		YGL_PrintError();
		return 1;
	}

	YGL_Palette* palette = YGL_CreatePalette(256);

	palette->colours[0] = (YGL_Colour) {0,   0,   0,   255};
	palette->colours[1] = (YGL_Colour) {255, 0  , 0,   255};
	palette->colours[2] = (YGL_Colour) {0,   255, 0,   255};
	palette->colours[3] = (YGL_Colour) {0,   0,   255, 255};
	palette->colours[4] = (YGL_Colour) {255, 255, 255, 255};

	while (true) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_QUIT: {
					YGL_FreeWindow(window);
					YGL_Quit();
					return 0;
				}
			}
		}

		window->canvas->ignoreRGB = true;
		
		YGL_ClearCanvas(window->canvas, YGL_PaletteIndexToColour(0));

		for (int x = 0; x < 8; ++ x) {
			YGL_DrawRawPixel(
				window->canvas, (YGL_Vec2) {x, 1}, x
			);
		}

		if (!YGL_PalettedCanvasToRGB(window->canvas, palette)) {
			YGL_PrintError();
		}

		YGL_DrawWindow(window);
	}
}
