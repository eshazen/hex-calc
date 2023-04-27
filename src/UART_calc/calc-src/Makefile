all: calc

# include needed for OS-X
CFLAGS = -I/usr/X11/include

#CFLAGS = -DDEBUG

clean:
	rm -f *.o *~ calc

tty_helper.o: tty_helper.c tty_helper.h

main.o: main.c tty_helper.h calc.h

calc: main.o tty_helper.o
	cc -o calc $^

