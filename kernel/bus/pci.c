#include <haruhi/memory/kheap.h>
#include <haruhi/console.h>
#include <haruhi/pci.h>

struct pci_device **pci_devices = NULL;
size_t pci_ndevices = 0;

void pci_map_print_handler(u8 bus, u8 device, u8 function)
{
	u8 c = get_pci_class(bus, device, function);
	char *class_str;

	switch (c) {

	case PCI_NOCLASS:
		class_str = "unclassified";
		break;
	case PCI_CLASS_STORAGE:
		class_str = "mass storage";
		break;
	case PCI_CLASS_NETWORK:
		class_str = "network";
		break;
	case PCI_CLASS_DISPLAY:
		class_str = "display";
		break;
	case PCI_CLASS_MEDIA:
		class_str = "multimedia";
		break;
	case PCI_CLASS_MEMORY:
		class_str = "memory";
		break;
	case PCI_CLASS_BRIDGE:
		class_str = "bridge";
		break;
	case PCI_CLASS_COMM:
		class_str = "simple communication";
		break;
	case PCI_CLASS_BASE:
		class_str = "base system peripheral";
		break;
	case PCI_CLASS_INPUT:
		class_str = "input device";
		break;
	case PCI_CLASS_DOCK:
		class_str = "docking station";
		break;
	case PCI_CLASS_PU:
		class_str = "processor";
		break;
	case PCI_CLASS_SERIAL:
		class_str = "serial bus";
		break;
	case PCI_CLASS_WIRELESS:
		class_str = "wireless";
		break;
	case PCI_CLASS_INT:
		class_str = "intelligent";
		break;
	case PCI_CLASS_SATCOM:
		class_str = "satellite communication";
		break;
	case PCI_CLASS_CRYPTO:
		class_str = "crypto";
		break;
	case PCI_CLASS_SIGNAL:
		class_str = "signal processing";
		break;
	case PCI_CLASS_ACC:
		class_str = "processing accelerator";
		break;
	case PCI_CLASS_NONESS:
		class_str = "non-essential";
		break;
	case PCI_CLASS_COPU:
		class_str = "coprocessor";
		break;
	case PCI_CLASS_UNASSIG:
		class_str = "type unassigned";
		break;
	default:
		class_str = "unknown";
		break;
	}

	printk("PCI: bus %d, device %d, function %d | %s device found\n", bus, device, function, class_str);
}

void pci_map(void (*fp)(u8, u8, u8))
{
	for (size_t i = 0; i < pci_ndevices; ++i) {
		fp(pci_devices[i]->bus, pci_devices[i]->device, pci_devices[i]->function);
	}
}

u16 get_pci_vendor_id(u8 bus, u8 device, u8 function)
{
	return pci_read32_config(bus, device, function, 0);
}

u8 get_pci_class(u8 bus, u8 device, u8 function)
{
	return pci_read32_config(bus, device, function, 0x8) >> 0x18;
}

u8 get_pci_subclass(u8 bus, u8 device, u8 function)
{
	return pci_read32_config(bus, device, function, 0x8) >> 0x10;
}

u8 get_pci_header_type(u8 bus, u8 device, u8 function)
{
	return (pci_read32_config(bus, device, function, 0xC) >> 0x10) & 0xFF;
}

u8 get_pci_progif(u8 bus, u8 device, u8 function)
{
	return (pci_read32_config(bus, device, function, 0x8) >> 0x8) & 0xFF;
}

u8 get_bridge_secondary_bus(u8 bus, u8 device, u8 function)
{
	return (pci_read32_config(bus, device, function, 0x18) >> 0x8) & 0xFF;
}


static void add_device(u8 bus, u8 device, u8 function, u16 vendor_id)
{
	struct pci_device *dev = kmalloc(sizeof(struct pci_device));
	dev->bus = bus;
	dev->device = device;
	dev->function = function;
	dev->vendor_id = vendor_id;
	pci_devices[pci_ndevices++] = dev;
}

static bool device_is_bridge(u8 bus, u8 device, u8 function)
{

	u8 class = get_pci_class(bus, device, function);
	u8 subclass = get_pci_subclass(bus, device, function);

	if (class != 6 || subclass != 4)
		return false;

	return true;

}

void pci_enumerate_bus(u8 bus)
{
	for (size_t dev = 0; dev < PCI_DEVS_PER_BUS; ++dev) {
		char max_functions = 1;
		u32 r = pci_read32_config(bus, dev, 0, 0);
		if (r == 0xffffffff) return;

		if (get_pci_header_type(bus, dev, 0) & 0x80)
			max_functions = 8;

		for (size_t f = 0; f < max_functions; ++f) {
			r = pci_read32_config(bus, dev, f, 0);
			if (r == 0xffffffff) continue;

			u16 vendor = get_pci_vendor_id(bus, dev, f);
			add_device(bus, dev, f, vendor);

			if (device_is_bridge(bus, dev, f)) {
				u8 newbus;
				newbus = get_bridge_secondary_bus(bus, dev, f);
				pci_enumerate_bus(newbus);
			}
		}
	}
}

