#include <stdint.h>
#include "init/xsdt.h"
#include "lib/klib.h"

static rsdp_desc_t *rsdp;
static xsdt_hdr_t *xsdt;


void dump_rsdp(rsdp_desc_t *r)
{
	char buf[9] = {0};
	memcpy(buf, &(r->signature), 8);
	kprintf("RSDP--SIG: %s ", buf);
	kprintf("CHKSM: 0x%x ", r->oemid);
	memcpy(buf, &(r->oemid), 6);
	kprintf("OEMID: %s ", buf);
	kprintf("REV: 0x%x RSDT_ADDR: 0x%x ", r->revision, r->rsdt_address);
}

rsdp_desc_t *get_rsdp()
{
	uint32_t off;

	uint64_t* search;

	/* Search in first KiB of EDBA
	 * then  0x000E0000 to 0x000FFFFF
	 */

	/* Search a lot of memory */
	for (search = (uint64_t*)0xA0000;
	     (uint64_t)search < 0x100000;
	     search += 0x10) {

		/* Check if signature matches */
		if (memcmp(search, "RSD PTR ", sizeof(uint64_t)) == 0) {
			kprintf("Signature found at: 0x%x, rev: %d\n",
				(uint64_t)search,
				((rsdp_desc_t*)search)->revision);

			rsdp_desc_t *r = (rsdp_desc_t*)search;
			dump_rsdp(r);

			if(r->revision != RSDP_REV_10 || r->revision !=
			   RSDP_REV_20) {
				continue;
			}

			DEBUG("RIGHT SIGNATURE");
			HALT;

			uint64_t len = r->revision == RSDP_REV_10 ?
				RSDP_DESC_10_LEN : RSDP_DESC_20_LEN;

			if(acpi_checksum((uint8_t*)r, len) == 0) {
				return r;
			}
		}
	}

	return NULL;
}



void xsdt_init()
{
	rsdp_desc_t *r2 = get_rsdp();
	HALT;

	rsdp = (rsdp_desc_t *)get_rsdp();
	kprintf("RSDP at: 0x%x\n", (uint64_t)rsdp);

	HALT;
	kprintf("XSDT at: 0x%x\n", (uint64_t)xsdt);


	kprintf("XSDT:\n");
	clear_screen();
	char str[9] = {0};

	memcpy(str, &xsdt->oemid, 6);
	kprintf("XSDT->OEMID: %s\n", str);
	memcpy(str, &xsdt->oemtableid, 8);
	kprintf("XSDT->OEMTABLEID: %s\n", str);




	kprintf("First 4 bytes of XSDT: 0x%x\n", ((uint32_t*)xsdt)[0]);


	kprintf("XSDT_CHECKSUM: 0x%x\n", xsdt_checksum(xsdt));


	if(xsdt_checksum(xsdt) != 0) {
		ERROR("XSDT checksum failed!\n");
	}

	HALT;
	kprintf("XSDP at: 0x%x", (uint64_t)xsdt);
	return 0;
}


uint8_t acpi_checksum(const uint8_t *data, uint64_t len)
{
	int i;
	uint8_t sum = 0;

	for (i = 0; i < len; i++) {
		sum += data[i];
	}

	return sum;
}

uint8_t xsdt_checksum(xsdt_hdr_t *hdr)
{
	uint64_t sum = 0;
	uint64_t i;
	for(i = 0; i < hdr->length; i++) {
		sum += ((uint8_t*)hdr)[i];
	}

	return sum == 0;
}

void *xsdt_find_sdt(char* signature)
{
	return NULL;
}


