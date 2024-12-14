#include <cmath>
#include <cstdint>
#include "window.hpp"
#include "noise/perlin.hpp"

int test(uint32_t *img, int width, int height) {
	static bool a = true;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (a)
				img[y * width + x] = 0x202020;
			else
				img[y * width + x] = 0x0;
		}
	}
	return 0;
}