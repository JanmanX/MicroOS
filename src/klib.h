#ifndef KLIB_H
#define KLIB_H

#include <stdint.h>

void itoa(char *buf, int base, int64_t n);

extern void kpanic();
#endif /* KLIB_H */
