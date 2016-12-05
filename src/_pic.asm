[BITS 64]

global pic_is_apic

pic_is_apic:
	; Since CPUID is checked in boot.o, we can safely assume it is available

