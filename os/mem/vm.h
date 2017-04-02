#ifndef _VM_H
#define _VM_H

#include "pagetable.h"

/* Map 64 GiB of RAM
 *
 * PD Tables	= 64 GiB / 2MiB = 32768
 * PDP Tables	= 32768 / 512	= 64
 * PML4 Tables  = 64 / 512	= 1
 */
#define PML4T_NUM	0x0001
uint64_t pml4t[PML4T_NUM] __attribute__((aligned(4096)));
uint64_t *pml4t_ptr = (uint64_t*)pml4t;

#define PDPT_NUM	0x0040
uint64_t pdpt[PDPT_NUM] __attribute__((aligned(4096)));
uint64_t *pdpt_ptr = (uint64_t*)pdpt;


#define PDT_NUM		0x8000
uint64_t pdt[PDT_NUM]__attribute__((aligned(4096)));
uint64_t *pdt_ptr = (uint64_t*)pdt;



#define MiB2		0x200000 // 2^21 bytes = 2097152 = 2MiB


void init_page_tables_identity(void);

#endif /* _VM_H */
