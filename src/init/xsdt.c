#include <stdint.h>
#include "init/xsdt.h"
#include "lib/klib.h"

extern rsdp_desc_t *get_rsdp();
static rsdp_desc_t *rsdp;

void xsdt_init()
{
	rsdp = get_rdsp();
	if(rsdp == NULL) {
		ERROR("Could not locate RDSP.");
	}


	kprintf("RSDP at 0x%x", (uint64_t)rsdp);
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
/*    XSDT *xsdt = (XSDT *) RootSDT;
    int entries = (xsdt->h.Length - sizeof(xsdt->h)) / 8;

    for (int i = 0; i < entries; i++)
    {
        ACPISDTHeader *h = (ACPISDTHeader *) xsdt->PointerToOtherSDT[i];
        if (!strncmp(h->Signature, "FACP", 4))
            return (void *) h;
    }
*/
    // No FACP found
    return NULL;
}
