#include <SDL2/SDL.h>
#define YGL_USE_SDL
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

	YGL_3DShape* cube[4];

	cube[0]            = YGL_Create3DShape(4);
	cube[0]->points[0] = (YGL_FVec3) {-10, -10, 5}; // bottom left
	cube[0]->points[1] = (YGL_FVec3) {-10,  10, 5}; // top left
	cube[0]->points[2] = (YGL_FVec3) { 10,  10, 5}; // top right
	cube[0]->points[3] = (YGL_FVec3) { 10, -10, 5}; // bottom right

	cube[1]            = YGL_Create3DShape(4);
	cube[1]->points[0] = (YGL_FVec3) {-10, -10, 10}; // bottom left
	cube[1]->points[1] = (YGL_FVec3) {-10,  10, 10}; // top left
	cube[1]->points[2] = (YGL_FVec3) { 10,  10, 10}; // top right
	cube[1]->points[3] = (YGL_FVec3) { 10, -10, 10}; // bottom right

	cube[2]            = YGL_Create3DShape(4);
	cube[2]->points[0] = (YGL_FVec3) {-10, -10,  5}; // bottom left
	cube[2]->points[1] = (YGL_FVec3) {-10,  10,  5}; // top left
	cube[2]->points[2] = (YGL_FVec3) {-10,  10, 10}; // top right
	cube[2]->points[3] = (YGL_FVec3) {-10, -10, 10}; // bottom right

	cube[3]            = YGL_Create3DShape(4);
	cube[3]->points[0] = (YGL_FVec3) { 10, -10, 10}; // bottom left
	cube[3]->points[1] = (YGL_FVec3) { 10,  10, 10}; // top left
	cube[3]->points[2] = (YGL_FVec3) { 10,  10,  5}; // top right
	cube[3]->points[3] = (YGL_FVec3) { 10, -10,  5}; // bottom right

	YGL_FVec3 camera = {0.0, 0.0, 0.0};

	int ticks = 0;

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

		++ ticks;
		const uint8_t* keys = SDL_GetKeyboardState(NULL);

		if (keys[SDL_SCANCODE_W]) {
			for (size_t i = 0; i < sizeof(cube) / sizeof(void*); ++ i) {
				YGL_Move3DShape(cube[i], (YGL_FVec3) {0, 0, -1});
			}
			camera.z -= 1;
		}
		if (keys[SDL_SCANCODE_A]) {
			for (size_t i = 0; i < sizeof(cube) / sizeof(void*); ++ i) {
				YGL_Move3DShape(cube[i], (YGL_FVec3) {1, 0, 0});
			}
			camera.x += 1;
		}
		if (keys[SDL_SCANCODE_S]) {
			for (size_t i = 0; i < sizeof(cube) / sizeof(void*); ++ i) {
				YGL_Move3DShape(cube[i], (YGL_FVec3) {0, 0, 1});
			}
			camera.z += 1;
		}
		if (keys[SDL_SCANCODE_D]) {
			for (size_t i = 0; i < sizeof(cube) / sizeof(void*); ++ i) {
				YGL_Move3DShape(cube[i], (YGL_FVec3) {-1, 0, 0});
			}
			camera.x -= 1;
		}
		if (keys[SDL_SCANCODE_LEFT]) {
			YGL_FVec2 camera2D = {camera.x, camera.z};
			for (size_t i = 0; i < sizeof(cube) / sizeof(void*); ++ i) {
				YGL_Spin3DShape(cube[i], camera2D, -1.0);
			}
		}
		if (keys[SDL_SCANCODE_RIGHT]) {
			YGL_FVec2 camera2D = {camera.x, camera.z};
			for (size_t i = 0; i < sizeof(cube) / sizeof(void*); ++ i) {
				YGL_Spin3DShape(cube[i], camera2D, 1.0);
			}
		}
		
		YGL_ClearCanvas(window->canvas, (YGL_Colour) {0, 50, 0, 255});

		for (size_t i = 0; i < sizeof(cube) / sizeof(void*); ++ i) {
			YGL_Draw3DPlane(
				window->canvas, cube[i], (YGL_Colour) {0, 255, 0, 255}
			);
		}

		YGL_DrawWindow(window);
	}
}
