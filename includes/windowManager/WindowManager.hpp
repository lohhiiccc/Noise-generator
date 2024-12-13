
#ifndef NOISE_GENERATOR_WINDOWMANAGER_HPP
#define NOISE_GENERATOR_WINDOWMANAGER_HPP

#include <X11/Xlib.h>
#include <mutex>
#include <cstdint>
#include "err.h"

class WindowManager {
public:
	WindowManager(int width, int height, int (*)(u_int32_t *img));
	~WindowManager();

	u_int32_t *get_image_addr() { return img; }

	void loop();
private:
	void update_image(int (*)(u_int32_t *img));
	void display_image();
	void handle_events(XEvent &GeneralEvent);

	int 					(*render)(u_int32_t *img);
	u_int32_t				*img;
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
	bool					isDisplayReady;
};

#endif //NOISE_GENERATOR_WINDOWMANAGER_HPP
