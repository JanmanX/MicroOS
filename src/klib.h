#ifndef KLIB_H
#define KLIB_H

#include <stdint.h>

void itoa(char *buf, int base, int64_t n);

extern void kpanic();

/* DEBUG FUNCTIONS
 * Should not be used in production */
#define BOCHS_DEBUG do {\
			asm volatile("xchg bx, bx");\
		} while(0);


#define HALT asm volatile("hlt")

#endif /* KLIB_H */
