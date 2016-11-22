#ifndef KPRINT_H
#define KPRINT_H

#include <stdint.h>

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

#endif /* KPRINT_H */
