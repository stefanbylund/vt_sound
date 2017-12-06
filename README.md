# C API for Vortex Tracker II Player

The **vt_sound** project provides a C API for Sinclair ZX Spectrum 128/+2/+3/Next
for using the Vortex Tracker II (VT) player. The API is a thin C wrapper on top
of the VT player PT3PROM.asm. The VT player supports playing of Pro Tracker 3.x
(PT3) modules on the AY-3-8912 sound chip.

The file PT3PROM.asm has been adapted to the z80asm assembler in
[z88dk](https://github.com/z88dk/z88dk) and is based on the file
PT3Play/ROM/PT3PROM.asm in http://bulba.untergrund.net/PTxTools.7z, which uses
the SjASM assembler syntax. The code section can be executed from RAM or ROM,
contains no self-modifying code, and can be assembled at any address. The data
section contains the variables and self-modifying code and can be located at any
address in RAM.

The [vt_sound_demo](https://github.com/stefanbylund/vt_sound_demo) project
contains a simple example program demonstrating how to use this API.

## Download

The latest version of this API can be downloaded **[here](build/vt_sound.zip)**.
This download contains the following header files and libraries:

* vt_sound/include/vt_sound.h
* vt_sound/lib/sccz80/vt_sound.lib
* vt_sound/lib/sdcc_ix/vt_sound.lib
* vt_sound/lib/sdcc_iy/vt_sound.lib

If you want to build the vt_sound libraries yourself, see the "How to Build"
section below.

## API Documentation

The vt_sound API is documented in the following header file:

* [vt_sound.h](include/vt_sound.h)

## How to Use

1. Download [vt_sound.zip](build/vt_sound.zip) and unpack it in a suitable
place. It contains the files listed in the "Download" section above.

2. Install the latest version of [z88dk](https://github.com/z88dk/z88dk) and
a Sinclair ZX Spectrum emulator with AY-3-8912 sound chip support, e.g.
[ZEsarUX](https://sourceforge.net/projects/zesarux/). If you want to compose
PT3 modules or convert other module formats to PT3, install the
[Vortex Tracker II](http://bulba.untergrund.net/VT1.0beta19Plus.7z) music
editor.

3. If the module to be played is a PT3 module, it can be played directly by the
VT player. If the module is not a PT3 module but a module in another format
supported by Vortex Tracker II, open the module in Vortex Tracker II and save it
as a PT3 module.

4. Create an assembler source file for loading the PT3 module(s). Define a
read-only data section and load the PT3 module(s) using the BINARY directive.
Associate each PT3 module with a public label starting with an underscore, e.g.
_music_module.

5. Make the PT3 module(s) available to your C program by declaring external
references to their public labels (but without the leading underscore) as
created in step 4 above, e.g. "extern uint8_t music_module[];".

6. Include vt_sound.h and call vt_init(<module_address>) to initialize the VT
player with the specified module.

7. Call vt_play() each 1/50 second or install the vt_play_isr() function as
an IM2 interrupt service routine. The module will now start playing in the
background.

8. Compile your program with z88dk and link it with the appropriate version of
vt_sound.lib.

9. Run your program in a Sinclair ZX Spectrum emulator with AY-3-8912 sound chip
support.

**Tip:** See the [vt_sound_demo](https://github.com/stefanbylund/vt_sound_demo)
project for a simple example of how to use vt_sound.h and link with vt_sound.lib.

**Tip:** If you copy the vt_sound header files and libraries into the following
directories in z88dk, the z88dk compiler will automatically find them without
the need for setting up any include and library paths:

* z88dk/include/_DEVELOPMENT/sccz80/
* z88dk/include/_DEVELOPMENT/sdcc/
* z88dk/libsrc/_DEVELOPMENT/lib/sccz80/
* z88dk/libsrc/_DEVELOPMENT/lib/sdcc_ix/
* z88dk/libsrc/_DEVELOPMENT/lib/sdcc_iy/

## How to Build

If you want to build the vt_sound libraries yourself, follow the steps below:

1. On Windows, you need [MinGW](http://www.mingw.org/),
[UnxUtils](https://sourceforge.net/projects/unxutils/) or
[Cygwin](https://www.cygwin.com/) for the basic Unix commands. Add the chosen
set of Unix commands to your path.

2. Install the latest version of [z88dk](https://github.com/z88dk/z88dk) and add
it to your path.

3. Download the vt_sound repository either as a ZIP archive using the
"Clone or download" button at the top of this page or with Git using the
following command:

> git clone https://github.com/stefanbylund/vt_sound.git

4. Go to the vt_sound repository and enter the following command:

> make all

## License

This software is licensed under the terms of the MIT license.

The Vortex Tracker II player in the file PT3PROM.asm is copyright (C) 2004-2007
by Sergey Bulba (http://bulba.untergrund.net/).
