# Changelog

All notable changes to the C API for Vortex Tracker II Player (vt_sound)
for Spectrum 128/+2/+3/Next will be documented in this file.

## 2022-06-07

* Moved the vt_sound_demo repository into this repository's demo folder.

## 2018-12-01

* Extended vt_mute() to also disable all channels.
* Changed vt_set_play_isr_enabled() parameter from int to boolean.

## 2018-11-18

* Make vt_play() function suitable for calling from a custom ISR.

## 2018-07-23

* Push/pop ix/iy registers in vt_init() and vt_play().

## 2017-07-23

* Added missing const qualifier.

## 2017-07-04

* First public release.
