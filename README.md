# Name #
youtube-dl-gui

## Description ##
[youtube-dl](https://github.com/rg3/youtube-dl) is an excellent command-line
program that allows downloading videos from [YouTube](http://youtube.com).
This project overlays that amazing functionality with a simple GUI interface to
make video retrieval easier for those not comfortable with the command line.
If this is you, I highly suggest you invest the time to learn the CL.  In the
meantime, I hope this app helps.

If you prefer a Python implementation, I suggest you look into the
[Python GUI version](https://code.google.com/p/youtube-dl-gui/), off of which
this project is based.

## Development ##
### Requirements ###
To build this application, you must have the
[Qt Project 4.6+](http://qt-project.org/) installed on your system, as well as
[cmake](http://www.cmake.org/), and of course the original youtube-dl project
should be installed and in your path.

This program is tested with youtube-dl version 2014.01.03.  Earlier versions
may work but are untested and officially unsupported.

### Building ###
Follow the standard steps to building any cmake project.

    git clone https://github.com/keelerm84/youtube-dl-gui
    cd youtube-dl-gui/build
    cmake ..
    make

## Bugs ##
Bugs and suggestions should be reported at
[https://github.com/keelerm84/youtube-dl-gui](https://github.com/keelerm84/youtube-dl-gui/issues).
