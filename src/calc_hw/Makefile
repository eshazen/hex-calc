#
# Makefile for blinky
#

MCU = atmega328

# 8 MHz for on-board oscillator if DIV8 fuse cleared
F_OSC = 8000000

# 16MHz for Stock arduino
# F_OSC = 16000000

CFLAGS = -g -Os -mmcu=$(MCU) $(EXTRAOPT) -DF_CPU=$(F_OSC) -Wl,-u,vfprintf -lprintf_min -lm
# no-optimization settings for interrupt code
CFLAGS_NOOPT = -g -O0 -mmcu=$(MCU) $(EXTRAOPT) -DF_CPU=$(F_OSC) -I../util -Wl,-u,vfprintf -lprintf_min

LDFLAGS = -Wl,-Map=$(<:.o=.map),--cref -mmcu=$(MCU)

# lfuse default 0x62 write as 0xe2 to disable CLKDIV8
FUSEOPT = -U lfuse:w:0xe2:m

# read fuses
RFUSEOPT = -U hfuse:r:-:h -U lfuse:r:-:h -U efuse:r:-:h

# USB tiny programmer
DUDEPORT  = -c usbtiny -P usb

# for AVRISP programmer on USB
# DUDEPORT  = -c avrispv2 -P usb

# for Arduino bootloader
# DUDEPORT  = -c arduino -P /dev/ttyACM0

DUDEMCU = m328
AVRDUDE  = avrdude $(DUDEPORT) -p $(DUDEMCU) -y -u 

objects = main.o lcd.o kb.o timer.o led.o calc.o calc_key.o avr_helper.o custom.o

headers = lcd.h kb.h timer.h led.h calc.h calc_key.h avr_helper.h custom.h

all: $(objects)  main.hex list

clean:
	rm -f *.o *~ *.hex *.elf *.map *.lst

flash: main.hex
	$(AVRDUDE) -U flash:w:$^:i

list:
	avr-objdump -h -S main.elf > main.lst
	avr-size --common -x main.elf

$(objects): %.o: %.c $(headers)
	avr-gcc -c $(CFLAGS) $< -o $@

main.elf: $(objects)
	avr-gcc $(LDFLAGS) $(objects) -o $@

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

fuse:
	$(AVRDUDE) $(FUSEOPT)

rfuse:
	$(AVRDUDE) $(RFUSEOPT)
