#ifndef _HARUHI_PCI_H
#define _HARUHI_PCI_H

#include <haruhi/types.h>

extern void pci_init(void);

u8 get_pci_class(u8 bus, u8 device, u8 function);
u8 get_pci_subclass(u8 bus, u8 device, u8 function);
u8 get_pci_header_type(u8 bus, u8 device, u8 function);
u8 get_pci_progif(u8 bus, u8 device, u8 function);
u8 get_bridge_secondary_bus(u8 bus, u8 device, u8 function);
void pci_map(void (*fp)(u8, u8, u8));
void pci_map_print_handler(u8 bus, u8 device, u8 function);
void pci_enumerate_bus(u8 bus);
extern u32 pci_read32_config(u8 bus, u8 device, u8 function, u8 offset);

static inline void enumerate_pci(void)
{
	pci_enumerate_bus(0);
}

struct pci_device {
	u8 bus;
	u8 device;
	u8 function;
	u16 vendor_id;
};

extern struct pci_device **pci_devices;
extern size_t pci_ndevices;

/* devices */

#define PCI_SUBCLASS_OTHER	0x80

#define PCI_NOCLASS		0x0
# define PCI_NOCLASS_NONVGACOMPAT	0x0
# define PCI_NOCLASS_VGACOMPAT		0x1

#define PCI_CLASS_STORAGE	0x1
# define PCI_SUBCLASS_SCSI		0x0
# define PCI_SUBCLASS_IDE		0x1
# define PCI_SUBCLASS_FLOPPY		0x2
# define PCI_SUBCLASS_IPI		0x3
# define PCI_SUBCLASS_RAID		0x4
# define PCI_SUBCLASS_ATA		0x5
# define PCI_SUBCLASS_SATA		0x6
# define PCI_SUBCLASS_SAS		0x7
# define PCI_SUBCLASS_NVM		0x8

#define PCI_CLASS_NETWORK	0x2
# define PCI_SUBCLASS_ETH		0x0
# define PCI_SUBCLASS_TOKENRING		0x1
# define PCI_SUBCLASS_FDDI		0x2
# define PCI_SUBCLASS_ATM		0x3
# define PCI_SUBCLASS_ISDN		0x4
# define PCI_SUBCLASS_WORDFIP		0x5
# define PCI_SUBCLASS_PICMG		0x6
# define PCI_SUBCLASS_NETIB		0x7
# define PCI_SUBCLASS_NETFABRIC		0x8

#define PCI_CLASS_DISPLAY	0x3
# define PCI_SUBCLASS_VGACOMPAT		0x0
# define PCI_SUBCLASS_XGA		0x1
# define PCI_SUBCLASS_3DC		0x2

#define PCI_CLASS_MEDIA		0x4
# define PCI_SUBCLASS_MVIDEO		0x0
# define PCI_SUBCLASS_MAUDIO		0x1
# define PCI_SUBCLASS_TELE		0x2
# define PCI_SUBCLASS_AUDIO		0x3

#define PCI_CLASS_MEMORY	0x5
# define PCI_SUBCLASS_RAM		0x0
# define PCI_SUBCLASS_FLASH		0x1

#define PCI_CLASS_BRIDGE	0x6
# define PCI_SUBCLASS_HOST_BRIDGE	0x0
# define PCI_SUBCLASS_ISA_BRIDGE	0x1
# define PCI_SUBCLASS_EISA_BRIDGE	0x2
# define PCI_SUBCLASS_MCA_BRIDGE	0x3
# define PCI_SUBCLASS_PCI_BRIDGE	0x4
# define PCI_SUBCLASS_PCMCIA_BRIDGE	0x5
# define PCI_SUBCLASS_NUBUS_BRIDGE	0x6
# define PCI_SUBCLASS_CARDBUS_BRIDGE	0x7
# define PCI_SUBCLASS_RACEWAY_BRIDGE	0x8
# define PCI_SUBCLASS_PCI_BRIDGE2	0x9
# define PCI_SUBCLASS_IB_BRIDGE		0xA

