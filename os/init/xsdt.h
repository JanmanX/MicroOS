#ifndef _XSDT_H
#define _XSDT_H

#include <stdint.h>


/* Pointer to the XSDT */
typedef struct rsdp_desc {
	char signature[8];
	uint8_t checksum;
	char oemid[6];
	uint8_t revision;
	uint32_t rsdt_address;

	/* 2.0, extension */
	uint32_t length;
	uint64_t xsdt_address;
	uint8_t ext_checksum;
	uint8_t reserved[3];
} __attribute__ ((packed)) rsdp_desc_t;



/* The RSDT is the main System Description Table */
typedef struct acpi_xsdt_hdr {
	char signature[4];
	uint32_t length;
	uint8_t revision;
	uint8_t checksum;
	char oemid[6];
	char oemtableid[8];
	uint32_t oemrevision;
	uint32_t creatorid;
	uint32_t creatorrevision;
} __attribute__((packed)) acpi_xsdt_hdr_t;


void xsdt_init();

//uint8_t xsdt_checksum(acpi_xsdt_hdr_t*);
//void *xsdt_find_sdt(char *signature);
#endif /* _XSDT_H */
