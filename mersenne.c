#include "mersenne.h"
#include <time.h>

#define MT_LEN 624
static uint32_t mt[MT_LEN];
static int mt_index = MT_LEN + 1;

void mt_srand(uint32_t seed) {
  mt[0] = seed;
  for (int i = 1; i < MT_LEN; i++) {
    // Japanese magic
    mt[i] = (1812433253UL * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i);
  }
  mt_index = MT_LEN;
}

void mt_init_with_time(void) {
  // init in sec from 1 jan 1970
  mt_srand((uint32_t)time(NULL));
}

uint32_t mt_rand(void) {
  if (mt_index >= MT_LEN) {
    if (mt_index > MT_LEN)
      mt_init_with_time(); // fallback
    for (int i = 0; i < MT_LEN; i++) {
      uint32_t y =
          (mt[i] & 0x80000000UL) | (mt[(i + 1) % MT_LEN] & 0x7fffffffUL);
      mt[i] = mt[(i + 397) % MT_LEN] ^ (y >> 1);
      if (y % 2 != 0)
        mt[i] ^= 2567483615UL;
    }
    mt_index = 0;
  }
  uint32_t y = mt[mt_index++];
  y ^= (y >> 11);
  y ^= (y << 7) & 2636928640UL;
  y ^= (y << 15) & 4022730752UL;
  y ^= (y >> 18);
  return y;
}

uint32_t mt_rand_range(uint32_t mi {
  uint32_t range = max - min + 1;
  uint32_t limit = UINT32_MAX - (UINT32_MIN % range);
  uint32_t random_val;

  do {
    random_val = mt_rand();
  } while (random_val >= limit);

  return min + (random_val % range);
}
