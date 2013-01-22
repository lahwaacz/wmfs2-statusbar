#include "Xstatus.h"

Xstatus::Xstatus(void) {
    dpy   = XOpenDisplay(NULL);
    root  = DefaultRootWindow(dpy);
    autf8 = XInternAtom(dpy, "UTF8_STRING", false);
    afunc = XInternAtom(dpy, "_WMFS_FUNCTION", false);
    acmd  = XInternAtom(dpy, "_WMFS_CMD", false);

    event.type         = ClientMessage;
    event.message_type = afunc;
    event.window       = root;
    event.format       = 32;
    event.data.l[4]    = true;
}

Xstatus::~Xstatus(void) {
    XCloseDisplay(dpy);
}

void Xstatus::sendStatus(const std::string statusLine) {
    XChangeProperty(dpy, root, afunc, autf8, 8, PropModeReplace, (unsigned char*)"status", 6);
    XChangeProperty(dpy, root, acmd, autf8, 8, PropModeReplace, (unsigned char*)statusLine.c_str(), statusLine.length());
  
    XSendEvent(dpy, root, false, StructureNotifyMask, (XEvent*)&event);
    XSync(dpy, False);
}
