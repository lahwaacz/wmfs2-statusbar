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
 -  [picojson](https://github.com/kazuho/picojson) - for parsing configuration files; included in project tree
 -  [cppformat](https://github.com/cppformat/cppformat)

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

Runtime configuration is supported via JSON config files. Path to the file can be specified using the `-c` argument:

    ./wmfs-statusbar -c /path/to/config-file
