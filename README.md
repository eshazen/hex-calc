# hex-calc

Simple Hex/Binary/Decimal calculator inspired by HP-16C and TI Programmer.

![front view](pix/front.jpg)

Features:

* Hex / Decimal / Binary display in signed or unsigned mode
  * Entire stack for 8/16 bits, two levels for 32 bits
* four-function two-compliment or unsigned arithmetic
* 8 / 16 / 32 / 64 bit word size
* four-level RPN stack with roll / swap

Runs on ATMeg328 at 8MHz.  Power is 4xAA batteries regulated to 5V.
Industry-standard 16x2 backlit LCD.  Three LEDs:

* Power
* f key (function/shift) active
* signed display mode

Code in <tt>src/calc_hw</tt>.

KiCAD design in <tt>keyboard-pcb</tt>.

See https://github.com/eshazen/calc-demo-xwin for an X-windows
app written in C which illustrates the general idea.

