#include <cmath>
#include <cstdint>
#include "window.hpp"
#include "noise/perlin.hpp"

int test(uint32_t *img) {
	static bool a = true;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (a)
				img[y * WIDTH + x] = 0x202020;
			else
				img[y * WIDTH + x] = 0x0;
		}
	}
	a = !a;
	return 0;
}