#include <haruhi/memory/kheap.h>
#include <haruhi/pci.h>
#include <asm/io.h>

#define PCI_CFG_ADDR	0xCF8
#define PCI_CFG_DATA	0xCFC

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

