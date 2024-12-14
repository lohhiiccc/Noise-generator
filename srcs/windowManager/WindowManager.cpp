#include "windowManager/WindowManager.hpp"
#include "noise/perlin.hpp"
#include <X11/Xutil.h>
#include <iostream>
#include <X11/Xlib.h>
#include <csignal>

WindowManager::WindowManager(int width, int height, int (*render)(u_int32_t *img, bool &needUpdate)) :
	render(render),
	ptrTabIndex(0),
	WindowX(0), WindowY(0),
	WindowWidth(width), WindowHeight(height),
	BorderWidth(0),
	WindowDepth(CopyFromParent),
	WindowClass(CopyFromParent),
	WindowVisual(CopyFromParent),
	AttributeValueMask(CWBackPixel | CWEventMask),
	isDisplayReady(false),
	needUpdate(true)
{
	img = new u_int32_t[width * height];
	MainDisplay = XOpenDisplay(0);
	RootWindow = XDefaultRootWindow(MainDisplay);
	WindowAttributes = {};
	WindowAttributes.background_pixel = 0x0;
	WindowAttributes.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask | ExposureMask;

	MainWindow = XCreateWindow(MainDisplay, RootWindow,
							 	WindowX, WindowY, WindowWidth, WindowHeight,
							 	BorderWidth, WindowDepth, WindowClass, WindowVisual,
							 	AttributeValueMask, &WindowAttributes);
	XMapWindow(MainDisplay, MainWindow);
	wmDelete = XInternAtom(MainDisplay, "WM_DELETE_WINDOW", false);
	XSetWMProtocols(MainDisplay, MainWindow, &wmDelete, 1);
	load_render(render);
	isWindowOpen = true;
}

WindowManager::~WindowManager() {
	XUnmapWindow(this->MainDisplay, this->MainWindow);
	XDestroyWindow(this->MainDisplay, this->MainWindow);
	XCloseDisplay(this->MainDisplay);
	delete[] img;
}

void WindowManager::handle_events(XEvent &GeneralEvent) {
	switch(GeneralEvent.type) {
		case KeyPress:
		{

		} break;
		case KeyRelease:
		{
			XKeyPressedEvent *event = (XKeyPressedEvent *)&GeneralEvent;
			if (event->keycode == XKeysymToKeycode(this->MainDisplay, XK_Escape)) {
				this->isWindowOpen = false;
			} else if (event->keycode == XKeysymToKeycode(this->MainDisplay, XK_space)) {
				this->ptrTabIndex = (this->ptrTabIndex + 1) % this->renderFunctions.size();
				this->render = this->renderFunctions[this->ptrTabIndex];
			}
		} break;
		case ClientMessage: {
			if (static_cast<Atom>(GeneralEvent.xclient.data.l[0]) == this->wmDelete) {
				this->isWindowOpen = false;
			}
		} break;
		case Expose:
		{
			if (!isDisplayReady)
				isDisplayReady = true;
		} break;
	}
}

void WindowManager::loop() {
	while (isWindowOpen) {
		while (XPending(this->MainDisplay) > 0)
		{
			XEvent GeneralEvent = {};
			XNextEvent(this->MainDisplay, &GeneralEvent);
			handle_events(GeneralEvent);
		}
		if (isDisplayReady) {
			if (this->needUpdate) {
				update_image(this->render);
				display_image();
			}
			// XSync(this->MainDisplay, false);
		}
	}
}

void WindowManager::display_image() {
	XImage image;

	image.width = WindowWidth;
	image.height = WindowHeight;
	image.format = ZPixmap;
	image.data = reinterpret_cast<char *>(img);
	image.byte_order = LSBFirst;
	image.bitmap_unit = 32;
	image.byte_order = LSBFirst;
	image.bitmap_pad = 32;
	image.depth = 24;
	image.bytes_per_line = this->WindowWidth * 4;
	image.bits_per_pixel = 32;

	const Pixmap pixmap = XCreatePixmap(MainDisplay, MainWindow, WindowWidth, WindowHeight, image.depth);
	XPutImage(MainDisplay, pixmap, DefaultGC(MainDisplay, 0), &image, 0, 0, 0, 0, WindowWidth, WindowHeight);
	XCopyArea(MainDisplay, pixmap, MainWindow, DefaultGC(MainDisplay, 0), 0, 0, WindowWidth, WindowHeight, 0, 0);
	XFreePixmap(MainDisplay, pixmap);
	XFlush(MainDisplay);
}

void WindowManager::update_image(int (*func)(u_int32_t *img, bool &needUpdate)) {
	if (func(this->img, this->needUpdate))
		this->isWindowOpen = false;
}

void WindowManager::load_render(int (*func)(u_int32_t *img, bool &needUpdate)) {
	this->renderFunctions.push_back(func);
}