#include <stdint.h>
#include "keyboard.h"
#include "interrupt.h"
#include "lib/klib.h"
#include "lib/circ_buf.h"
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

static volatile uint8_t key_down = 0;
static volatile uint8_t shift = 0;
static volatile uint8_t ctrl = 0;

/* Circular buffer */
static uint8_t _key_buffer[KB_KEY_BUFFER];
static circ_buf_t key_buffer;


static uint8_t key_map_lower[] = { 0x00, 0, '1', '2', '3', '4', '5', '6', '7',
	'8', '9', '0', '-', '=', 0x0e, 0, 'q', 'w', 'e', 'r', 't', 'y', 'u',
	'i', 'o', 'p', '[', ']', 0x1c, 0, 'a', 's', 'd', 'f', 'g', 'h', 'j',
	'k', 'l', ';', 0x27, '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm',
	',', '.', '/', 0, 0, 0, ' ', 0 };

static uint8_t key_map_upper[] = { 0x00, 0, '!', '@', '#', '$', '%', '^', '&',
	'*', '(', ')', '_', '+', 0x0e, 0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U',
	'I', 'O', 'P', '{', '}', 0x1c, 0, 'A', 'S', 'D', 'F', 'G', 'H', 'J',
	'K', 'L', ':', 0x22, '~', 0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	'<', '>', '?', 0, 0, 0, ' ', 0 };

