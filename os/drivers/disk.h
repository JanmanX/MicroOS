#ifndef DISKS_H
#define DISKS_H

#include <stdint.h>

#define DISKS_MAX	0x20

void disk_init(uint8_t bus, uint8_t slot);
uint32_t disk_count();

#endif /* DISKS_H */
