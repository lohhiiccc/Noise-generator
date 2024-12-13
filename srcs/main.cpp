
#include "windowManager/WindowManager.hpp"

#define WIDTH 500
#define HEIGHT 800

int main() {
	WindowManager	window(WIDTH, HEIGHT);

	window.loop();

	return 0;
}
