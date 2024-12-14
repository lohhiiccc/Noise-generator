#include <cstdint>
#include "window.hpp"
#include "noise/perlin.hpp"

int random(uint32_t *img, int width, int height) {
	static PerlinNoise PerlinNoise;
	static float time = 0.0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float r = (PerlinNoise.noise(x * 0.0001 + time, (y * 00.001) + time)) * 0.5;
			int color = static_cast<int>((r + 1) * 127.5);
			img[y * width + x] = (color << 16) >> 1| (color << 8) | 0;
		}
	}
	time += 0.01;
	return 0;
}

