#include <stdint.h>

#include "idt.h"
#include "gdt.h"

/* Interrupt Descriptor Table */
static idt_t idt;

/* Exception gates */
static idt_desc_t idt_descriptors[MAX_INTERRUPTS];

extern void interrupt_dummy_handler(void);

/* Initializes IDT */
void idt_init()
{
	idt.limit = (uint16_t)(MAX_INTERRUPTS * IDT_DESCRIPTOR_SIZE - 1);
	idt.base = (uint64_t) &idt_descriptors;

	unsigned int i;
	for(i = 0; i < MAX_INTERRUPTS; i++) {
		idt_set_interrupt(i,
				  GDT_KERNEL_CODE_SEGMENT,
				  (IDTE_DPL_RING0 | IDTE_PRESENT |IDTE_TYPE_TRAP_32),
				 (uint8_t)0x00,
				(exception_gate_t)interrupt_dummy_handler);
	}


	/* Load IDT */
	asm volatile("lidt (%0)"			/* instructions */
		     :					/* output operands */
		     : "r"((uint64_t)&idt));		/* input operands */
}

/* Sets an exception gate */
void idt_set_interrupt(uint32_t index, uint16_t selector, uint8_t type_attr,
			uint8_t ist, exception_gate_t exception_gate)
{
	idt_descriptors[index].selector = selector;

	idt_descriptors[index].ist = ist;

	idt_descriptors[index].type_attr = type_attr;


	uint64_t addr = (uint64_t)exception_gate;
	idt_descriptors[index].offset_1 = (uint16_t)addr & 0xFFFF;
	idt_descriptors[index].offset_2 = (uint16_t)(addr >> 16) & 0xFFFF;
	idt_descriptors[index].offset_3 = (uint16_t)(addr >> 32) & 0xFFFFFFFF;

	idt_descriptors[index].zero = (uint32_t) 0;
}

