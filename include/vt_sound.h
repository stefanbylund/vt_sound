/*******************************************************************************
 * Stefan Bylund 2016
 *
 * C API for calling the Vortex Tracker II (VT) player in PT3PROM.asm.
 * The VT player supports playing of Pro Tracker 3.x (PT3) modules.
 *
 * The module(s) to be played is created in the following way:
 *
 * 1. If the module is a PT3 module, it can be played directly by the VT player.
 * 2. If the module is not a PT3 module but a module in another format supported
 *    by Vortex Tracker II, open the module in Vortex Tracker II and save it as
 *    a PT3 module.
 * 3. Create an assembler source file for loading the PT3 module(s).
 *    Define a read-only data section and load the PT3 module(s) using the
 *    BINARY directive. Associate each PT3 module with a public label starting
 *    with an underscore, e.g. _music_module.
 *
 * How to use:
 *
 * 1. Make the PT3 module(s) available to your C program by declaring external
 *    references to their public labels (but without the leading underscore) as
 *    created in step 3 above, e.g. "extern uint8_t music_module[];".
 * 2. Call vt_init(<module_address>) to initialize the VT player with the
 *    specified module.
 * 3. Call vt_play() each 1/50 second or install the vt_play_isr() function as
 *    an IM2 interrupt service routine. The module will now start playing in the
 *    background.
 ******************************************************************************/

#ifndef _VT_SOUND_H
#define _VT_SOUND_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Returns a pointer to the VT player's setup byte.
 * Set bit 0 to disable looping; bit 7 is set after each loop.
 */
extern uint8_t *vt_get_setup(void);

/*
 * Initializes the VT player with the specified module.
 *
 * If this function is called during playing of the module, it mutes the sound
 * and reinitializes the VT player with the specified module to be played from
 * its beginning.
 */
extern void vt_init(const void *module_address) __z88dk_fastcall;

/*
 * Plays one snippet of the module. Call this function each 1/50 second to play
 * the module continuously, e.g. from your interrupt service routine.
 * The AF, BC, DE, HL, AF', BC', DE', HL', IX, IY registers should be preserved
 * when calling vt_play().
 */
extern void vt_play(void);

/*
 * This function is tailored for installation as a self-contained IM2 interrupt
 * service routine to play the module in the background.
 */
extern void vt_play_isr(void);

/*
 * Enables (true) or disables (false) the vt_play_isr() interrupt service
 * routine. The vt_play_isr() interrupt service routine is initially enabled.
 */
extern void vt_set_play_isr_enabled(bool enabled) __z88dk_fastcall;

/*
 * Mutes the sound. Call vt_play() to continue playing again.
 *
 * If the vt_play_isr() interrupt service routine is used, call
 * vt_set_play_isr_enabled(false) before calling vt_mute() to mute the sound.
 * Call vt_set_play_isr_enabled(true) to continue playing again.
 */
extern void vt_mute(void);

/*
 * Returns a pointer to the VT player's current position pointer word.
 */
extern uint16_t *vt_get_cur_pos(void);

#endif
