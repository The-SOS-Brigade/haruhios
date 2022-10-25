#ifndef _HARIHI_IDE_H
#define _HARUHI_IDE_H

#include <haruhi/types.h>

#define IDE_MAX_DEVS 4

struct ide_device {
	int reserved;
};

void ide_init(void);

extern struct pci_device *ide_controller;
extern struct ide_device ide_devices[IDE_MAX_DEVS];

#endif
