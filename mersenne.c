#include "mersenne.h"

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

uint32_t mt_rand(void) {
  if (mt_index >= MT_LEN) {
    if (mt_index > MT_LEN)
      mt_srand(5489UL); // Default seed
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
