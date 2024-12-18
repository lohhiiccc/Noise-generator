#include <cmath>
#include <cstdint>
#include "window.hpp"
#include "noise/perlin.hpp"

int wood(uint32_t *img, int width, int height) {
	static PerlinNoise perlinNoise;
	static float time = 0.0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float n = perlinNoise.noise(x / 100.0 + time, y / 100.0 + time);
			float wood = sin((x * 0.1 + n * 5.0));
			int color = static_cast<int>((wood + 1) * 127.5);
			img[y * width + x] = (color << 16) | (color << 8) | color;
		}
	}
	time += 0.01;
	return 0;
}
