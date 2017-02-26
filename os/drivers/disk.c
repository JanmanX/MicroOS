#include <stdint.h>

#include "disk.h"
#include <drivers/pci.h>
#include <lib/klib.h>

/* For the lack of better system of maintaining devices, 'disks' will be used to
 * keep track of available disks in the disk_table. */
pci_dev_t disk_table[DISKS_MAX] = {0};
uint32_t disks = 0;

void disk_init(uint8_t bus, uint8_t slot)
{
	if(disks >= DISKS_MAX) {
		DEBUG("Cannot initialize any more disks.");
		return;
	}

	/* Add disk entry */
	disk_table[disks].bus = bus;
	disk_table[disks].slot = slot;
	disks++;

	return;
}


uint32_t disk_count()
{
	return disks;
}
