#
# Makefile for UART example
#
# NOTE: edit F_OSC and DUDPORT to support either directly programming
# the hardware using a programming cable, or Arduino bootloader.
#

# MCU = atmega328
MCU = atmega168

# 8 MHz for on-board oscillator
# F_OSC = 8000000

# 16 MHz for Arduino
F_OSC = 16000000

# CFLAGS = -g -Os -mmcu=$(MCU) $(EXTRAOPT) -DF_CPU=$(F_OSC)
# CFLAGS = -g -Os -mmcu=$(MCU) $(EXTRAOPT) -DF_CPU=$(F_OSC) -Wl,-u,vfprintf -lprintf_min -lm
CFLAGS =  -g -Os -mmcu=$(MCU) $(EXTRAOPT) -DF_CPU=$(F_OSC) -Wl,-u,vfprintf

LDFLAGS = -Wl,-Map=$(<:.o=.map),--cref -mmcu=$(MCU)

FUSEOPT = -U hfuse:w:0xd9:m

# programmer configuration for avrdude programming utility

# for AVRISP programmer on USB
# DUDEPORT  = -c avrispv2 -P usb

# for Arduino bootloader
DUDEPORT  = -c arduino -P /dev/ttyACM0

# set to correct device type; usually an Arduino Uno is 328p
DUDEMCU = m328p

AVRDUDE  = avrdude $(DUDEPORT) -p $(DUDEMCU) -y -u 

objects = calc-src/main.o uart.o calc-src/calc.o avr_helper.o calc-src/calc_key.o

headers = uart.h


all: $(objects)  main.hex list

clean:
	rm -f *.o *~ *.hex *.elf *.map *.lst calc-src/*.o

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
