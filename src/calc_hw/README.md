# calc_hw

Calculator firmware to run on real hardware

## Bugs / Missing Features

* Occasional key bounce
* Turn off cursor
* Keyboard:
  * HEX/BIN/DEC should set push = 1
  * 8 bit mode inaccessible (shifted CLx)
  * no way to cancel f prefix (just push f again)
* Display:
  * 8,16,32-bit decimal can use both lines for X/Y with label
  * 64-bit hex can use both lines for X/Y (no label)
  * 64-bit binary needs shift/toggle
  * Use 8 custom characters to make reverse video or other markers
    * This is troublesome as there are only 8 and we need 16 <br>
	  (need to re-write the custom character table on the fly)
  * AVR doesn't have 64-bit signed decimal display
* power down timeout

## Enhancements

* Floating point mode?  Double or decimal64?
* Unit conversions (english/metric)

