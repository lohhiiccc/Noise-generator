
#include <cstdint>
#include "window.hpp"
#include "noise/perlin.hpp"

int cloud(uint32_t *img, int width, int height) {
	static PerlinNoise PerlinNoise;
	static float time = 0.0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float n = PerlinNoise.noise(x / 100.0 + time, (y / 100.0) + time) * 0.5;
			n += PerlinNoise.noise(x / 50.0 + time, (y / 50.0) + time) * 0.25;

			int color = static_cast<int>((n + 1) * 127.5);
			img[y * width + x] = (color << 16) | (color << 8) | color ;
		}
	}
	time += 0.1;
	return 0;
}

