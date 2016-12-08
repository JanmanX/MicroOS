#ifndef KLIB_H
#define KLIB_H

#include <stdint.h>

#include "lib/cpuid.h"

void itoa(char *buf, int base, int64_t n);

extern void kpanic();


/* Printing routines */
enum color {
	BLACK = 0x0,
	BLUE = 0x1,
	GREEN = 0x2,
	CYAN = 0x3,
	RED = 0x4,
	MAGENTA = 0x5,
	BROWN = 0x6,
	LIGHT_GRAY = 0x7,
	DARK_GRAY = 0x8,
	LIGHT_BLUE = 0x9,
	LIGHT_GREEN = 0xA,
	LIGHT_CYAN = 0xB,
	LIGHT_RED = 0xC,
	LIGHT_MAGENTA = 0xD,
	YELLOW = 0XE,
	WHITE = 0XF,
};

/* Clears the screen */
void clear_screen();

/* Non-formatted kernel print */
void kprint(char *str);

/* Formatted kernel print
 * WARN: Can only parse 5 varargs!  */
void kprintf(const char *fmt, ...);



uint8_t inb(uint16_t port);
void outb(uint16_t, uint8_t val);

/* DEBUG FUNCTIONS
 * Should not be used in production */
#define BOCHS_DEBUG do {\
			asm volatile("xchg %bx, %bx");\
		} while(0);


#define HALT asm volatile("hlt")




#endif /* KLIB_H */
