#ifndef _APIC_H
#define _APIC_H

#define IA32_APIC_BASE_MSR 0x1B
#define IA32_APIC_BASE_MSR_BSP 0x100 // Processor is a BSP
#define IA32_APIC_BASE_MSR_ENABLE 0x800


typedef struct multiple_apic_descriptor_table {
/*
   00 	4 	Signature 'APIC'
   04 	4 	Length
   08 	1 	Revision
   09 	1 	Checksum
   0a 	6 	OEMID
   10 	8 	OEM Table ID
   18 	4 	OEM Revision
   1c 	4 	Creator ID
   20 	4 	Creator Revision
   */
	uint32_t	apic;
	uint32_t	length;
	uint8_t		revision;
	uint8_t		checksum;
	uint64_t	oem_id:48;
	uint64_t	oem_table_id;
	uint32_t	oem_revision;
	uint32_t	creator_id;
	uint32_t	creator_revision;
}__attribute__((packed)) madt_t;




#endif /* _APIC_H */
