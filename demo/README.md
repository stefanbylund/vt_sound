# Demonstration of vt_sound

This folder contains a simple example program demonstrating how to use the
[vt_sound](https://github.com/stefanbylund/vt_sound) C API for the Vortex
Tracker II player to play a PT3 module in the background.

## How to Build

If you want to build this demo program yourself, follow the steps below:

1. On Windows, you need [MinGW](http://www.mingw.org/),
[UnxUtils](https://sourceforge.net/projects/unxutils/) or
[Cygwin](https://www.cygwin.com/) for the basic Unix commands. Add the chosen
set of Unix commands to your path.

2. Install the latest version of [z88dk](https://github.com/z88dk/z88dk) and
a Sinclair ZX Spectrum emulator with AY-3-8912 sound chip support, e.g.
[ZEsarUX](https://sourceforge.net/projects/zesarux/).

3. Download the vt_sound repository either as a ZIP archive using the
"Clone or download" button at the top of this page or with Git using the
following command:

> git clone https://github.com/stefanbylund/vt_sound.git

4. Go to the vt_sound directory and enter the following command to build the
C API for Vortex Tracker II Player:

> make all

5. Go to the vt_sound/demo directory and enter the following command to build
the demo program:

> make all

6. Run the vt_sound/demo/bin/\<compiler-flavour\>/vt_sound_demo.tap file in your
Sinclair ZX Spectrum emulator.

**Tip:** If you don't care for makefiles or don't want to install
MinGW/UnxUtils/Cygwin on Windows, you can build vt_sound demo manually
by using the z88dk command-line invocation located in the header of the
vt_sound_demo.c source file.

## License

This software is licensed under the terms of the MIT license.

The included PT3 example module music.pt3 is originally called Tears.pt3 and is
copyright (C) 2005 by Sergey Bulba (http://bulba.untergrund.net/).
