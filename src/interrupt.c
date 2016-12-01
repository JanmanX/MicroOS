#include "interrupt.h"
#include "idt.h"

void interrupt_init()
{
	idt_init();
	// pic_init();
}
