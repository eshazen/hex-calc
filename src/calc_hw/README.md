# calc_hw

Calculator firmware to run on real hardware

## Bugs / Missing Features

* Display:
  * 64-bit binary needs shift/toggle
  * Use 8 custom characters to make reverse video or other markers
    * This is troublesome as there are only 8 and we need 16 <br>
	  (need to re-write the custom character table on the fly)
  * AVR doesn't have 64-bit signed decimal display
* power down timeout (but can't turn off 

## Enhancements

* Floating point mode?  Double or decimal64?
* Unit conversions (english/metric)

