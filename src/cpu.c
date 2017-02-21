#include <stdint.h>
#include "cpu.h"

/* issue a single request to CPUID. Fits 'intel features', for instance
 *  note that even if only "eax" and "edx" are of interest, other registers
 *  will be modified by the operation, so we need to tell the compiler about it.
 */
inline void cpuid(int code, uint32_t *a, uint32_t *d)
{
	asm volatile("cpuid":"=a"(*a),"=d"(*d):"a"(code):"ecx","ebx");
}

/** issue a complete request, storing general registers output as a string
 *  */
inline int cpuid_string(int code, uint32_t where[4])
{
	asm volatile("cpuid":"=a"(*where),"=b"(*(where+1)),
		     "=c"(*(where+2)),"=d"(*(where+3)):"a"(code));
	return (int)where[0];
}


uint8_t cpu_has_msr()
{
	uint32_t a, d; // eax, edx
	cpuid(1, &a, &d);
	return d & CPUID_FLAG_MSR;
}

void cpu_get_msr(uint32_t msr, uint32_t *lo, uint32_t *hi)
{
	asm volatile("rdmsr" : "=a"(*lo), "=d"(*hi) : "c"(msr));
}

void cpu_set_msr(uint32_t msr, uint32_t lo, uint32_t hi)
{
	asm volatile("wrmsr" : : "a"(lo), "d"(hi), "c"(msr));
}


