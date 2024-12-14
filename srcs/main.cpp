
#include "windowManager/WindowManager.hpp"
#include "window.hpp"


int main() {
	WindowManager window(WIDTH, HEIGHT, test);
	window.load_render(graph);
	window.load_render(graph2);
	window.load_render(cloud);
	window.load_render(marble);
	window.load_render(random);
	window.load_render(wood);
	window.load_render(mountain);

	window.loop();
	return 0;
}