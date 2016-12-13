#include "pic.h"
#include "lib/klib.h"

void pic_init()
{
	/* Remap PIC interrupts */
	pic_remap(PIC1_VECTOR_OFFSET, PIC2_VECTOR_OFFSET);

	/* Send End-Of-Interrupt to both PICs so as to 'reset' interrupts */
	pic_eoi(0x08);
}

void pic_remap(uint8_t offset_master, uint8_t offset_slave)
{
	uint8_t a1, a2;

	/* We do not want to keep the masks
	a1 = inb(PIC1_DATA);
	a2 = inb(PIC2_DATA);
	*/

	/* Starts initialization sequence (in cascade) */
	/* Master PIC */
	outb(PIC1_CMD, ICW1_INIT + ICW1_ICW4);

	/* Slave PIC */
	outb(PIC2_CMD, ICW1_INIT + ICW1_ICW4);

	/* Set vector offsets for the PICs */
	outb(PIC1_DATA, offset_master);	/* ICW2 */
	outb(PIC2_DATA, offset_slave);	/* ICW2	*/

	/* Tell PIC1 (master) that the slave PIC is at IRQ 2 */
	outb(PIC1_DATA, 4);		/* ICW3 */
	outb(PIC2_DATA, 2);		/* ICW3 */


	/* Write ICW4 to PICs, notifying that we are going to write to them */
	outb(PIC1_DATA, ICW4_8086);
	outb(PIC2_DATA, ICW4_8086);

	outb(PIC1_DATA, 0xFF);
	outb(PIC2_DATA, 0xFF);
}

void pic_set_mask(uint8_t irq_line)
{
	uint16_t port;
	uint8_t value;

	if(irq_line < 8) {
		port = PIC1_DATA;
	} else {
		port = PIC2_DATA;
		irq_line -= 8;
	}

	value = inb(port) | (1 << irq_line);
	outb(port, value);
}

void pic_clear_mask(uint8_t irq_line)
{
	uint16_t port;
	uint8_t value;

	if(irq_line < 8) {
		port = PIC1_DATA;
	} else {
		port = PIC2_DATA;
		irq_line -= 8;
	}

	value = inb(port) & ~(1 << irq_line);
	outb(port, value);
}


uint16_t pic_get_mask(void)
{
	return (inb(PIC2_DATA) << 8 | inb(PIC1_DATA));
}

/* ISR - Interrupt Service Register
 * IRR - Interrupt Request Register */
/* Helper function */
static uint16_t __pic_get_irq_reg(int ocw3)
{
	outb(PIC1_CMD, ocw3);
	outb(PIC2_CMD, ocw3);
	return (inb(PIC2_CMD) << 8) | inb(PIC1_CMD);
}

uint16_t pic_get_irr(void)
{
	__pic_get_irq_reg(PIC_READ_IRR);
}

uint16_t pic_get_irs(void)
{
	__pic_get_irq_reg(PIC_READ_ISR);
}

void pic_eoi(uint8_t irq)
{
	/* If interrupt came from slave PIC, we need to notify both. */
	if(irq >= 8) {
		outb(PIC2_CMD, PIC_EOI);
	}

	outb(PIC1_CMD, PIC_EOI);
}
