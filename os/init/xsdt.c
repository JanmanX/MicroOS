#include <stdint.h>
#include "init/xsdt.h"
#include "lib/klib.h"

static rsdp_desc_t *rsdp;
static xsdt_hdr_t *xsdt;

rsdp_desc_t *get_rsdp(void)
{
	/* Search a lot of memory... */
	uint16_t *off;

	/* OK, now find RSDP */
	for (off = (uint16_t*)0xf0000; off < 0x100000; off += 0x01) {
		/* Skip if not equal */
		if (memcmp(off, RSDP_SIGNATURE, RSDP_SIGNATURE_LEN)) {
			continue;
		}

		/* Get structure length from revision */
		uint64_t len = ((rsdp_desc_10_t*)off)->revision == RSDP_REV_10 ?
			RSDP_DESC_10_LEN : RSDP_DESC_20_LEN;

		/* return if matching checksum */
		if(acpi_checksum(off, len)) {
			return (rsdp_desc_t*)off;
		}

	}

	/* Nothing found */
	return NULL;
}



void xsdt_init(void)
{
	clear_screen();

	if((rsdp = get_rsdp()) == NULL) {
		ERROR("RSDP NOT FOUND!");
	}
	kprintf("RSDP @ 0x%x\n", rsdp);

	xsdt = rsdp->revision == RSDP_REV_10
		? rsdp->rsdt_address
		: ((rsdp_desc_20_t*)rsdp)->xsdt_address;

	/* Print debug info */
	kprintf("XSDT @ 0x%x\n", (uint64_t)xsdt);
	char str[9] = {0};
	memcpy(str, &xsdt->signature, 4);
	kprintf("XSDT->SIGNATURE: %s\n", str);
	kprintf("XSDT_CHECKSUM: 0x%x\n", acpi_checksum(xsdt, XSDT_HDR_LEN));

	/* STOP */
	if(xsdt_checksum(xsdt) == 0) {
		ERROR("XSDT checksum failed!\n");
	}
	LOG("ASD");
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

	return sum == 0;
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


