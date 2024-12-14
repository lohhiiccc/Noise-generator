#include <cstdint>
#include <cmath>
#include "window.hpp"
#include "noise/perlin.hpp"

int graph(uint32_t *img) {
	static PerlinNoise PerlinNoise;
	static float time = 0.0;
	for (int x = 0; x < WIDTH; x++) {
		float n = PerlinNoise.noise(x / 100.0 + time, 0.0) * 0.5;

		int y = static_cast<int>((n + 1) * (HEIGHT >> 1));
		for (int i = 0; i < HEIGHT; ++i) {
			if (i == y)
				img[i * WIDTH + x] = 0xFFFFFF;
			else
				img[i * WIDTH + x] = 0;
		}
	}
	time += 0.001;
	return 0;
}

int graph2(uint32_t *img) {
	static PerlinNoise PerlinNoise;
	static float time = 0.0;
	for (int x = 0; x < WIDTH; x++) {
		float n = PerlinNoise.noise(x / 100.0, time) * 0.5;

		int y = static_cast<int>((n + 1) * (HEIGHT >> 1));
		for (int i = 0; i < HEIGHT; ++i) {
			if (i - y < 40 && i - y > -40){
				int co = static_cast<int>(255 * (40 - abs(i - y)) / 40);
				img[i * WIDTH + x] = 0 << 16| (co << 8) | co;
			}
			else
				img[i * WIDTH + x] = 0;
		}
	}
	time += 0.001;
	return 0;
}
