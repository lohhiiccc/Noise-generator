#include <cstdint>
#include <cmath>
#include "window.hpp"
#include "noise/perlin.hpp"

int mountain(uint32_t *img, bool &needUpdate) {
	if (!needUpdate)
		return 0;
	needUpdate = false;
	static PerlinNoise P(9);
	static PerlinNoise P2(1000);
	static PerlinNoise P3(500);
	static float time = 0.0;

	/*basic color sunsine gradient no noise*/

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			float n = P2.noise(x / 10 + (time * 0.5), y / 100.0 + (time * 0.5)) * 0.5 + 0.5;
			int color = static_cast<int>(n * 255);
			img[y * WIDTH + x] = (0 << 16) | (color << 8) | color;
		}
	}
	/*mountain*/
	for (int x = 0; x < WIDTH; x++) {
		float n = P.noise(x / 100.0 + time, 0) * 0.5;
		float n2 = P2.noise(x / 1000.0 , 0) + P2.noise(x / 40.0 + (time * 0.5), 0) * 0.5;
		int y = static_cast<int>((n + 1) * (HEIGHT >> 1));
		int y2 = static_cast<int>((n2 + 1) * (HEIGHT >> 1) );
		for (int i = y2; i < HEIGHT; ++i) {
			img[i * WIDTH + x] = 0xf0f0f0;
		}
		for (int i = y; i < HEIGHT; ++i) {
			img[i * WIDTH + x] = 0x151515;
		}
	}


	time += 0.03;
	needUpdate = true;
	return 0;
}
