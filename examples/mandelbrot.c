#include <YGL.h>

int t = 0;

YGL_Colour Mandelbrot(YGL_Vec2 pos, int maxIt, YGL_Vec2 size) {
	// written by kouzeru
	YGL_FVec2 fsize   = YGL_Vec2ToFloat(size);
	YGL_FVec2 scaled  = YGL_Vec2ToFloat(pos);
	scaled.x = (scaled.x - fsize.x / 2.0f) * fsize.x;
	scaled.y = (scaled.y - fsize.y / 2.0f) * fsize.x;
	
	int    it = 0;
	double pi = 3.14159265359;
	double ox = -1.7686343663753872;
	double oy =  0.0021018480275678;
	double zm = pow(2.,-((t%4096)/4096.)*56.)*1e-4;
	double cx = scaled.x * zm + ox;
	double cy = scaled.y * zm + oy;
	double zx = 0.0;
	double zy = 0.0;
	double zzx, zzy, zzl;
	double a, b, c, u, R, G, B;

	for(; it < maxIt; it++){
		zzx = zx * zx;
		zzy = zy * zy;
		if (zzx + zzy > 4.f && it > 1 ) {
			a = log(zzl);
			b = log(4.f);
			c = log(zzx + zzy);
			u = sqrt(it + (b - a) / (c - a) + 1) * 0.5f + t * 0.05;
			float l = fabs(sin((u/4.       ) * pi * 2)           )*255.0;
			float s =     (sin((u          ) * pi * 2)+        1.)*0.5;
			R = (fmax(fmin(sin((u/16.      ) * pi * 2)+0.5,1.),0.)*s+(1.-s))*l;
			G = (fmax(fmin(sin((u/16.+1./3.) * pi * 2)+0.5,1.),0.)*s+(1.-s))*l;
			B = (fmax(fmin(sin((u/16.+2./3.) * pi * 2)+0.5,1.),0.)*s+(1.-s))*l;
			return (YGL_Colour) {R, G, B, 255};
		}
		zzl = zzx + zzy;
		zy = 2 * zx * zy + cy;
		zx = zzx - zzy + cx;
	}
	return (YGL_Colour) {0, 0, 0, 255};
}

int main(void) {
	if (!YGL_Init()) {
		fprintf(stderr, "YGL_Init failed\n");
		return 1;
	}

	YGL_Window* window = YGL_CreateWindow("YGL", 100, 100);

	if (window == NULL) {
		fprintf(stderr, "Failed to make window\n");
		return 1;
	}

	while (true) {
		++ t;

		#ifdef YGL_USE_SDL
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
		#endif
		
		YGL_ClearCanvas(window->canvas, (YGL_Colour) {0, 50, 0, 255});

		for (int x = 0; x < window->canvas->size.x; ++ x) {
			for (int y = 0; y < window->canvas->size.y; ++ y) {
				YGL_Vec2   pos    = {x, y};
				YGL_Colour colour = Mandelbrot(pos, 4096, window->canvas->size);

				/*colour = YGL_AndColour(
					colour, (YGL_Colour) {0xFF, 0, 0xFF, 255}
				);*/

				YGL_DrawPixel(window->canvas, pos, colour);
			}
		}

		YGL_DrawWindow(window);
	}
}
