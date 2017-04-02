#include <stdint.h>
#include "pagetable.h"
#include <lib/klib.h>
#include "vm.h"


static void reload_page_table(uint64_t pml4t_start_phys)
{
	asm volatile("mov %0, %%rax;\
		     mov %%rax, %%cr3;"
		     :
		     : "r"(pml4t_start_phys)
		     : "%rax"
		    );
}

void init_page_tables_identity(void)
{
	uint64_t i = 0;
	uint64_t addr = 0x00;
	uint64_t entry = 0;

	/* Zero out tables */
	memset(pml4t, 0x00, PML4T_NUM * sizeof(pml4e_t));
	memset(pdpt, 0x00, PDPT_NUM * sizeof(pdpe_t));
	memset(pdt, 0x00, PDT_NUM * sizeof(pde_t));

	/* Setup PML4T */
	for(i = 0; i < PML4T_NUM; i++) {
		pml4t[i]= ((uint64_t)pdpt) | PAGE_PRESENT | PAGE_WRITE;
	}

	/* Setup PDPT */
	for(i = 0; i < PDPT_NUM; i++) {
		pdpt_ptr[i] = ((uint64_t)(&pdt[i * 512]))  | PAGE_PRESENT | PAGE_WRITE;
	}

	/* Setup PDT */
	for(i = 0; i < PDT_NUM; i++) {
		pdt_ptr[i] = (uint64_t)(MiB2 * i) | PAGE_PRESENT | PAGE_WRITE |
			PAGE_2MB;
 	}


	/* Reload */
	reload_page_table((uint64_t)pml4t);
}
