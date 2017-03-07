#ifndef KLIB_H
#define KLIB_H

#include <stdint.h>

#include <cpuid.h>

#define NULL ((void*)0x00)

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

void update_cursor(int, int);

/* Non-formatted kernel print */
void kprint(char *str);

/* Formatted kernel print
 * WARN: Can only parse 5 varargs!  */
void kprintf(const char *fmt, ...);

void *memcpy(void *dst, void *src, uint64_t count);
uint8_t memcmp(const uint8_t *s1, const uint8_t *s2, uint64_t n);
void memset(uint8_t *s, uint8_t c, uint64_t n);

void _pause(void);
uint8_t inb(uint16_t port);
uint32_t ind(uint16_t port);
void outb(uint16_t, uint8_t val);
void outd(uint16_t, uint32_t val);

#define OUTB(PORT, VALUE) do {\
		asm volatile ( "outb %0, %1" : : "a"((uint8_t)(VALUE)), "Nd"((uint16_t)(PORT)));\
		} while(0)

#define OUTD(PORT, VALUE) do {\
		asm volatile ( "out %0, %1" : : "a"((uint32_t)(VALUE)), "Nd"((uint16_t)(PORT)));\
		} while(0)

/* Macros, for convenience and avoid confusion...  */
#define INB(PORT) inb(port)
#define IND(PORT) ind(port)


/* DEBUG FUNCTIONS
 * Should not be used in production */
#define BOCHS_DEBUG do {\
			asm volatile("xchg %bx, %bx");\
		} while(0);


#define HALT asm volatile("hlt")

#define LOG(m) kprintf("[LOG %s():%d]: %s\n", __func__, __LINE__, m)

#define DEBUG(m) kprintf("[DEBUG %s():%d]: %s\n", __func__, __LINE__, m)
#define ERROR(m) do {\
		kprintf("[ERROR %s():%d]: %s\n", __func__, __LINE__, m);\
		HALT;\
		} while(0);


#endif /* KLIB_H */
