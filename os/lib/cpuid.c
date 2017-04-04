#include <stdint.h>
#include "cpuid.h"
#include <lib/klib.h>


void cpuid(uint32_t code, uint32_t *a, uint32_t *d) {
	asm volatile("cpuid"
		     : "=a"(*a), "=d"(*d)	/* output operands */
		     : "a"(code)		/* input operands */
		     : "ecx", "ebx");		/* clobbers */
}
