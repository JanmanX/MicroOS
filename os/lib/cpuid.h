#ifndef _CPUID_H
#define _CPUID_H

#include <stdint.h>
#include <lib/klib.h>

void cpuid(uint32_t code, uint32_t *a, uint32_t *d);


/* Functions */
#define CPUID_FEATURES			0x01
#define CPUID_EXTENDED_FEATURES		0x80000001


/* Register bits */
#define CPUID_EDX_GBYTE_PAGING		((1 << 26))
#define CPUID_EDX_LAPIC			((1 << 9 ))

#endif /* _CPUID_H */
