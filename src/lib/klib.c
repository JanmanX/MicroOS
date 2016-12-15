#include <stdint.h>

#include "lib/klib.h"



void update_cursor(int row, int col)
{
	unsigned short position=(row*80) + col;

	// cursor LOW port to vga INDEX register
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char)(position&0xFF));
	// cursor HIGH port to vga INDEX register
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char)((position>>8)&0xFF));
}


void itoa(char *buf, int base, int64_t n)
{
	char *p = buf;
	char *p1, *p2;
	uint64_t un = n;
	int div = 10;

	if(base == 'd' && n < 0) {
		*p++ = '-';
		un = -n;
		buf++;
	} else if (base == 'x') {
		div = 16;
	}

	do {
		/* calculate remainder */
		int r = un % div;

		*p++ = (r < 10) ? r + '0' : r + 'a' - 10;
	} while(un /= div);

	/* Terminate string */
	*p = 0;

	/* Reverse the string */
	p1 = buf;
	p2 = p - 1;


	while(p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;

	}
}

#define VGA_ADDRESS	0xB8000
static uint8_t *vga_buffer = (uint8_t*)VGA_ADDRESS;
static uint8_t vga_buffer_x = 0x00;
static uint8_t vga_buffer_y = 0x00;

/* Upper nibble = back colour
 * Lower nibble = fore colour */
static uint8_t vga_attrib = (LIGHT_CYAN)|(BLACK << 4);

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
	if(vga_buffer_y >= 25) {
		clear_screen();
		vga_buffer_x = 0;
		vga_buffer_y = 0;
	}

	if(c == '\n') {
		vga_buffer_y++;
		vga_buffer_x = 0;
	} else {
		uint16_t *addr = (uint16_t*)VGA_ADDRESS
			+ (vga_buffer_y * 80 + vga_buffer_x);
		*addr = c | (uint16_t)(vga_attrib << 8);

		vga_buffer_x++;

		if(vga_buffer_x >= 80) {
			vga_buffer_x = 0;
			vga_buffer_y++;
		}
	}

	update_cursor(vga_buffer_x, vga_buffer_y);
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

void *memcpy(void *dst, void *src, uint64_t count)
{
	char* _dst = (char*)dst;
	char* _src = (char*)src;

	while (count--) {
		*_dst++ = *_src++;
	}
	return dst;
}


uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile ( "inb %1, %0"
		       : "=a"(ret)
		       :
		       "Nd"(port)
		     );
	return ret;
}


void outb(uint16_t port, uint8_t val)
{
	asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

/* XXX: Do not use. Intended for *old* machines (25+ years) */
inline void io_wait(void)
{
	/* TODO: This is probably fragile. */
	asm volatile ( "jmp 1f\n\t"
		       "1:jmp 2f\n\t"
		       "2:" );
}

void _pause(void)
{
	asm volatile ( "pause" );
}
