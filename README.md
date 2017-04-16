# tb32
Experimental robot based around stm32, esp8266, .96" OLED, and alegro drivers

### Instructions:

* Follow the instructions in the readme for `git@github.com:beckdac/stm32f103c8t6.git` which is the same as the parent fork, unless otherwise identified.
* In `rtos/libwwg` build the library with `make`. (Side note, this library is very useful, see examples for ideas).
* In this application's directory, do a `make clobber` and `make` and if you are using the ST LINK v2 or similar, `make flash`.

## Other thoughts:

With my generic ST LINK v2, `openocd` and the ARM gdb have been very useful.
