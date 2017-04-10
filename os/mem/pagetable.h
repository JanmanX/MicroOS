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
	uint8_t mbz:1;
	uint8_t ign2:1;
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
	uint8_t d:1;
	uint8_t ps:1;
	uint8_t g:1;
	uint8_t avl:3;
	uint8_t pat:1;
	uint64_t reserved:17;
	uint64_t base_address:22;
	uint16_t _available:11;
	uint8_t nx:1;
} __attribute__((packed)) pdpe_t;

/* Bits */
#define PAGE_PRESENT	(1UL << 0)
#define PAGE_RW		(1UL << 1)
#define PAGE_US		(1UL << 2)
#define PAGE_PWT	(1UL << 3)
#define PAGE_PCD	(1UL << 4)
#define PAGE_A		(1UL << 5)
#define PAGE_D		(1UL << 6)
#define PAGE_PS		(1UL << 7)
#define PAGE_G		(1UL << 8)
#define PAGE_NX		(1UL << 63)

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


#define MM_GET_PML4_INDEX(x) (((x) >> 39) & 0x1FF)
#define MM_GET_PDP_INDEX(x)  (((x) >> 30) & 0x1FF)


/* Functions */


#endif /* _PAGETABLE_H */
