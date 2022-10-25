#include <haruhi/memory/kheap.h>
#include <haruhi/console.h>
#include <haruhi/string.h>
#include <haruhi/panic.h>
#include <haruhi/pci.h>
#include <haruhi/ide.h>
#include <asm/pci.h>

struct pci_device *ide_controller = NULL;
struct ide_device ide_devices[IDE_MAX_DEVS] = {0};

static struct pci_device *get_ide_controller(void)
{
	for (size_t i = 0; i < pci_ndevices; ++i) {
		u8 cls = get_pci_class(pci_devices[i]->bus, pci_devices[i]->device, pci_devices[i]->function);
		u8 subcls = get_pci_subclass(pci_devices[i]->bus, pci_devices[i]->device, pci_devices[i]->function);

		if (cls == PCI_CLASS_STORAGE && subcls == PCI_SUBCLASS_IDE) {
			return pci_devices[i];
		}
	}

	return NULL;
}

void ide_init(void)
{
	ide_controller = get_ide_controller();

	if (!ide_controller)
		panic("no IDE controller found");
}
