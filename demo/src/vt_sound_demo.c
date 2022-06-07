/*******************************************************************************
 * Stefan Bylund 2016
 *
 * A simple example program for Sinclair ZX Spectrum for demonstrating how
 * to use the Vortex Tracker II player from C to play a PT3 module in the
 * background. See vt_sound.h for more information.
 *
 * zcc +zx -vn -SO3 -startup=1 -clib=sdcc_iy --max-allocs-per-node200000
 *   -L<vt_sound>/lib/sdcc_iy -lvt_sound -I<vt_sound>/include vt_sound_demo.c
 *   sound.asm -o vt_sound_demo -create-app
 ******************************************************************************/

#include <input.h>
#include <z80.h>
#include <intrinsic.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "vt_sound.h"

#pragma output CRT_ORG_CODE = 0x8184
#pragma output CLIB_MALLOC_HEAP_SIZE = 0
#pragma printf = "%c %s"

#define printCls() printf("%c", 12)
#define printAt(row, col, str) printf("\x16%c%c%s", (col + 1), (row + 1), (str))

extern uint8_t music_module[];

static void init_isr(void)
{
    // Set up IM2 interrupt service routine:
    // Put Z80 in IM2 mode with a 257-byte interrupt vector table located
    // at 0x8000 (before CRT_ORG_CODE) filled with 0x81 bytes. Install the
    // vt_play_isr() interrupt service routine at the interrupt service routine
    // entry at address 0x8181.

    intrinsic_di();
    im2_init((void *) 0x8000);
    memset((void *) 0x8000, 0x81, 257);
    z80_bpoke(0x8181, 0xC3);
    z80_wpoke(0x8182, (uint16_t) vt_play_isr);
    intrinsic_ei();
}

int main(void)
{
    vt_init(music_module);
    init_isr();

    printCls();
    printAt(10, 8, "Enjoy the music!\n");
    printAt(12, 5, "Press any key to exit\n");

    while (true)
    {
        if (in_inkey() != 0)
        {
            break;
        }
    }

    vt_set_play_isr_enabled(false);
    vt_mute();
    return 0;
}
