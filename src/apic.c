#include <stdint.h>
#include "cpu.h"
#include "apic.h"

#if 0
uint8_t check_apic() {
	uint32_t eax, edx;
	cpuid(1, &eax, &edx);
	return edx & CPUID_FEAT_EDX_APIC;
}

/* Set the physical address for local APIC registers */
void cpu_set_apic_base(uintptr_t apic) {
	uint32_t edx = 0;
	uint32_t eax = (apic & 0xfffff000) | IA32_APIC_BASE_MSR_ENABLE;

#ifdef __PHYSICAL_MEMORY_EXTENSION__
	edx = (apic >> 32) & 0x0f;
#endif

	cpu_set_msr(IA32_APIC_BASE_MSR, eax, edx);
}

/**
 * Get the physical address of the APIC registers page
 * make sure you map it to virtual memory ;)
 */
uint64_t cpu_get_apic_base() {
	uint32_t eax, edx;
	cpu_get_msr(IA32_APIC_BASE_MSR, &eax, &edx);

	return (eax & 0xfffff000) | ((edx & 0x0f) << 32);
	return (eax & 0xfffff000);
}

void enable_apic() {
	/* Hardware enable the Local APIC if it wasn't enabled */
	cpu_set_apic_base(cpu_get_apic_base());

	/* Set the Spourious Interrupt Vector Register bit 8 to start receiving interrupts */
	write_reg(0xF0, ReadRegister(0xF0) | 0x100);
}
#endif
