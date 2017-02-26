#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define MAX_INTERRUPTS 0xFF

/* IDT Entries */
#define IDTE_TYPE_TRAP_32		0xF
#define IDTE_TYPE_INTERRUPT_32		0xE
#define IDTE_TYPE_TRAP_16		0x7
#define IDTE_TYPE_INTERRUPT_16		0x6
#define IDTE_TYPE_TASK_16		0x5
#define IDTE_PRESENT			(0x1 << 7)
#define IDTE_DPL_RING0			(0x0 << 5)
#define IDTE_DPL_RING1			(0x1 << 5)
#define IDTE_DPL_RING2			(0x2 << 5)
#define IDTE_DPL_RING3			(0x3 << 5)


/*
 * The IST and type_attr fields
 *                                                               (+4 bytes)
 16                               8                               0
  +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
  | P |  DPL  | Z |     Type      |        Zero       |    IST    |
  +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *
 */

typedef void (*exception_gate_t)(void);


/* Interrupt Descriptor Table (IDT) */
typedef struct idt {
	/* Length of IDT in bytes - 1 */
	uint16_t limit;

	/* Linear address of start of IDT (gate 0) */
	uint64_t base;
}__attribute__((packed)) idt_t;


/* IDT entry = Exception gates */
#define IDT_DESCRIPTOR_SIZE
typedef struct idt_desc {
	/* Offset bits [0,15] */
	uint16_t offset_1;

	/* Code segment selector in GDT or LDT */
	uint16_t selector;

	/* Interrupt Stack Table offset
	 * Bits [0,2], rest is zero */
	uint8_t ist;

	/* Types and Attributes */
	uint8_t type_attr;

	/* Offset bits [16, 31]*/
	uint16_t offset_2; // offset bits 16..31

	/* Offset bits [32, 63] */
	uint32_t offset_3;

	/* Reserved */
	uint32_t zero;
}__attribute__((packed))  idt_desc_t;


/* Initializes the IDT */
void idt_init();

/* Sets an exception gate in the IDT */
void idt_set_interrupt(uint32_t index, uint16_t selector, uint8_t type_attr,
		uint8_t ist, exception_gate_t exception_gate);

#endif /* X86_64_IDT_H */
