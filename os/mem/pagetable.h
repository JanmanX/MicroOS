#ifndef _PAGETABLE_H
#define _PAGETABLE_H

#include <stdint.h>

/* Page-Map Level 4 Table */
typedef struct pml4e {
	uint8_t p:1;
	uint8_t rw:1;
	uint8_t us:1;
	uint8_t pwt:1;
	uint8_t pcd:1;
	uint8_t a:1;
	uint8_t ign:1;
	uint8_t mbz:2;
	uint8_t avl:3;
	uint64_t base_address:40;
	uint16_t _available:11;
	uint8_t nx:1;
} __attribute__((packed)) pml4e_t;

/* Page Directory Pointer Table */
typedef struct pdpe {
	uint8_t p:1;
	uint8_t rw:1;
	uint8_t us:1;
	uint8_t pwt:1;
	uint8_t pcd:1;
	uint8_t a:1;
	uint8_t ign:1;
	uint8_t _zero:1;
	uint8_t mbz:1;
	uint8_t avl:3;
	uint64_t base_address:40;
	uint16_t _available:11;
	uint8_t nx:1;
} __attribute__((packed)) pdpe_t;

/* Page Directory Table */
typedef struct pde {
	uint8_t p:1;
	uint8_t rw:1;
	uint8_t us:1;
	uint8_t pwt:1;
	uint8_t pcd:1;
	uint8_t a:1;
	uint8_t d:1;
	uint8_t ps:1;
	uint8_t g:1;
	uint8_t avl:3;
	uint8_t pat:1;
	uint8_t _reserved:8;
	uint64_t base_address:31;
	uint16_t _available:11;
	uint8_t nx:1;
} __attribute__((packed)) pde_t;


/* Bits */
#define PAGE_PRESENT	(1 << 0)
#define PAGE_RW		(1 << 1)
#define PAGE_US		(1 << 2)
#define PAGE_PWT	(1 << 3)
#define PAGE_PCD	(1 << 4)
#define PAGE_A		(1 << 5)
#define PAGE_D		(1 << 6)
#define PAGE_PS		(1 << 7)
#define PAGE_G		(1 << 8)
#define PAGE_NX		(1 << 64)

#define PAGE_MASK       0xFFFFFFFFFFFFF000
#define PAGE_ATTRIBS    0x0000000000000FFF
#define PAGE_PRESENT    0x1
#define PAGE_WRITE      0x2
#define PAGE_USER       0x4
#define PAGE_WRITETHR   0x8
#define PAGE_NOT_CACHE  0x10
#define PAGE_ACCESSED   0x20
#define PAGE_DIRTY      0x40
#define PAGE_2MB        0x80
#define PAGE_CPU_GLOBAL 0x100
#define PAGE_LV4_GLOBAL 0x200



/* Functions */


#endif /* _PAGETABLE_H */
