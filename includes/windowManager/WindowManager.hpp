
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
	int						WindowX;
	int						WindowY;
	int						WindowWidth;
	int						WindowHeight;
	int						BorderWidth;
	int						WindowDepth;
	int						WindowClass;
	Visual					*WindowVisual;
	int						AttributeValueMask;
	XSetWindowAttributes	WindowAttributes;
	Window 					MainWindow;
	Display  				*MainDisplay;
	Window 					RootWindow;
	Atom 					wmDelete;
	bool 					isWindowOpen;
};

#endif //NOISE_GENERATOR_WINDOWMANAGER_HPP
