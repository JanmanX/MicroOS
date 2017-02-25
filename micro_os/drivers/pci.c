#include "pci.h"
#include <lib/klib.h>


typedef struct pci_classcode_entry
{
	uint8_t		class ;
	uint8_t		subclass ;
	uint8_t		progif ;
	char *		desc ;
	char *		sub_desc ;
	char *		prog_desc ;
}  pci_classcode_entry_t;

pci_classcode_entry_t pci_class_code_table [] =
{
	{ 0x00, 0x00, 0x00, "Pre-2.0 PCI Specification Device", "Non-VGA","" } ,
	{ 0x00, 0x01, 0x00, "Pre-2.0 PCI Specification Device", "VGA Compatible", "" } ,

	{ 0x01, 0x00, 0x00, "Mass Storage Controller", "SCSI", "" } ,
	{ 0x01, 0x01, 0x00, "Mass Storage Controller", "IDE", "" } ,
	{ 0x01, 0x02, 0x00, "Mass Storage Controller", "Floppy", "" } ,
	{ 0x01, 0x03, 0x00, "Mass Storage Controller", "IPI", "" } ,
	{ 0x01, 0x04, 0x00, "Mass Storage Controller", "RAID", "" } ,
	{ 0x01, 0x80, 0x00, "Mass Storage Controller", "Other", "" } ,

	{ 0x02, 0x00, 0x00, "Network Controller", "Ethernet", "" } ,
	{ 0x02, 0x01, 0x00, "Network Controller", "Token Ring", "" } ,
	{ 0x02, 0x02, 0x00, "Network Controller", "FDDI", "" } ,
	{ 0x02, 0x03, 0x00, "Network Controller", "ATM", "" } ,
	{ 0x02, 0x80, 0x00, "Network Controller", "Other", "" } ,

	{ 0x01, 0x05, 0x20, "Mass Storage Controller", "ATA controller with single DMA", "" } ,
	{ 0x01, 0x05, 0x30, "Mass Storage Controller", "ATA controller with chained DMA", "" } ,

	{ 0x03, 0x00, 0x00, "Display Controller", "PC Compatible", "VGA" } ,
	{ 0x03, 0x00, 0x01, "Display Controller", "PC Compatible", "8514" } ,
	{ 0x03, 0x01, 0x00, "Display Controller", "XGA", "" } ,
	{ 0x03, 0x80, 0x00, "Display Controller", "Other", "" } ,

	{ 0x04, 0x00, 0x00, "Multimedia Device", "Video", "" } ,
	{ 0x04, 0x01, 0x00, "Multimedia Device", "Audio", "" } ,
	{ 0x04, 0x80, 0x00, "Multimedia Device", "Other", "" } ,

	{ 0x05, 0x00, 0x00, "Memory Controller", "RAM", "" } ,
	{ 0x05, 0x01, 0x00, "Memory Controller", "Flash", "" } ,
	{ 0x05, 0x80, 0x00, "Memory Controller", "Other", "" } ,

	{ 0x06, 0x00, 0x00, "Bridge Device", "Host/PCI", "" } ,
	{ 0x06, 0x01, 0x00, "Bridge Device", "PCI/ISA", "" } ,
	{ 0x06, 0x02, 0x00, "Bridge Device", "PCI/EISA", "" } ,
	{ 0x06, 0x03, 0x00, "Bridge Device", "PCI/Micro Channel", "" } ,
	{ 0x06, 0x04, 0x00, "Bridge Device", "PCI/PCI", "" } ,
	{ 0x06, 0x05, 0x00, "Bridge Device", "PCI/PCMCIA", "" } ,
	{ 0x06, 0x06, 0x00, "Bridge Device", "PCI/NuBus", "" } ,
	{ 0x06, 0x07, 0x00, "Bridge Device", "PCI/CardBus", "" } ,
	{ 0x06, 0x80, 0x00, "Bridge Device", "Other", "" } ,

	{ 0x07, 0x00, 0x00, "Simple Communications Controller", "Serial", "Generic XT Compatible" } ,
	{ 0x07, 0x00, 0x01, "Simple Communications Controller", "Serial", "16450 Compatible" } ,
	{ 0x07, 0x00, 0x02, "Simple Communications Controller", "Serial", "16550 Compatible" } ,
	{ 0x07, 0x01, 0x00, "Simple Communications Controller", "Parallel", "Standard" } ,
	{ 0x07, 0x01, 0x00, "Simple Communications Controller", "Parallel", "Bidirectional" } ,
	{ 0x07, 0x01, 0x01, "Simple Communications Controller", "Parallel", "ECP 1.X Compliant" } ,
	{ 0x07, 0x80, 0x02, "Simple Communications Controller", "Other", "" } ,

	{ 0x08, 0x00, 0x00, "Base Systems Peripheral", "PIC (Programmable Interrupt Controller)", "Generic 8259" } ,
	{ 0x08, 0x00, 0x01, "Base Systems Peripheral", "PIC (Programmable Interrupt Controller)", "ISA" } ,
	{ 0x08, 0x00, 0x02, "Base Systems Peripheral", "PIC (Programmable Interrupt Controller)", "PCI" } ,
	{ 0x08, 0x01, 0x00, "Base Systems Peripheral", "DMA (Direct Memory Access)", "Generic 8259" } ,
	{ 0x08, 0x01, 0x01, "Base Systems Peripheral", "DMA (Direct Memory Access)", "ISA" } ,
	{ 0x08, 0x01, 0x02, "Base Systems Peripheral", "DMA (Direct Memory Access)", "EISA" } ,
	{ 0x08, 0x02, 0x00, "Base Systems Peripheral", "System Timer", "Generic 8259" } ,
	{ 0x08, 0x02, 0x01, "Base Systems Peripheral", "System Timer", "ISA" } ,
	{ 0x08, 0x02, 0x02, "Base Systems Peripheral", "System Timer", "EISA" } ,
	{ 0x08, 0x03, 0x00, "Base Systems Peripheral", "RTC (Real Time Clock)", "Generic" } ,
	{ 0x08, 0x03, 0x01, "Base Systems Peripheral", "RTC (Real Time Clock)", "ISA" } ,
	{ 0x08, 0x80, 0x00, "Base Systems Peripheral", "Other", "" } ,

	{ 0x09, 0x00, 0x00, "Input Device", "Keyboard", "" } ,
	{ 0x09, 0x01, 0x00, "Input Device", "Digitizer (Pen)", "" } ,
	{ 0x09, 0x02, 0x00, "Input Device", "Mouse", "" } ,
	{ 0x09, 0x80, 0x00, "Input Device", "Other", "" } ,

	{ 0x0A, 0x00, 0x00, "Docking Station", "Generic", "" } ,
	{ 0x0A, 0x80, 0x00, "Docking Station", "Other", "" } ,

	{ 0x0B, 0x00, 0x00, "Processor", "i386", "" } ,
	{ 0x0B, 0x01, 0x00, "Processor", "i486", "" } ,
	{ 0x0B, 0x02, 0x00, "Processor", "Pentium", "" } ,
	{ 0x0B, 0x10, 0x00, "Processor", "Alpha", "" } ,
	{ 0x0B, 0x20, 0x00, "Processor", "Power PC", "" } ,
	{ 0x0B, 0x80, 0x00, "Processor", "Co-processor", "" } ,

	{ 0x0C, 0x00, 0x00, "Serial Bus Controller", "Firewire (IEEE 1394)", "" } ,
	{ 0x0C, 0x01, 0x00, "Serial Bus Controller", "ACCESS.bus", "" } ,
	{ 0x0C, 0x02, 0x00, "Serial Bus Controller", "SSA (Serial Storage Archetecture)", "" } ,
	{ 0x0C, 0x03, 0x00, "Serial Bus Controller", "USB (Universal Serial Bus)", "" } ,
	{ 0x0C, 0x04, 0x00, "Serial Bus Controller", "Fibre Channel", "" } ,

	{ 0xFF, 0x00, 0x00, "Unknown", "Device Does Not Fit In Class Codes", "UDF" } ,
} ;

