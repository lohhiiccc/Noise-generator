#include "windowManager/WindowManager.hpp"

WindowManager::WindowManager(int width, int height) : _width(width), _height(height) {
	_display = XOpenDisplay(NULL);
	if (NULL == _display) errx(2, "unable to open display");
	_screen = DefaultScreen(_display);
	root = RootWindow(_display, _screen);
	win = XCreateSimpleWindow(_display, root, 0, 0, _width, _height, 10,
							  0, 0x0f0f0f);

	XMapWindow(_display, win);
	XFlush(_display);
}

WindowManager::~WindowManager() {
	XUnmapWindow(_display, win);
	XDestroyWindow(_display, win);
	XCloseDisplay(_display);
}

void WindowManager::loop() {
	while (XNextEvent(_display, &event) != 0);
}
