#include <cstdint>
#include "window.hpp"
#include "noise/perlin.hpp"

int random(uint32_t *img, bool &needUpdate) {
	if (!needUpdate)
		return 0;
	needUpdate = false;
	static PerlinNoise PerlinNoise;
	static float time = 0.0;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			float r = (PerlinNoise.noise(x * 0.0001 + time, (y * 00.001) + time)) * 0.5;

			int color = static_cast<int>((r + 1) * 127.5);
			img[y * WIDTH + x] = (color << 16) >> 1| (color << 8) | 0;
		}
	}
	time += 0.01;
	needUpdate = true;
	return 0;
}