// Use this value for loop control during searching:
#define	PCI_CLASS_CODE_TABLE_LEN (sizeof(pci_class_code_table)/sizeof(pci_classcode_entry_t))

char *pci_get_class_string(uint8_t class)
{
	uint32_t i = 0;
	for(i = 0; i < PCI_CLASS_CODE_TABLE_LEN; i++) {
		if(pci_class_code_table[i].class == class) {
			return pci_class_code_table[i].desc;
		}
	}

	return "unknown";

}

char *pci_get_subclass_string(uint8_t class, uint8_t subclass)
{
	uint32_t i = 0;
	for(i = 0; i < PCI_CLASS_CODE_TABLE_LEN; i++) {
		if(pci_class_code_table[i].class == class
		   && pci_class_code_table[i].subclass == subclass) {
			return pci_class_code_table[i].sub_desc;
		}
	}

	return "unknown";
}
void pci_init()
{
	uint8_t slot = 0;
	uint8_t bus = 0;
	const uint8_t func = 0;
	uint8_t class = 0;
	uint8_t subclass = 0;

	for(bus = 0; bus < PCI_BUS_MAX; bus++) {
		for(slot = 0;  slot < PCI_SLOT_MAX; slot++) {
			uint16_t classes = pci_read_config(bus,
							   slot,
							   func,
							   PCI_REGISTER_SUBCLASS);

			/* Check vendorID is device exists. */
			if(pci_read_config(bus, slot, 0x00, 0x00) == 0xffff ) {
				continue;
			}


			kprintf("PCI device found: %s, %s\n",
				pci_get_class_string((uint8_t)classes >> 8),
				pci_get_subclass_string((uint8_t)classes >> 8,
							(uint8_t)classes & 0xFF));
			/* TODO: Something smart about detecting and initializing
			 * devices here */
			switch((uint8_t)classes >> 8) {
			case PCI_CLASS_MASS_STORAGE_CONTROLLER: {
				/* TODO: INIT IDE DRIVER HERE */
				kprintf("PCI Mass Storage Controller found on\
					bus: 0x%x, slot: 0x%x\n", bus, slot);
				break;
			}
			}
		}
	}

}

uint32_t pci_read_config(uint8_t bus,
			 uint8_t slot,
			 uint8_t func,
			 uint8_t offset)
{
	uint32_t _b = ((uint32_t)(bus)) << 16;
	uint32_t _s = ((uint32_t)(slot)) << 11;
	uint32_t _f = ((uint32_t)(func)) << 8;

	uint32_t payload = _b
		| _s
		| _f
		| (offset & 0xFC)
		| ((uint32_t)0x80000000);

	/* Write to the address */
	outd(PCI_CONFIG_ADDRESS, payload);

	/* Read the data */
	uint32_t ret = (uint32_t)((ind(PCI_CONFIG_DATA) >> ((offset & 2) * 8))
				  & 0xffff);
	return ret;
}



