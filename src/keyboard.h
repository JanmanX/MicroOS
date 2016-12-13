#ifndef KEYBOARD_H
#define KEYBOARD_H

/* x86 PS/2 */
#define PS2_KB_DATA	0x60
#define PS2_KB_STATUS	0x64

/* PS/2 keycodes */
/* http://wiki.osdev.org/PS/2_Keyboard#Driver_Model */
#define PS2_KB_INTERFACETEST		0xAB
#define PS2_KB_IDENTIFY			0xF2
#define PS2_KB_ENABLE_SCANNING		0xF3
#define PS2_KB_DISABLE_SCANNING		0xF5
#define PS2_KB_ACK			0xFA
#define PS2_KB_RESEND_LAST		0xFE

/* To poll, wait until bit 0 of the Status Register becomes set, then read the
 * received byte of data from IO Port 0x60.
 *
 * http://wiki.osdev.org/%228042%22_PS/2_Controller#Recieving_Bytes_From_Device.2Fs
 */
#define PS2_KB_OUTPUT_READY		0x1

/* Poll bit 1 of the Status Register ("Input buffer empty/full") until it
 * becomes clear, or until your time-out expires */
#define PS2_KB_INPUT_READY	        0x2



#define KB_IRQ		0x21	/* 33 */
#define KB_DEV_NAME	"KEYBOARD"
#define KB_PIC_LINE	0x01	/* Keyboard sit at IRQ 1 on PIC */

void keyboard_init();
void keyboard_interrupt_handler(void);

extern void _keyboard_interrupt_handler(void);

#endif /* KEYBOARD_H */
