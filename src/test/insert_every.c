
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *insert_every( char *str, int n, char c, int maxc);

int main( int argc, char *argv[]) {
  int n;
  char c;
  int maxc;
  char *p;
  char buff[80];

  if( argc < 4) {
    printf("usage:  insert_every <string> <n> <char>\n");
    exit(1);
  }

  strcpy( buff, argv[1]);
  n = atoi( argv[2]);
  c = argv[3][0];

  p = insert_every( buff, n, c, sizeof(buff));
  printf("Result: %s\n", p);
}

// start at end of string, insert c every n characters
// modify in place but don't exceed buffer size maxc
char *insert_every( char *str, int n, char c, int maxc) {
  int rl = strlen( str);	/* keep track of result length */
  int cp;
  if( rl > 3) {
    cp = rl-3;
    while( cp > 0) {
      memmove( str+cp+1, str+cp, rl-cp+1);
      str[cp] = c;
      cp -= 3;
      rl++;
    }
  }
  return str;
}
