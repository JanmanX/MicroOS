#ifndef _XSDT_H
#define _XSDT_H

#include <stdint.h>

#define RSDP_SIGNATURE		"RSD PTR "
#define RSDP_SIGNATURE_LEN	8
/* Pointer to the XSDT */
#define RSDP_REV_10 0
#define RSDP_REV_20 2

/* RSDP Version 1.0 */
typedef struct rsdp_desc_10 {
	uint8_t signature[8];
	uint8_t checksum;
	uint8_t oemid[6];
	uint8_t revision;
	uint32_t rsdt_address;
}__attribute__((packed)) rsdp_desc_10_t;
typedef rsdp_desc_10_t rsdp_desc_t;
#define RSDP_DESC_10_LEN (sizeof(rsdp_desc_10_t))

typedef struct rsdp_desc_20 {
	/* First part */
	rsdp_desc_10_t rsdp_10;

	/* 2.0, extension */
	uint32_t length;
	uint64_t xsdt_address;
	uint8_t ext_checksum;
	uint8_t reserved[3];
} __attribute__ ((packed)) rsdp_desc_20_t;
#define RSDP_DESC_20_LEN (sizeof(rsdp_desc_20_t))



/* The RSDT is the main System Description Table */
typedef struct xsdt_hdr {
	char signature[4];
	uint32_t length;
	uint8_t revision;
	uint8_t checksum;
	char oemid[6];
	char oemtableid[8];
	uint32_t oemrevision;
	uint32_t creatorid;
	uint32_t creatorrevision;
} __attribute__((packed)) xsdt_hdr_t;
#define XSDT_HDR_LEN sizeof(xsdt_hdr_t)


void xsdt_init();

rsdp_desc_t *get_rsdp();
uint8_t acpi_checksum(const uint8_t *data, uint64_t len);
uint8_t rsdp_checksum(rsdp_desc_t *rsdp);
uint8_t xsdt_checksum(xsdt_hdr_t*);
//void *xsdt_find_sdt(char *signature);
#endif /* _XSDT_H */
