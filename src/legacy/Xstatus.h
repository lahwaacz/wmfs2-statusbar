#pragma once

#include <string>

#include <X11/Xlib.h>
#include <X11/Xatom.h>

class Xstatus {
    private:
        Display *dpy;
        Window root;
        Atom autf8;
        Atom afunc;
        Atom acmd;
        XClientMessageEvent event;
    public:
        Xstatus(void);
        ~Xstatus(void);

        void sendStatus(const std::string statusLine);
};

