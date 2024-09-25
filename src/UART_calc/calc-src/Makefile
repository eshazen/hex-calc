all: calc

# include needed for OS-X
CFLAGS = -I/usr/X11/include -DUSE_TTY -DAVR8

#CFLAGS = -DDEBUG

clean:
	rm -f *.o *~ calc

calc_key.o: calc_key.c calc_key.h calc.h

calc.o: calc.c calc.h

tty_helper.o: tty_helper.c tty_helper.h

main.o: main.c tty_helper.h calc.h

calc: main.o tty_helper.o calc_key.o calc.o
	cc -o calc $^

