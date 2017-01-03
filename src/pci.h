#ifndef PCI_H
#define PCI_H

#include <stdint.h>


#define PCI_CONFIG_ADDRESS	0xCF8
#define PCI_CONFIG_DATA		0xCFC

void pci_init();

uint32_t pci_read_config(uint8_t bus,
			 uint8_t slot,
			 uint8_t func,
			 uint8_t offset);


extern char *pci_vendor_string[];
#endif /* PCI_H */
