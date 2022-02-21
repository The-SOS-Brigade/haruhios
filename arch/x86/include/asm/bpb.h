#ifndef _ASM_X86_BPB_H
#define _ASM_X86_BPB_H

#define BPB_OEMID		0x7C03
#define BPB_BPS			0x7C0B
#define BPB_SPC			0x7C0D
#define BPB_RESERVED		0x7C0E
#define BPB_FAT_COUNT		0x7C10
#define BPB_ROOTDIR_ENTRIES	0x7C11
#define BPB_MEDIA_DESC		0x7C15
#define BPB_SPT			0x7C18
#define BPB_HPC			0x7C1A
#define BPB_HIDDEN		0x7C1C
#define BPB_TOTAL_SECTORS	0x7C20
#define EBPB_SPF		0x7C24
#define EBPB_FLAGS		0x7C28
#define EBPB_ROOT_CLUSTER	0x7C2C
#define EBPB_FSINFO_SECTOR	0x7C30
#define EBPB_BACKUP_SECTOR	0x7C32
#define EBPB_RESERVED0		0x7C34
#define EBPB_RESERVED1		0x7C38
#define EBPB_RESERVED2		0x7C3B
#define EBPB_DRIVE_NUMBER	0x7C40
#define EBPB_NT_FLAGS		0x7C41
#define EBPB_SIGNATURE		0x7C42
#define EBPB_VOLUME_ID		0x7C43
#define EBPB_SYSTEMID_STRING	0x7C52

#endif
