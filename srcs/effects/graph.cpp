#include <cstdint>
#include "window.hpp"
#include "noise/perlin.hpp"

int graph(uint32_t *img, bool &needUpdate) {
	if (!needUpdate)
		return 0;
	needUpdate = false;
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
	needUpdate = true;
	return 0;
}

