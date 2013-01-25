Simple lightweight statusbar for WMFS2
======================================

Preview
-------

![Screenshot preview](https://raw.github.com/lahwaacz/wmfs2-statusbar/master/statusbar-preview.png)

Build dependencies
------------------

 -  gcc (obviously)
 -  cmake
 -  pkg-config
 -  libx11 - Xlib.h
 -  xproto - Xatom.h
 -  libmpdclient - MPD plugin
 -  libpulse - PulseAudio plugin
 -  (optional) boost - currently for debug purposes only

Runtime dependencies
--------------------

 -  wmfs2
 -  mpd - MPD plugin
 -  pulseaudio - PulseAudio plugin

Compilation
-----------

    git clone git://github.com/lahwaacz/wmfs2-statusbar.git
    cd ./wmfs2-statusbar
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local ./
    make
    make install

Configuration
-------------

Runtime configuration is not currently supported, you need to make changes in source code and recompile.
