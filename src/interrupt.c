#include "lib/klib.h"
#include "interrupt.h"
#include "idt.h"
#include <cpuid.h>



void interrupt_init()
{
	idt_init();
	// pic_init();
}
