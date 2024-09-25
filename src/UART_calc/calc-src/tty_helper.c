// tty_helper.c - unix/linux raw mode enable for bare keyboard input
//
// mostly from https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
//
// tty_raw()            enter raw mode
// tty_cooked()         exit raw mode
// tty_ready()          return 1 if there is a character available, else 0
// tty_char()           return next character, wait if needed
//
// Note the ^C is disabled so the main program must provide some way to exit
// when tty_ready() notices a character, it is buffered and returned on the
// next call to tty_char()
//

// #define TEST_MAIN

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>

#include "tty_helper.h"

static struct termios orig_termios;
static char save_char = 0;

void die( char *msg) {
  fprintf( stderr, "ERROR: %s\n", msg);
  exit(1);
}

void tty_cooked() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    die("tcsetattr");
}
void tty_raw() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
  atexit(tty_cooked);
  struct termios raw = orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  //  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}


int tty_ready() {
  char c = '\0';
  if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");
  if( !c) return 0;
  save_char = c;
  return 1;
}


int tty_char() {
  if( save_char) return save_char;
  while( !tty_ready())
    ;
  int rc = save_char;
  save_char = '\0';
  return rc;
}



#ifdef TEST_MAIN

int main() {
  tty_raw();
  while (1) {
    while( !tty_ready())
      ;
    int c = tty_char();
    if (iscntrl(c)) {
      printf("%d\r\n", c);
    } else {
      printf("%d ('%c')\r\n", c, c);
    }
    if (c == 'q') break;
  }
  return 0;
}

#endif
