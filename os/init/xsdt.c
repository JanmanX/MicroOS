#include <stdint.h>
#include "init/xsdt.h"
#include "lib/klib.h"

static rsdp_desc_t *rsdp;


long int get_rsdp();
void xsdt_init()
{
	rsdp = (rsdp_desc_t *)get_rsdp();
	kprintf("RSDP at: 0x%x", (uint64_t)rsdp);



	return 0;
}



uint8_t xsdt_checksum(acpi_xsdt_hdr_t *hdr)
{
	uint8_t sum = 0;
	uint32_t i;
	for(i = 0; i < hdr->length; i++) {
		sum += ((uint8_t*)hdr)[i];
	}

	return sum == 0;
}

void *xsdt_find_sdt(char* signature)
{
   return NULL;
}


