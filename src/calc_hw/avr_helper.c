#include "avr_helper.h"

//
// convert uint64 to string (from KamilCuk on stackoverflow)
// return result in static buffer
//
char *uint64_to_str(uint64_t n) {
  static char sval[21];
  char *dest = sval;
 dest += 20;
  *dest-- = 0;
  while (n) {
    *dest-- = (n % 10) + '0';
    n /= 10;
  }
  return dest + 1;
}
