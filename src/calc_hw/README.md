# calc_hw

Calculator firmware to run on real hardware

## Bugs

* signed mode doesn't work.  Clues:
  * both LEDs flash on most buttons
  * drop/swap don't work either
* 8 bit mode inaccessible (currently shifted f, need to move)
* no way to cancel f prefix
* display should extend to both lines when necessary
* AVR doesn't have 64-bit signed decimal display
* power down timeout


