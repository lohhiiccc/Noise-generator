#include "windowManager/WindowManager.hpp"
#include "noise/perlin.hpp"
#include <X11/Xutil.h>
#include <iostream>
#include <X11/Xlib.h>
#include <csignal>

WindowManager::WindowManager(int width, int height, renderFunction render) :
	render(render),
	ptrTabIndex(0),
	WindowX(0), WindowY(0),
	WindowWidth(width), WindowHeight(height),
	BorderWidth(0),
	WindowDepth(CopyFromParent),
	WindowClass(CopyFromParent),
	WindowVisual(CopyFromParent),
	AttributeValueMask(CWBackPixel | CWEventMask),
	isDisplayReady(false)
{
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
	this->init_img();
	load_render(render);
	isWindowOpen = true;
}

WindowManager::~WindowManager() {
	this->destroy_img();
	XUnmapWindow(this->MainDisplay, this->MainWindow);
	XDestroyWindow(this->MainDisplay, this->MainWindow);
	XCloseDisplay(this->MainDisplay);
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
		case ConfigureNotify:
		{
			XConfigureEvent *event = (XConfigureEvent *)&GeneralEvent;
			if (event->width != this->WindowWidth || event->height != this->WindowHeight) {
				this->WindowWidth = event->width;
				this->WindowHeight = event->height;
				this->resize_img();
			}
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
			update_image(this->render);
			display_image();
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

	XPutImage(MainDisplay, Pixmap, DefaultGC(MainDisplay, 0), &image, 0, 0, 0, 0, WindowWidth, WindowHeight);
	XCopyArea(MainDisplay, Pixmap, MainWindow, DefaultGC(MainDisplay, 0), 0, 0, WindowWidth, WindowHeight, 0, 0);
	XFlush(MainDisplay);
}

void WindowManager::update_image(renderFunction r) {
	if (r(img, WindowWidth, WindowHeight) != 0)
		this->isWindowOpen = false;
}

void WindowManager::load_render(renderFunction r) {
	this->renderFunctions.push_back(r);
}

void WindowManager::init_img() {
	this->img = new u_int32_t[WindowWidth * WindowHeight];
	this->Pixmap = XCreatePixmap(MainDisplay, MainWindow, WindowWidth, WindowHeight, 24);
}

void WindowManager::destroy_img() {
	delete[] img;
	XFreePixmap(MainDisplay, Pixmap);
}

void WindowManager::resize_img() {
	this->destroy_img();
	this->init_img();
}