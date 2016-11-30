#include <stdint.h>
#include "idt.h"

/* Interrupt Descriptor Table */
static idt_t idt;

/* Exception gates */
static idt_desc_t idt_descriptors[MAX_INTERRUPTS];

/* Initializes IDT */
void idt_init()
{
	idt.limit = (uint16_t)(MAX_INTERRUPTS * IDT_DESCRIPTOR_SIZE - 1);
	idt.base = (uint64_t) &idt_descriptors;

	/* Load IDT */
	asm volatile("lidt (%0)"			/* instructions */
		     :					/* output operands */
		     : "r"((uint64_t)&idt));		/* input operands */
}

/* Sets an exception gate */
void idt_set_interrupt(uint32_t index, uint16_t selector, uint8_t type_attr,
		       exception_gate_t exception_gate)
{
	index = index;
}

