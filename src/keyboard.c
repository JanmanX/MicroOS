#include <stdint.h>
#include "keyboard.h"
#include "interrupt.h"
#include "lib/klib.h"
#include "keyboard.h"

/* Waits until keyboard is ready to receive data */
#define KB_WAIT_INPUT_BUSY do {\
	while((inb(PS2_KB_STATUS) & PS2_KB_INPUT_READY)) {\
		_pause();\
	}\
	} while(0)

/* Waits until keyboard can send data */
#define KB_WAIT_OUTPUT_BUSY do {\
	while(!(inb(PS2_KB_STATUS) & PS2_KB_OUTPUT_READY)) {\
		_pause();\
	}\
	} while(0)


static uint8_t key_map_lower[] = {0x00, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0x0e, 0,
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0x1c, 0, 'a',
	's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 0x27, '`', 0, '\\', 'z', 'x',
	'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, 0, 0, ' ', 0};

static uint8_t key_map_upper[] = {0x00, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 0x0e,
   0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 0x1c, 0, 'A',
   'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', 0x22, '~', 0, '|', 'Z', 'X',
   'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, 0, 0, ' ', 0};

//   ; 0e = backspace
//   ; 1c = enter



static uint8_t keyboard_status(void)
{
	return inb(PS2_KB_STATUS);
}

static uint8_t keyboard_read(void)
{
	KB_WAIT_OUTPUT_BUSY;

	return inb(PS2_KB_DATA);
}

static uint8_t keyboard_send(uint8_t data)
{
	/* Wait while keyboard is busy */
	KB_WAIT_INPUT_BUSY;

	/* Send message */
	outb(PS2_KB_DATA, data);

	/* Wait for output */
	KB_WAIT_OUTPUT_BUSY;


	/* Return output */
	return inb(PS2_KB_DATA);
}


void keyboard_init()
{
	while(keyboard_status() & PS2_KB_OUTPUT_READY) {
		inb(PS2_KB_DATA);
	}

	/* Reset & disable scan */
	if(keyboard_send(PS2_KB_DISABLE_SCANNING) != PS2_KB_ACK) {
		DEBUG("Could not disable keyboard scanning");
		return;
	}

	/* TODO: IDENTIFY KEYBOARD HERE*/
	if(keyboard_send(PS2_KB_IDENTIFY) != PS2_KB_ACK) {
		DEBUG("Could not identify PS2 keyboard.");
		return;
	}


	if(keyboard_read() == PS2_KB_INTERFACETEST) {
		keyboard_read();
	} else {
		DEBUG("Could not perform iterfacetest on PS2 keyboard");
		return;
	}

	/* Reset & enable scan */
	if(keyboard_send(PS2_KB_ENABLE_SCANNING) != PS2_KB_ACK) {
		DEBUG("Could not enable keyboard scanning");
		return;
	}

	/* ALL THE LEDS! */
	keyboard_send(0xED);
	keyboard_send(0x7);


	/* Request interrupt */
	request_irq(KB_IRQ,
		    (interrupt_handler_t)_keyboard_interrupt_handler,
		    KB_DEV_NAME);

	/* Enable PIC interrupt line */
	pic_clear_mask(KB_PIC_LINE);

}


void keyboard_interrupt_handler()
{
	char c[2] = {0};
	c[0] = key_map_lower[keyboard_read()];
	kprintf("Keyboard pressed: %s\n", c);
	pic_eoi(KB_PIC_LINE);
}

