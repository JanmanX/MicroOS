#ifndef _PAGETABLE_H
#define _PAGETABLE_H

#include <stdint.h>

/* Page-Map Level 4 Table */
typedef struct pml4t {
	uint8_t nx:1;
	uint16_t _available:11;
	uint64_t base_address:40;
	uint8_t avl:3;
	uint8_t mbz:2;
	uint8_t ign:1;
	uint8_t a:1;
	uint8_t pcd:1;
	uint8_t pwt:1;
	uint8_t us:1;
	uint8_t rw:1;
	uint8_t p:1
} __attribute__((packed)) pml4t_t;


/* Page Directory Pointer Table */
typedef struct pdpt {
	uint8_t nx:1
	uint16_t _available:11;
	uint64_t base_address:40;
	uint8_t avl:3;
	uint8_t mbz:1;
	uint8_t _zero:1;
	uint8_t ign:1;
	uint8_t a:1;
	uint8_t pcd:1;
	uint8_t pwt:1;
	uint8_t us:1;
	uint8_t rw:1;
	uint8_t p:1
} __attribute__((packed)) pdpt_t;

/* Page Directory Table */
typedef struct pdt {
	uint8_t nx:1;
	uint16_t _available:11;
	uint64_t base_address:31;
	uint8_t _reserved:8;
	uint8_t pat:1;
	uint8_t avl:3;
	uint8_t g:1;
	uint8_t _one:1;
	uint8_t d:1;
	uint8_t a:1;
	uint8_t pcd:1;
	uint8_t pwt:1;
	uint8_t us:1;
	uint8_t rw:1;
	uint8_t p:1
} __attribute__((packed)) pdt_t;


#endif /* _PAGETABLE_H */
