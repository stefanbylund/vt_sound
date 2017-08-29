################################################################################
# Stefan Bylund 2017
#
# Makefile for compiling C library for Vortex Tracker II player.
# Supports both the SCCZ80 and SDCC compilers.
################################################################################

MKDIR := mkdir -p

RM := rm -rf

ZIP := zip -r -q

SRCS := src/vt_sound.asm src/PT3PROM.asm

LIBDIR_SCCZ80 := lib/sccz80

LIBDIR_SDCC_IX := lib/sdcc_ix

LIBDIR_SDCC_IY := lib/sdcc_iy

DEBUGFLAGS := --list --c-code-in-asm

all: all_sccz80 all_sdcc_ix all_sdcc_iy

all_sccz80:
	$(MKDIR) $(LIBDIR_SCCZ80)
	zcc +zx -vn -O3 -x -clib=new $(DEBUG) -Iinclude $(SRCS) -o $(LIBDIR_SCCZ80)/vt_sound

all_sdcc_ix:
	$(MKDIR) $(LIBDIR_SDCC_IX)
	zcc +zx -vn -SO3 -x -clib=sdcc_ix $(DEBUG) --max-allocs-per-node200000 -Iinclude $(SRCS) -o $(LIBDIR_SDCC_IX)/vt_sound

all_sdcc_iy:
	$(MKDIR) $(LIBDIR_SDCC_IY)
	zcc +zx -vn -SO3 -x -clib=sdcc_iy $(DEBUG) --max-allocs-per-node200000 -Iinclude $(SRCS) -o $(LIBDIR_SDCC_IY)/vt_sound

debug_sccz80: DEBUG = $(DEBUGFLAGS)

debug_sdcc_ix: DEBUG = $(DEBUGFLAGS)

debug_sdcc_iy: DEBUG = $(DEBUGFLAGS)

debug_sccz80: all_sccz80

debug_sdcc_ix: all_sdcc_ix

debug_sdcc_iy: all_sdcc_iy

distro:
	$(RM) build/vt_sound.zip
	cd ..; $(ZIP) vt_sound/build/vt_sound.zip vt_sound/include vt_sound/lib

clean:
	$(RM) lib zcc_opt.def zcc_proj.lst src/*.lis
