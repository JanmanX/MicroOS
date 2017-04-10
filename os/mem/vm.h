#ifndef _VM_H
#define _VM_H

#include "pagetable.h"

#define PML4T_NUM	0x0001
uint64_t pml4t[PML4T_NUM] __attribute__((aligned(4096)));

#define PDPT_NUM	0x0000
uint64_t pdpt[PDPT_NUM] __attribute__((aligned(4096)));

#define PDE_NUM		0x0200
uint64_t pdt[PDE_NUM] __attribute__((aligned(4096)));


#define KiB                (1024UL)
#define MiB                (1024UL*1024UL)
#define GiB                (1024UL*1024UL*1024UL)

void init_page_tables_identity(void);

uint8_t mm_map(uint64_t phys, uint64_t virt);

#endif /* _VM_H */
