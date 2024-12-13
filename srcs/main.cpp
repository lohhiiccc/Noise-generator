
#include "windowManager/WindowManager.hpp"
#include "window.hpp"


int main() {
	WindowManager window(WIDTH, HEIGHT, graph);
	window.load_render(cloud);
	window.load_render(marble);
	window.load_render(random);
	window.load_render(wood);


	window.loop();
	return 0;
}