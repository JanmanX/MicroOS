#include <stdint.h>
#include "pagetable.h"
#include <lib/klib.h>
#include "vm.h"


static void reload_page_table(uint64_t pml4t_start_phys)
{
	BOCHS_DEBUG;
	asm volatile("mov %0, %%rax;\
		     mov %%rax, %%cr3;"
		     :
		     : "r"(pml4t_start_phys)
		     : "%rax"
		    );
	DEBUG("3");


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


	DEBUG("1");

	/* Setup PML4T */
	for(i = 0; i < PML4T_NUM; i++) {
		pml4t[i]= ((uint64_t)pdpt) | PAGE_PRESENT | PAGE_WRITE;
#if 0
		pml4t[i].p = 1;
		pml4t[i].rw = 1;
		pml4t[i].base_address = (uint64_t)&(pdpt[i]);
#endif

	}

	/* Setup PDPT */
	for(i = 0; i < PDPT_NUM; i++) {
		pdpt_ptr[i] = (uint64_t)(pdt) | PAGE_PRESENT | PAGE_WRITE;

#if 0
		pdpt[i].p = 1;
		pdpt[i].rw = 1;
		pdpt[i].base_address = (uint64_t)&(pdt[i]);
#endif
	}

	/* Setup PDT */
	for(i = 0; i < PDT_NUM; i++) {
		pdt_ptr[i] = (uint64_t)(MiB2 * i) | PAGE_PRESENT | PAGE_WRITE |
			PAGE_2MB;
#if 0
		pdt[i].p = 1;
		pdt[i].rw = 1;
		pdt[i].ps = 1;
		pdt[i].base_address = (uint64_t)MiB2 * i;
#endif
	}

	kprintf("PML4T_PTR: 0x%x\n", (uint64_t)pml4t_ptr);

	kprintf("PML4T[0]: 0x%x\nPDPT[0]: 0x%x\nPDT[0]: 0x%x\n",
		*(uint64_t*)pml4t, *(uint64_t*)pdpt, *(uint64_t*)pdt);


	DEBUG("2");

	/* Reload */
	reload_page_table((uint64_t)pml4t);
}
