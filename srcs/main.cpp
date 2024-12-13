
#include "windowManager/WindowManager.hpp"
#include "noise/perlin.hpp"

#define WIDTH 720
#define HEIGHT 420

int render(uint32_t *img) {
	static PerlinNoise PerlinNoise;
	static float time = 0.0;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			float n = (PerlinNoise.noise(x / 100.0 + time, (y / 100.0) + time));

			int color = static_cast<int>((n + 1) * 127.5);
			img[y * WIDTH + x] = (color << 16) | (color << 8) | color ;
		}
	}
	time += 0.1;
	return 0;
}

int main() {
	WindowManager	window(WIDTH, HEIGHT, render);

	window.loop();
	return 0;
}
