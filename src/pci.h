#ifndef PCI_H
#define PCI_H

#include <stdint.h>

#define PCI_BUS_MAX		0xFF
#define PCI_SLOT_MAX		0x1F

#define PCI_CONFIG_ADDRESS	0xCF8
#define PCI_CONFIG_DATA		0xCFC

/* PCI Device Structure field offsets */
#define PCI_REGISTER_VENDOR_ID		0x00
#define PCI_REGISTER_DEVICE_ID		0x02
#define PCI_REGISTER_COMMAND		0x04
#define PCI_REGISTER_STATUS		0x06
#define PCI_REGISTER_SUBCLASS		0x0A
#define PCI_REGISTER_CLASS		0x0B
#define PCI_REGISTER_BAR0		0x10
#define PCI_REGISTER_BAR1		0x14
#define PCI_REGISTER_BAR2		0x18
#define PCI_REGISTER_BAR3		0x1C
#define PCI_REGISTER_BAR4		0x20
#define PCI_REGISTER_BAR5		0x24
/* ... more here ... */
#define PCI_REGISTER_INTERRUPT_LINE	0x3C
#define PCI_REGISTER_INTERRUPT_PIN	0x3D


/* PCI Class definitions */
#define PCI_CLASS_MASS_STORAGE_CONTROLLER	0x01
#define PCI_SUBCLASS_MASS_STORAGE_IDE		0x01

/* Descriptor for PCI devices */
typedef struct pci_dev {
	uint8_t bus;
	uint8_t slot;
} pci_dev_t;


void pci_init();

uint32_t pci_read_config(uint8_t bus,
			 uint8_t slot,
			 uint8_t func,
			 uint8_t offset);


// extern char *pci_vendor_string[];
#endif /* PCI_H */
