#ifndef MERSENNE_H
#define MERSENNE_H

#include <stdint.h>

void mt_srand(uint32_t seed);
void mt_init_with_time(void);
uint32_t mt_rand(void);
uint32_t mt_rand_range(uint32_t min, uint32_t max);

#endif // MERSENNE_H
