
#ifndef NOISE_GENERATOR_WINDOWMANAGER_HPP
#define NOISE_GENERATOR_WINDOWMANAGER_HPP

#include <X11/Xlib.h>
#include <mutex>
#include <cstdint>
#include <vector>

typedef int (*renderFunction)(u_int32_t *img, int width, int height);

class WindowManager {
public:
	WindowManager(int width, int height, renderFunction r);
	~WindowManager();

	void load_render(renderFunction r);
	void loop();
private:
	void resize_img();
	void init_img();
	void destroy_img();
	void update_image(renderFunction);
	void display_image();
	void handle_events(XEvent &GeneralEvent);

	renderFunction							render;
	std::vector<renderFunction>				renderFunctions;
	uint8_t 								ptrTabIndex;
	u_int32_t								*img;
	int										WindowX;
	int										WindowY;
	int										WindowWidth;
	int										WindowHeight;
	int										BorderWidth;
	int										WindowDepth;
	int										WindowClass;
	Visual									*WindowVisual;
	int										AttributeValueMask;
	XSetWindowAttributes					WindowAttributes;
	Window 									MainWindow;
	Display  								*MainDisplay;
	Window 									RootWindow;
	Atom 									wmDelete;
	bool 									isWindowOpen;
	bool									isDisplayReady;
	Pixmap									Pixmap;
};

#endif //NOISE_GENERATOR_WINDOWMANAGER_HPP
