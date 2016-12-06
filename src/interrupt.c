#include <stdint.h>
#include "lib/klib.h"
#include "interrupt.h"
#include "idt.h"
#include <cpuid.h>
#include "gdt.h"




void interrupt_setup_gates()
{
	uint8_t ist = 0;
	uint8_t type = (IDTE_DPL_RING0 | IDTE_PRESENT | IDTE_TYPE_TRAP_32);

	idt_set_interrupt(0,  GDT_KERNEL_CODE_SEGMENT, type, ist, (exception_gate_t)exception_gate_0);
	idt_set_interrupt(1,  GDT_KERNEL_CODE_SEGMENT, type, ist, (exception_gate_t)exception_gate_1);
	idt_set_interrupt(2,  GDT_KERNEL_CODE_SEGMENT, type, ist, (exception_gate_t)exception_gate_2);
	idt_set_interrupt(3,  GDT_KERNEL_CODE_SEGMENT, type, ist, (exception_gate_t)exception_gate_3);
	idt_set_interrupt(4,  GDT_KERNEL_CODE_SEGMENT, type, ist, (exception_gate_t)exception_gate_4);
	idt_set_interrupt(5,  GDT_KERNEL_CODE_SEGMENT, type, ist, (exception_gate_t)exception_gate_5);
	idt_set_interrupt(6,  GDT_KERNEL_CODE_SEGMENT, type, ist, (exception_gate_t)exception_gate_6);
	idt_set_interrupt(7,  GDT_KERNEL_CODE_SEGMENT, type, ist, (exception_gate_t)exception_gate_7);
	idt_set_interrupt(8,  GDT_KERNEL_CODE_SEGMENT, type, ist, (exception_gate_t)exception_gate_8);
	idt_set_interrupt(9,  GDT_KERNEL_CODE_SEGMENT, type, ist, (exception_gate_t)exception_gate_9);
	idt_set_interrupt(10,  GDT_KERNEL_CODE_SEGMENT, type, ist,(exception_gate_t) exception_gate_10);
	idt_set_interrupt(11,  GDT_KERNEL_CODE_SEGMENT, type, ist,(exception_gate_t) exception_gate_11);
	idt_set_interrupt(12,  GDT_KERNEL_CODE_SEGMENT, type, ist,(exception_gate_t) exception_gate_12);
	idt_set_interrupt(13,  GDT_KERNEL_CODE_SEGMENT, type, ist,(exception_gate_t) exception_gate_13);
	idt_set_interrupt(14,  GDT_KERNEL_CODE_SEGMENT, type, ist,(exception_gate_t) exception_gate_14);
	idt_set_interrupt(15,  GDT_KERNEL_CODE_SEGMENT, type, ist,(exception_gate_t) exception_gate_15);
	idt_set_interrupt(16,  GDT_KERNEL_CODE_SEGMENT, type, ist,(exception_gate_t) exception_gate_16);
	idt_set_interrupt(17,  GDT_KERNEL_CODE_SEGMENT, type, ist,(exception_gate_t) exception_gate_17);
	idt_set_interrupt(18,  GDT_KERNEL_CODE_SEGMENT, type, ist,(exception_gate_t) exception_gate_18);
	idt_set_interrupt(19,  GDT_KERNEL_CODE_SEGMENT, type, ist,(exception_gate_t) exception_gate_19);
	idt_set_interrupt(20,  GDT_KERNEL_CODE_SEGMENT, type, ist,(exception_gate_t) exception_gate_20);
}

void interrupt_init()
{
	idt_init();

	// Init exception gates here
	interrupt_setup_gates();


//	enable_interrupts();

	int x = 42 / 0;


	// pic_init();
}


void interrupt_handle(uint8_t irq)
{

}



