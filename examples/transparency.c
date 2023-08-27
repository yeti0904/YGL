#include <stdio.h>
#include <YGL.h>

int main(void) {
	if (!YGL_Init()) {
		YGL_PrintError();
		return 1;
	}

	YGL_Window* window = YGL_CreateWindow("YGL", 640, 480);

	if (window == NULL) {
		YGL_PrintError();
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

		YGL_Rect rect = {50, 50, 100, 100};
		YGL_FillRect(window->canvas, rect, (YGL_Colour) {255, 0, 0, 127});
		rect.x += 50;
		rect.y += 50;
		YGL_FillRect(window->canvas, rect, (YGL_Colour) {255, 0, 0, 127});

		YGL_DrawWindow(window);
	}
}
