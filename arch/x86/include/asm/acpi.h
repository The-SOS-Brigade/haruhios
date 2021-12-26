#ifndef _ASM_X86_ACPI_H
#define _ASM_X86_ACPI_H

#include <haruhi/types.h>

struct acpi_rsdp_desc {
	char	signature[8];
	u8	checksum;
	char	oem_id[6];
	u8	revision;
	u32	rsdt_addr;
} __attribute__((packed));

struct acpi_table_header {
	char	signature[4];
	u32	length;
	u8	revision;
	u8	checksum;
	char	oem_id[6];
	char	oem_table_id[8];
	u32	oem_revision;
	u32	creator_id;
	u32	creator_revision;
} __attribute__((packed));

struct acpi_rsdt_desc {
	struct acpi_table_header hdr;
	u32 table_ptr;
} __attribute__((packed));

struct acpi_generic_addr {
	u8 addr_space;
	u8 bit_width;
	u8 bit_offset;
	u8 access_size;
	u64 addr;
} __attribute__((packed));

struct acpi_fadt_desc {
	struct acpi_table_header hdr;
	u32 firmware_ctrl;
	u32 dsdt_ptr;
	/* ACPI 1.0 */
	u8 reserved0;
	u8 ppmp;
	u16 sci_int;
	u32 smi_cmd_port;
	u8 acpi_enable;
	u8 acpi_disable;
	u8 s4bios_req;
	u8 pstate_ctrl;
	u32 pm1a_event_blk;
	u32 pm1b_event_blk;
	u32 pm1a_ctrl_blk;
	u32 pm1b_ctrl_blk;
	u32 pm2_ctrl_blk;
	u32 pm_timer_blk;
	u32 gpe0_blk;
	u32 gpe1_blk;
	u8 pm1_event_length;
	u8 pm1_ctrl_length;
	u8 pm2_ctrl_length;
	u8 pm_timer_length;
	u8 gpe0_length;
	u8 gpe1_length;
	u8 gpe1_base;
	u8 c_state_ctrl;
	u16 worst_c2_lat;
	u16 worst_c3_lat;
	u16 flush_size;
	u16 flush_stride;
	u8 duty_offset;
	u8 duty_width;
	u8 day_alarm;
	u8 month_alarm;
	u8 century;
	u16 iapc_boot_arch;
	u8 reserved1;
	u32 flags;
	struct acpi_generic_addr reset_reg;
	u8 reset_value;
	u8 reserved2[3];
	/* ACPI 2.0+ */
	u64 ext_firmware_ctrl;
	u64 ext_dsdt;
	struct acpi_generic_addr ext_pm1a_event_blk;
	struct acpi_generic_addr ext_pm1b_event_blk;
	struct acpi_generic_addr ext_pm1a_ctrl_blk;
	struct acpi_generic_addr ext_pm1b_ctrl_blk;
	struct acpi_generic_addr ext_pm2_ctrl_blk;
	struct acpi_generic_addr ext_pm_timer_blk;
	struct acpi_generic_addr ext_gpe0_blk;
	struct acpi_generic_addr ext_gpe1_blk;
} __attribute__((packed));

#define ACPI_RSDP_SIGNATURE "RSD PTR "
#define ACPI_MADT_SIGNATURE "APIC"
#define ACPI_BERT_SIGNATURE "BERT"
#define ACPI_CPEP_SIGNATURE "CPEP"
#define ACPI_DSDT_SIGNATURE "DSDT"
#define ACPI_ECDT_SIGNATURE "ECDT"
#define ACPI_EINJ_SIGNATURE "EINJ"
#define ACPI_ERST_SIGNATURE "ERST"
#define ACPI_FADT_SIGNATURE "FACP"
#define ACPI_FACS_SIGNATURE "FACS"
#define ACPI_HEST_SIGNATURE "HEST"
#define ACPI_MSCT_SIGNATURE "MSCT"
#define ACPI_MPST_SIGNATURE "MPST"
#define ACPI_PMTT_SIGNATURE "PMTT"
#define ACPI_PSDT_SIGNATURE "PSDT"
#define ACPI_RASF_SIGNATURE "RASF"
#define ACPI_RSDT_SIGNATURE "RSDT"
#define ACPI_SBST_SIGNATURE "SBST"
#define ACPI_SLIT_SIGNATURE "SLIT"
#define ACPI_SRAT_SIGNATURE "SRAT"
#define ACPI_SSDT_SIGNATURE "SSDT"
#define ACPI_XSDT_SIGNATURE "XSDT"

extern struct acpi_rsdp_desc *_rsdp;
extern struct acpi_fadt_desc *_fadt;
extern struct acpi_rsdt_desc *_rsdt;

static inline struct acpi_fadt_desc *get_fadt(void)
{
	return _fadt;
}

#endif

