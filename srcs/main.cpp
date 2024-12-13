
#include <csignal>
#include "windowManager/WindowManager.hpp"

#define WIDTH 500
#define HEIGHT 800

int main() {
	WindowManager	window(WIDTH, HEIGHT);
	u_int32_t *img = window.get_image_addr();

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			img[y * WIDTH + x] = (y * 255 / HEIGHT) * 0x100 + (x * 255 / WIDTH);
		}
	}



	window.loop();
	return 0;
}
