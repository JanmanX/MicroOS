#include <stdint.h>
#include "pagetable.h"
#include <lib/klib.h>
#include "vm.h"
#include <lib/cpuid.h>

void mm_dump_pdpe(pdpe_t *p)
{
	uint64_t *t = (uint64_t*)p;
	kprintf("RAW: 0x%x\n", *t);

	kprintf("p: 0x%x \n", p->p);
	kprintf("rw: 0x%x\n", p->rw);
	kprintf("us: 0x%x\n", p->us);
	kprintf("pwt: 0x%x\n", p->pwt);
	kprintf("pcd: 0x%x\n", p->pcd);
	kprintf("a: 0x%x\n", p->a);
	kprintf("d: 0x%x \n", p->d);
	kprintf("ps: 0x%x\n", p->ps);
	kprintf("g: 0x%x\n", p->g);
	kprintf("avl: 0x%x\n", p->avl);
	kprintf("pat: 0x%x\n", p->pat);
	kprintf("base_address: 0x%x\n", p->base_address);
	kprintf("_available: 0x%x\n", p->_available);
	kprintf("nx: 0x%x\n", p->nx);

}

static void reload_page_table(uint64_t pml4t_start_phys)
{
	asm volatile("mov %0, %%rax;\
		     mov %%rax, %%cr3;"
		     :
		     : "r"(pml4t_start_phys)
		     : "%rax"
		    );
}

uint8_t mm_map(uint64_t phys, uint64_t virt)
{
	if(MM_GET_PML4_INDEX(phys) > PML4E_NUM) {
		kprintf("Cannot map pages at 0x%x\n", phys);
		return 1;
	}
}


void init_page_tables_identity(void)
{
	uint64_t i = 0;
	uint64_t addr = 0x00;
	uint64_t entry = 0;

	/* Zero out tables */
	memset(pml4t, 0x00, PML4E_NUM * sizeof(uint64_t));
	memset(pdpt, 0x00, PDPE_NUM * sizeof(uint64_t));
	memset(pdt, 0x00, PDE_NUM * sizeof(uint64_t));


	/* Setup PML4T */
	for(i = 0; i < PML4E_NUM; i++) {
		pml4t[i] = (uint64_t)(&pdpt[i * 0x200])
			| PAGE_PRESENT
			| PAGE_RW;
	}

	/* Setup PDPT */
	for(i = 0; i < PDPE_NUM; i++) {
		pdpt[i] = (i * GiB)
			| PAGE_PS
			| PAGE_PRESENT
			| PAGE_RW;

	}

	/* Reload */
	reload_page_table((uint64_t)pml4t);

	LOG("Page tables inited\n");
}