static uint16_t scanmap_normal[KB_SCAN_CODES] = {
	[0x01] = INPUT_KEY_ESCAPE		,
	[0x02] = INPUT_KEY_1			,
	[0x03] = INPUT_KEY_2			,
	[0x04] = INPUT_KEY_3			,
	[0x05] = INPUT_KEY_4			,
	[0x06] = INPUT_KEY_5			,
	[0x07] = INPUT_KEY_6			,
	[0x08] = INPUT_KEY_7			,
	[0x09] = INPUT_KEY_8			,
	[0x0A] = INPUT_KEY_9			,
	[0x0B] = INPUT_KEY_0			,
	[0x0C] = INPUT_KEY_DASH			,
	[0x0D] = INPUT_KEY_EQUAL		       ,
	[0x0E] = INPUT_KEY_BACKSPACE		,
	[0x0F] = INPUT_KEY_TAB			,
	[0x10] = INPUT_KEY_Q			,
	[0x11] = INPUT_KEY_W			,
	[0x12] = INPUT_KEY_E			,
	[0x13] = INPUT_KEY_R			,
	[0x14] = INPUT_KEY_T			,
	[0x15] = INPUT_KEY_Y			,
	[0x16] = INPUT_KEY_U			,
	[0x17] = INPUT_KEY_I			,
	[0x18] = INPUT_KEY_O			,
	[0x19] = INPUT_KEY_P			,
	[0x1A] = INPUT_KEY_OPEN_BRACKET		,
	[0x1B] = INPUT_KEY_CLOSE_BRACKET	       ,
	[0x1C] = INPUT_KEY_ENTER		       ,
	[0x1D] = INPUT_KEY_LEFT_CTRL		,
	[0x1E] = INPUT_KEY_A			,
	[0x1F] = INPUT_KEY_S			,
	[0x20] = INPUT_KEY_D			,
	[0x21] = INPUT_KEY_F			,
	[0x22] = INPUT_KEY_G			,
	[0x23] = INPUT_KEY_H			,
	[0x24] = INPUT_KEY_J			,
	[0x25] = INPUT_KEY_K			,
	[0x26] = INPUT_KEY_L			,
	[0x27] = INPUT_KEY_SEMICOLON		,
	[0x28] = INPUT_KEY_APOSTROPH		,
	[0x29] = INPUT_KEY_GRAVE_ACCENT		,
	[0x2A] = INPUT_KEY_LEFT_SHIFT		,
	[0x2B] = INPUT_KEY_BACKSLASH		,
	[0x2C] = INPUT_KEY_Z			,
	[0x2D] = INPUT_KEY_X			,
	[0x2E] = INPUT_KEY_C			,
	[0x2F] = INPUT_KEY_V			,
	[0x30] = INPUT_KEY_B			,
	[0x31] = INPUT_KEY_N			,
	[0x32] = INPUT_KEY_M			,
	[0x33] = INPUT_KEY_COMMA		       ,
	[0x34] = INPUT_KEY_PERIOD		,
	[0x35] = INPUT_KEY_SLASH		       ,
	[0x36] = INPUT_KEY_RIGHT_SHIFT		,
	[0x37] = INPUT_KEY_KP_STAR		,
	[0x38] = INPUT_KEY_LEFT_ALT		,
	[0x39] = INPUT_KEY_SPACEBAR		,
	[0x3A] = INPUT_KEY_CAPS_LOCK		,
	[0x3B] = INPUT_KEY_F1			,
	[0x3C] = INPUT_KEY_F2			,
	[0x3D] = INPUT_KEY_F3			,
	[0x3E] = INPUT_KEY_F4			,
	[0x3F] = INPUT_KEY_F5			,
	[0x40] = INPUT_KEY_F6			,
	[0x41] = INPUT_KEY_F7			,
	[0x42] = INPUT_KEY_F8			,
	[0x43] = INPUT_KEY_F9			,
	[0x44] = INPUT_KEY_F10			,
	[0x45] = INPUT_KEY_NUM_LOCK		,
	[0x46] = INPUT_KEY_SCROLL_LOCK		,
	[0x47] = INPUT_KEY_KP_7			,
	[0x48] = INPUT_KEY_KP_8			,
	[0x49] = INPUT_KEY_KP_9			,
	[0x4A] = INPUT_KEY_KP_DASH		,
	[0x4B] = INPUT_KEY_KP_4			,
	[0x4C] = INPUT_KEY_KP_5			,
	[0x4D] = INPUT_KEY_KP_6			,
	[0x4E] = INPUT_KEY_KP_PLUS		,
	[0x4F] = INPUT_KEY_KP_1			,
	[0x50] = INPUT_KEY_KP_2			,
	[0x51] = INPUT_KEY_KP_3			,
	[0x52] = INPUT_KEY_KP_0			,
	[0x53] = INPUT_KEY_KP_PERIOD		,
	[0x54] = INPUT_KEY_SYSREQ		,
	[0x56] = INPUT_KEY_EUROPE_2		,
	[0x57] = INPUT_KEY_F11			,
	[0x58] = INPUT_KEY_F12			,
	[0x59] = INPUT_KEY_KP_EQUAL		,
	[0x5C] = INPUT_KEY_I10L_6		,
	[0x64] = INPUT_KEY_F13			,
	[0x65] = INPUT_KEY_F14			,
	[0x66] = INPUT_KEY_F15			,
	[0x67] = INPUT_KEY_F16			,
	[0x68] = INPUT_KEY_F17			,
	[0x69] = INPUT_KEY_F18			,
	[0x6A] = INPUT_KEY_F19			,
	[0x6B] = INPUT_KEY_F20			,
	[0x6C] = INPUT_KEY_F21			,
	[0x6D] = INPUT_KEY_F22			,
	[0x6E] = INPUT_KEY_F23			,
	[0x70] = INPUT_KEY_I10L_2		,
	/* The following two keys (0x71, 0x72) are release-only. */
	[0x71] = INPUT_KEY_LANG_2		,
	[0x72] = INPUT_KEY_LANG_1		,
	[0x73] = INPUT_KEY_I10L_1		,
	/* The following key (0x76) can be either F24 or LANG_5. */
	[0x76] = INPUT_KEY_F24			,
	[0x77] = INPUT_KEY_LANG_4		,
	[0x78] = INPUT_KEY_LANG_3		,
	[0x79] = INPUT_KEY_I10L_4		,
	[0x7B] = INPUT_KEY_I10L_5		,
	[0x7D] = INPUT_KEY_I10L_3		,
	[0x7E] = INPUT_KEY_EQUAL_SIGN		,
};

