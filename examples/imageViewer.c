#include <stdio.h>
#include <YGL.h>

int main(int argc, char** argv) {
	if (argc == 1) {
		printf("Usage: %s {file}\n", argv[0]);
		return 0;
	}

	if (!YGL_Init()) {
		YGL_PrintError();
		return 1;
	}

	YGL_Window* window = YGL_CreateWindow("YGL", 640, 480);

	if (window == NULL) {
		YGL_PrintError();
		return 1;
	}

	YGL_Canvas* image = YGL_LoadImage(argv[1]);

	if (image == NULL) {
		YGL_PrintError();
		return 1;
	}

	while (true) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_QUIT: {
					YGL_FreeCanvas(image);
					YGL_FreeWindow(window);
					YGL_Quit();
					return 0;
				}
				case SDL_WINDOWEVENT: {
					switch (e.window.event) {
						case SDL_WINDOWEVENT_RESIZED: {
							YGL_Vec2 newSize = {
								e.window.data1, e.window.data2
							};

							YGL_ResizeCanvas(window->canvas, newSize);
							break;
						}
					}
					
					break;
				}
			}
		}
		
		YGL_ClearCanvas(window->canvas, (YGL_Colour) {0, 50, 0, 255});
		YGL_BlitCanvas(window->canvas, NULL, NULL, image);
		YGL_DrawWindow(window);
	}
}
