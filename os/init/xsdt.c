#include <stdint.h>
#include "init/xsdt.h"
#include "lib/klib.h"

static rsdp_desc_t *rsdp;
static xsdt_hdr_t *xsdt;
static acpi_sdt_hdr_t *madt;

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
	/* Get the pointer to System Descriptors */
	if((rsdp = get_rsdp()) == NULL) {
		ERROR("RSDP NOT FOUND!");
	}
	kprintf("RSDP @ 0x%x\n", rsdp);

	/* Get the revision and the pointer accordingly */
	xsdt = rsdp->revision == RSDP_REV_10
		? rsdp->rsdt_address
		: ((rsdp_desc_20_t*)rsdp)->xsdt_address;

	/* do checksum of XSDT */
	if(acpi_checksum(xsdt, xsdt->h.length) == 0) {
		ERROR("XSDT CHECKSUM FAILED\n");
	} else {
		LOG("XSDT CHECKSUM PASSED");
	}

	/* Parse */
	int i = 0;
	int entries = (xsdt->h.length - sizeof(xsdt->h)) / 8;
	kprintf("XSDT ENTRIES: 0x%x\n", entries);
	for(i = 0; i < entries; i++) {
		HALT;
		acpi_sdt_hdr_t *hdr = xsdt->next_sdt[i];

		uint8_t buf[5] = {0};
		memcpy(buf, hdr, 4);
		kprintf("ACPI_SDT_HDR SIGNATURE: %s\n", buf);
		HALT;
	}

	/* return */
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