#define PCI_CLASS_COMM		0x7
# define PCI_SUBCLASS_SERIAL		0x0
# define PCI_SUBCLASS_PARALLEL		0x1
# define PCI_SUBCLASS_MPSERIAL		0x2
# define PCI_SUBCLASS_MODEM		0x3
# define PCI_SUBCLASS_GPIB		0x4
# define PCI_SUBCLASS_SCARD		0x5

#define PCI_CLASS_BASE		0x8
# define PCI_SUBCLASS_PIC		0x0
# define PCI_SUBCLASS_DMA		0x1
# define PCI_SUBCLASS_TIMER		0x2
# define PCI_SUBCLASS_RTC		0x3
# define PCI_SUBCLASS_HOTPLUG		0x4
# define PCI_SUBCLASS_SDHOST		0x5
# define PCI_SUBCLASS_IOMMU		0x6

#define PCI_CLASS_INPUT		0x9
# define PCI_SUBCLASS_KEYBOARD		0x0
# define PCI_SUBCLASS_DPEN		0x1
# define PCI_SUBCLASS_MOUSE		0x2
# define PCI_SUBCLASS_SCANNER		0x3
# define PCI_SUBCLASS_GAMEPORT		0x4

#define PCI_CLASS_DOCK		0xA
# define PCI_SUBCLASS_DOCKGENERIC	0x0

#define PCI_CLASS_PU		0xB
# define PCI_SUBCLASS_I386		0x0
# define PCI_SUBCLASS_I486		0x1
# define PCI_SUBCLASS_PENTIUM		0x2
# define PCI_SUBCLASS_PENTIUMPRO	0x3
# define PCI_SUBCLASS_ALPHA		0x10
# define PCI_SUBCLASS_PPC		0x20
# define PCI_SUBCLASS_MIPS		0x30
# define PCI_SUBCLASS_COPU		0x40

#define PCI_CLASS_SERIAL	0xC
# define PCI_SUBCLASS_FIREWIRE		0x0
# define PCI_SUBCLASS_ACCESS		0x1
# define PCI_SUBCLASS_SSA		0x2
# define PCI_SUBCLASS_USB		0x3
# define PCI_SUBCLASS_FIBRE		0x4
# define PCI_SUBCLASS_SMBUS		0x5
# define PCI_SUBCLASS_IB		0x6
# define PCI_SUBCLASS_IPMI		0x7
# define PCI_SUBCLASS_SERCOS		0x8
# define PCI_SUBCLASS_CANBUS		0x9

#define PCI_CLASS_WIRELESS	0xD
# define PCI_SUBCLASS_IRDA		0x0
# define PCI_SUBCLASS_IRCONSUMER	0x1
# define PCI_SUBCLASS_RF		0x10
# define PCI_SUBCLASS_BLUETOOTH		0x11
# define PCI_SUBCLASS_BROADBAND		0x12
# define PCI_SUBCLASS_ETHERNET_A	0x20
# define PCI_SUBCLASS_ETHERNET_B	0x21

#define PCI_CLASS_INT		0xE
# define PCI_SUBCLASS_I20		0x0

#define PCI_CLASS_SATCOM	0xF
# define PCI_SUBCLASS_SATTV		0x1
# define PCI_SUBCLASS_SATAUDIO		0x2
# define PCI_SUBCLASS_SATVOICE		0x3
# define PCI_SUBCLASS_SATDATA		0x4

#define PCI_CLASS_CRYPTO	0x10
# define PCI_SUBCLASS_NETCOM_CRYPTO	0x0
# define PCI_SUBCLASS_ENTERT_CRYPTO	0x10

#define PCI_CLASS_SIGNAL	0x11
# define PCI_SUBCLASS_DPIO		0x0
# define PCI_SUBCLASS_PERFCOUNT		0x1
# define PCI_SUBCLASS_COMMSYNC		0x10
# define PCI_SUBCLASS_SIGPROC		0x20

#define PCI_CLASS_ACC		0x12
#define PCI_CLASS_NONESS	0x13
#define PCI_CLASS_COPU		0x40
#define PCI_CLASS_UNASSIG	0xFF

#define PCI_DEVS_PER_BUS	0x20

#endif

