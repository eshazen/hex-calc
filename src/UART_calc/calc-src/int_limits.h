#include <inttypes.h>

// macros to generate limits on the fly based on word size
#define MAX_SIGNED(r) ((int64_t)((1LL<<((r)-1))-1))
#define MAX_UNSIGNED(r) ((uint64_t)(((1LL<<(r))-1)))
#define MIN_SIGNED(r) ((int64_t)((1LL<<((r)-1))))
