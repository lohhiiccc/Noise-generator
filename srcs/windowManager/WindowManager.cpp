#include "windowManager/WindowManager.hpp"
#include <string.h>
#include <X11/Xutil.h>
#include <iostream>
#include <X11/Xlib.h>
#include <csignal>
#include <mutex>

WindowManager::WindowManager(int width, int height) :
	WindowX(0), WindowY(0),
	WindowWidth(width), WindowHeight(height),
	BorderWidth(0),
	WindowDepth(CopyFromParent),
	WindowClass(CopyFromParent),
	WindowVisual(CopyFromParent),
	AttributeValueMask(CWBackPixel | CWEventMask)
{
	img = new u_int32_t[width * height];
	MainDisplay = XOpenDisplay(0);
	RootWindow = XDefaultRootWindow(MainDisplay);
	bzero(&WindowAttributes, sizeof(XSetWindowAttributes));
	WindowAttributes.background_pixel = 0x0;
	WindowAttributes.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask | ExposureMask;

	MainWindow = XCreateWindow(MainDisplay, RootWindow,
							 	WindowX, WindowY, WindowWidth, WindowHeight,
							 	BorderWidth, WindowDepth, WindowClass, WindowVisual,
							 	AttributeValueMask, &WindowAttributes);
	XMapWindow(MainDisplay, MainWindow);
	wmDelete = XInternAtom(MainDisplay, "WM_DELETE_WINDOW", false);
	XSetWMProtocols(MainDisplay, MainWindow, &wmDelete, 1);

	isWindowOpen = true;
}

WindowManager::~WindowManager() {
	XUnmapWindow(this->MainDisplay, this->MainWindow);
	XDestroyWindow(this->MainDisplay, this->MainWindow);
	XCloseDisplay(this->MainDisplay);
	delete[] img;
}

void WindowManager::loop() {
	while (isWindowOpen) {
		XEvent GeneralEvent = {};
		XNextEvent(this->MainDisplay, &GeneralEvent);

		switch(GeneralEvent.type) {
			case KeyPress:
			case KeyRelease:
			{
				XKeyPressedEvent *event = (XKeyPressedEvent *)&GeneralEvent;
				if (event->keycode == XKeysymToKeycode(this->MainDisplay, XK_Escape)) {
					this->isWindowOpen = false;
				}
			} break;
			case ClientMessage: {
				if (static_cast<Atom>(GeneralEvent.xclient.data.l[0]) == this->wmDelete) {
					this->isWindowOpen = false;
				}
			} break;
			case Expose:
			{
				std::cout << "test" << std::endl;
				display_image();
			} break;
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

	XPutImage(MainDisplay, MainWindow, DefaultGC(MainDisplay, 0), &image, 0, 0, 0, 0, WindowWidth, WindowHeight);
	XFlush(MainDisplay);
}
