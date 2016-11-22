#include "kprint.h"
#include "klib.h"

uint8_t *vga_buffer = (uint8_t*)0xB8000;
uint8_t vga_buffer_x = 0x00;
uint8_t vga_buffer_y = 0x00;
/* Upper nibble = back colour
 * Lower nibble = fore colour */
uint8_t vga_attrib = (YELLOW)|(DARK_GRAY << 4);

void clear_screen()
{
	uint16_t *vga_buffer = (uint16_t*)0xB8000;
	register unsigned int i = 0;
	for(i = 0; i < (80*25); i++) {
		*vga_buffer++ = (uint16_t)0x00;
	}

	vga_buffer_x = 0;
	vga_buffer_y = 0;
}

void set_color(uint8_t foreground, uint8_t background)
{
	vga_attrib = (foreground) | (background << 4);
}


void write_char(uint8_t c)
{
	if(c == '\n') {
		vga_buffer_y++;
		vga_buffer_x = 0;
	} else {
		uint16_t *addr = (uint16_t*)0xB8000
					+ (vga_buffer_y * 80 + vga_buffer_x);
		*addr = c | (uint16_t)(vga_attrib << 8);

		vga_buffer_x++;

		if(vga_buffer_x >= 80) {
			vga_buffer_x = 0;
			vga_buffer_y++;
		}
	}

	if(vga_buffer_y >= 25) {
		vga_buffer_x = 0;
		vga_buffer_y = 0;
	}
}

void kprint(char *str)
{
	uint8_t c;
	while((c = *str++) != 0) {
		write_char(c);
	}
}

// XXX
// XXX
// XXX
void kprintf(const char *fmt, ...)
{
	/* Since we are working with AMD64-like ABI, varargs are stored in
	 * registers, not stack. */
#define MAX_ARGS	5

	uint64_t _arg[MAX_ARGS] = {0};

	/* Used to maintain count of varargs consumed */
	uint64_t args_consumed = 0;

	register uint64_t rsi asm("rsi");
	register uint64_t rdx asm("rdx");
	register uint64_t rcx asm("rcx");
	register uint64_t r8 asm("r8");
	register uint64_t r9 asm("r9");
	_arg[0] = rsi;
	_arg[1] = rdx;
	_arg[2] = rcx;
	_arg[3] = r8;
	_arg[4] = r9;
	uint64_t *arg = _arg;


	uint8_t c;
	char buf[24];

	while((c = *fmt++) != 0)
	{
		if(args_consumed >= MAX_ARGS) {
			write_char(c);
			continue;
		}

		if( c != '%') {
			write_char(c);
			continue;
		}

		/* Get the character after '%' */
		c = *fmt++;
		char *s;


		switch(c) {
		case 'd':
		case 'u':
		case 'x':
			itoa(buf, c, (int64_t)*arg++);

			s = buf;
			goto string;

		case 's':
			s = *arg++;

			if(!s) {
				s = "(NULL)";
			}
			/* Fall through */
			/* goto string; */
		string:
			kprint(s);
			break;
		default:
			write_char(arg++);
			break;
		}


		++args_consumed;
	}
}
