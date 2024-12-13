
#ifndef NOISE_GENERATOR_WINDOWMANAGER_HPP
#define NOISE_GENERATOR_WINDOWMANAGER_HPP

#include <X11/Xlib.h>
#include "err.h"

class WindowManager {
public:
	WindowManager(int width, int height);
	~WindowManager();

	void loop();
private:
	Display *_display;
	int 	_screen;
	Window	root;
	Window	win;
	XEvent 	event;
	int 	_width;
	int 	_height;

};

#endif //NOISE_GENERATOR_WINDOWMANAGER_HPP
