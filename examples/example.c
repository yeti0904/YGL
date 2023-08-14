#include <SDL2/SDL.h>
#include <YGL.h>

int main(void) {
	if (!YGL_Init()) {
		fprintf(stderr, "YGL_Init failed\n");
		return 1;
	}

	YGL_Window* window = YGL_CreateWindow("YGL", 640, 480);

	if (window == NULL) {
		fprintf(stderr, "Failed to make window\n");
		return 1;
	}

	while (true) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_QUIT: {
					YGL_FreeWindow(window);
					YGL_Quit();
					return 0;
				}
				case SDL_WINDOWEVENT: {
					switch (e.window.event) {
						case SDL_WINDOWEVENT_RESIZED: {
							YGL_Vec2 newSize = {e.window.data1, e.window.data2};

							YGL_ResizeCanvas(window->canvas, newSize);
							break;
						}
					}
					break;
				}
			}
		}

		YGL_ClearCanvas(window->canvas, (YGL_Colour) {0, 0, 0, 255});

		YGL_Vec2 triangle[] = {
			{100, 200}, {200, 200}, {150, 100}
		};

		YGL_DrawShape(window->canvas, triangle, 3, (YGL_Colour) {0, 255, 0, 255});

		YGL_DrawWindow(window);
	}
}
