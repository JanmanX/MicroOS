#include <stdint.h>
#include <lib/klib.h>
#include "interrupt.h"
#include "idt.h"
#include "gdt.h"


void interrupt_setup_gates()
{
	uint8_t ist = 0;
	uint8_t type = (IDTE_DPL_RING0 | IDTE_PRESENT | IDTE_TYPE_TRAP_32);

	idt_set_interrupt(0,  GDT_KERNEL_CODE_SEGMENT, type, ist, (interrupt_handler_t)interrupt_handler_0);
	idt_set_interrupt(1,  GDT_KERNEL_CODE_SEGMENT, type, ist, (interrupt_handler_t)interrupt_handler_1);
	idt_set_interrupt(2,  GDT_KERNEL_CODE_SEGMENT, type, ist, (interrupt_handler_t)interrupt_handler_2);
	idt_set_interrupt(3,  GDT_KERNEL_CODE_SEGMENT, type, ist, (interrupt_handler_t)interrupt_handler_3);
	idt_set_interrupt(4,  GDT_KERNEL_CODE_SEGMENT, type, ist, (interrupt_handler_t)interrupt_handler_4);
	idt_set_interrupt(5,  GDT_KERNEL_CODE_SEGMENT, type, ist, (interrupt_handler_t)interrupt_handler_5);
	idt_set_interrupt(6,  GDT_KERNEL_CODE_SEGMENT, type, ist, (interrupt_handler_t)interrupt_handler_6);
	idt_set_interrupt(7,  GDT_KERNEL_CODE_SEGMENT, type, ist, (interrupt_handler_t)interrupt_handler_7);
	idt_set_interrupt(8,  GDT_KERNEL_CODE_SEGMENT, type, ist, (interrupt_handler_t)interrupt_handler_8);
	idt_set_interrupt(9,  GDT_KERNEL_CODE_SEGMENT, type, ist, (interrupt_handler_t)interrupt_handler_9);
	idt_set_interrupt(10,  GDT_KERNEL_CODE_SEGMENT, type, ist,(interrupt_handler_t) interrupt_handler_10);
	idt_set_interrupt(11,  GDT_KERNEL_CODE_SEGMENT, type, ist,(interrupt_handler_t) interrupt_handler_11);
	idt_set_interrupt(12,  GDT_KERNEL_CODE_SEGMENT, type, ist,(interrupt_handler_t) interrupt_handler_12);
	idt_set_interrupt(13,  GDT_KERNEL_CODE_SEGMENT, type, ist,(interrupt_handler_t) interrupt_handler_13);
	idt_set_interrupt(14,  GDT_KERNEL_CODE_SEGMENT, type, ist,(interrupt_handler_t) interrupt_handler_14);
	idt_set_interrupt(15,  GDT_KERNEL_CODE_SEGMENT, type, ist,(interrupt_handler_t) interrupt_handler_15);
	idt_set_interrupt(16,  GDT_KERNEL_CODE_SEGMENT, type, ist,(interrupt_handler_t) interrupt_handler_16);
	idt_set_interrupt(17,  GDT_KERNEL_CODE_SEGMENT, type, ist,(interrupt_handler_t) interrupt_handler_17);
	idt_set_interrupt(18,  GDT_KERNEL_CODE_SEGMENT, type, ist,(interrupt_handler_t) interrupt_handler_18);
	idt_set_interrupt(19,  GDT_KERNEL_CODE_SEGMENT, type, ist,(interrupt_handler_t) interrupt_handler_19);
	idt_set_interrupt(20,  GDT_KERNEL_CODE_SEGMENT, type, ist,(interrupt_handler_t) interrupt_handler_20);
}

void interrupt_init()
{
	/* Setup Interrupt Descriptor Table */
	idt_init();

	/* Init exception gates here */
	interrupt_setup_gates();

	/* Initialize Programmable Interrupt Controller (PIC) */
	pic_init();

	/* Enable interrupts */
	enable_interrupts();
}


