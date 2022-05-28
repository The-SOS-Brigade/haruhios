#include <haruhi/memory/kheap.h>
#include <haruhi/pci.h>
#include <asm/io.h>

#define PCI_CFG_ADDR	0xCF8
#define PCI_CFG_DATA	0xCFC

struct pci_device **pci_devices = NULL;
size_t pci_ndevices = 0;

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

static void enumerate_bus(u8 bus)
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
				enumerate_bus(newbus);
			}
		}
	}
}

static inline void enumerate_pci(void)
{
	enumerate_bus(0);
}

void pci_init(void)
{
	pci_devices = kmalloc(PCI_DEVS_PER_BUS * sizeof(void *));
	enumerate_pci();
}

u32 pci_read32_config(u8 bus, u8 device, u8 function, u8 offset)
{
	u32 address = (0x80000000)
		    | (bus << 16)
		    | (device << 11)
		    | ((function & 0b111) << 8)
		    | (offset & ~0b11);

	outl(PCI_CFG_ADDR, address);
	return inl(PCI_CFG_DATA);
}