static uint16_t scanmap_escaped[KB_SCAN_CODES] = {
	[0x10] = INPUT_CONS_SCAN_PREVIOUS_TRACK	,
	[0x19] = INPUT_CONS_SCAN_NEXT_TRACK	,
	[0x1C] = INPUT_KEY_KP_ENTER		,
	[0x1D] = INPUT_KEY_RIGHT_CTRL		,
	[0x20] = INPUT_CONS_MUTE		       ,
	[0x21] = INPUT_CONS_AL_CALCULATOR	,
	[0x22] = INPUT_CONS_PLAY_PAUSE		,
	[0x24] = INPUT_CONS_STOP		       ,
	[0x2E] = INPUT_CONS_VOLUME_DOWN		,
	[0x30] = INPUT_CONS_VOLUME_UP		,
	[0x32] = INPUT_CONS_AC_HOME		,
	[0x35] = INPUT_KEY_KP_SLASH		,
	[0x37] = INPUT_KEY_PRINT_SCREEN		,
	[0x38] = INPUT_KEY_RIGHT_ALT		,
	[0x46] = INPUT_KEY_PAUSE		       ,
	[0x47] = INPUT_KEY_HOME			,
	[0x48] = INPUT_KEY_UP_ARROW		,
	[0x49] = INPUT_KEY_PAGE_UP		,
	[0x4B] = INPUT_KEY_LEFT_ARROW		,
	[0x4D] = INPUT_KEY_RIGHT_ARROW		,
	[0x4F] = INPUT_KEY_END			,
	[0x50] = INPUT_KEY_DOWN_ARROW		,
	[0x51] = INPUT_KEY_PAGE_DOWN		,
	[0x52] = INPUT_KEY_INSERT		,
	[0x53] = INPUT_KEY_DELETE		,
	[0x5B] = INPUT_KEY_LEFT_GUI		,
	[0x5C] = INPUT_KEY_RIGHT_GUI		,
	[0x5D] = INPUT_KEY_APPLICATION		,
	/* The following extended key (0x5E) may also be INPUT_KEY_POWER. */
	//	[0x5E] = INPUT_GD_SYSTEM_POWER_DOWN,
	//	[0x5F] = INPUT_GD_SYSTEM_SLEEP	   ,
	//	[0x63] = INPUT_GD_SYSTEM_WAKE_UP          ,
	//	[0x65] = INPUT_CONS_AC_SEARCH	   ,
	//	[0x66] = INPUT_CONS_AC_BOOKMARKS          ,
	//	[0x67] = INPUT_CONS_AC_REFRESH	   ,
	//	[0x68] = INPUT_CONS_AC_STOP	   ,
	//	[0x69] = INPUT_CONS_AC_FORWARD	   ,
	//	[0x6A] = INPUT_CONS_AC_BACK	   ,
	//	[0x6B] = INPUT_CONS_AL_LOCAL_BROWSE,
	//	[0x6C] = INPUT_CONS_AL_EMAIL_READER,
	//	[0x6D] = INPUT_CONS_AL_MEDIA_SELECT,
};


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
	OUTB(PS2_KB_DATA, data);

	/* Wait for output */
	KB_WAIT_OUTPUT_BUSY;

	/* Return output */
	return inb(PS2_KB_DATA);
}


void keyboard_init()
{
	/* Setup buffer */
	circ_buf_init(&key_buffer, _key_buffer, 1, KB_KEY_BUFFER, 0);

	/* Empty the PS/2 buffer */
	while(keyboard_status() & PS2_KB_OUTPUT_READY) {
		inb(PS2_KB_DATA);
	}

	/* Reset & disable scan */
	if(keyboard_send(PS2_KB_DISABLE_SCANNING) != PS2_KB_ACK) {
		DEBUG("Could not disable keyboard scanning");
		return;
	}

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

	/* Request interrupt */
	request_irq(KB_IRQ,
		    (interrupt_handler_t)_keyboard_interrupt_handler,
		    KB_DEV_NAME);

	/* Enable PIC interrupt line */
	pic_clear_mask(KB_PIC_LINE);

}


void keyboard_interrupt_handler()
{
	uint8_t code = keyboard_read();

	/* Extended keys ignored */
	if((code == SCAN_EXT0) || (code == SCAN_EXT1)) {
		return (char)0x00;
	}

	/* Is key pressed */
	if(code & SCAN_RELEASE) {
		key_down = 0;
	} else {
		key_down = 1;
	}


	switch(code) {
	case INPUT_KEY_RIGHT_SHIFT:
	case INPUT_KEY_LEFT_SHIFT:
		shift = key_down ? 1 : 0;
		break;


	case INPUT_KEY_LEFT_CTRL:
	case INPUT_KEY_RIGHT_CTRL:
		ctrl = key_down ? 1 : 0;
		break;

	default:
		{
			if(key_down) {
				if(shift) {
					code = key_map_upper[code];
				} else {
					code = key_map_lower[code];
				}

				/* Save the code */
				circ_buf_push(&key_buffer, &code);

			} else {
				code = 0;
			}
		}
	}

	/* Send End Of Interrupt to PIC */
	pic_eoi(KB_PIC_LINE);
}

char keyboard_get_key()
{
	char ret = 0;

	circ_buf_pop(&key_buffer, &ret);

	return ret;
}

uint64_t keyboard_keys_available(void)
{
	return key_buffer.count;
}