void interrupt_handle(pt_regs_t *regs)
{
	switch((uint8_t)regs->orig_ax) {
	case 0: kprintf("Interrupt handler, IRQ: 0x%x: Divide-by-Zero-Error\n",
			(uint8_t)regs->orig_ax);
		break;
	case 1: kprintf("Interrupt handler, IRQ: 0x%x: Debug\n",
			(uint8_t)regs->orig_ax);
		break;
	case 2: kprintf("Interrupt handler, IRQ: 0x%x: Non-Maskable-Interrupt\n",
			(uint8_t)regs->orig_ax);
		break;
	case 3: kprintf("Interrupt handler, IRQ: 0x%x: Breakpoint \n",
			(uint8_t)regs->orig_ax);
		break;
	case 4: kprintf("Interrupt handler, IRQ: 0x%x: Overflow\n",
			(uint8_t)regs->orig_ax);
		break;
	case 5: kprintf("Interrupt handler, IRQ: 0x%x: Bound-Range\n",
			(uint8_t)regs->orig_ax);
		break;
	case 6: kprintf("Interrupt handler, IRQ: 0x%x: Invalid-Opcode \n",
			(uint8_t)regs->orig_ax);
		break;
	case 7: kprintf("Interrupt handler, IRQ: 0x%x: Device-Not-Available \n",
			(uint8_t)regs->orig_ax);
		break;
	case 8: kprintf("Interrupt handler, IRQ: 0x%x: Double-Fault\n",
			(uint8_t)regs->orig_ax);
		break;
	case 9: kprintf("Interrupt handler, IRQ: 0x%x: Coprocessor-Segment-Ovnvalid-TSS\n",
			(uint8_t)regs->orig_ax);
		break;
	case 11: kprintf("Interrupt handler, IRQ: 0x%x: Segment-Not-Present\n",
			 (uint8_t)regs->orig_ax);
		 break;
	case 12: kprintf("Interrupt handler, IRQ: 0x%x: Stack\n",
			 (uint8_t)regs->orig_ax);
		 break;
	case 13: kprintf("Interrupt handler, IRQ: 0x%x: General-Protection #Gccesses and protection checks\n",
			 (uint8_t)regs->orig_ax);
		 break;
	case 14: kprintf("Interrupt handler, IRQ: 0x%x: Page-Fault\n",
			 (uint8_t)regs->orig_ax);
		 break;
	case 15: kprintf("Interrupt handler, IRQ: 0x%x: Reserved 16 x87 FloatException-Pending \n",
			 (uint8_t)regs->orig_ax);
		 break;
	case 17: kprintf("Interrupt handler, IRQ: 0x%x: Alignment-Check \n",
			 (uint8_t)regs->orig_ax);
		 break;
	case 18: kprintf("Interrupt handler, IRQ: 0x%x: Machine-Check \n",
			 (uint8_t)regs->orig_ax);
		 break;
	case 19: kprintf("Interrupt handler, IRQ: 0x%x: SIMD Floating-Point \n",
			 (uint8_t)regs->orig_ax);
		 break;
	case 20: kprintf("Interrupt handler, IRQ: 0x%x: Unsupported \n",
			 (uint8_t)regs->orig_ax);
		 break;
	case 30: kprintf("Interrupt handler, IRQ: 0x%x: Security Exception\n",
			 (uint8_t)regs->orig_ax);
		 break;
	case 31: kprintf("Interrupt handler, IRQ: 0x%x: Reserved\n",
			 (uint8_t)regs->orig_ax);
		 break;

	default:
		kprintf("Interrupt handler, IRQ: 0x%x\n", (uint8_t)regs->orig_ax);
	}
}

void request_irq(uint8_t irq, interrupt_handler_t irq_handler, char *name)
{
	if(irq < 32) {
		kprintf("Could not register interrupt routine: %d for %s\n",irq,
			name);
		HALT;
	}

	idt_set_interrupt(irq,
			  GDT_KERNEL_CODE_SEGMENT,
			(IDTE_DPL_RING0 | IDTE_PRESENT | IDTE_TYPE_TRAP_32),
			0x00,
			irq_handler);
}


