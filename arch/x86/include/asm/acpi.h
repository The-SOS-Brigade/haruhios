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

#endif

