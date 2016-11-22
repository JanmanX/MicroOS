[BITS 32]

%include "src/defines.inc"

%define MULTIBOOT_MAGIC 	0xE85250D6
%define MULTIBOOT_ARCH 		0x00	; 32-bit i386, '4' is MIPS

section .multiboot_header
header_start:
	multiboot_magic 	dd MULTIBOOT2_HEADER_MAGIC
	multiboot_arch		dd MULTIBOOT_ARCHITECTURE_I386
	multiboot_header_len	dd header_end - header_start
	multiboot_header_chksm	dd 0x100000000 - (MULTIBOOT_MAGIC + MULTIBOOT_ARCH + (header_end - header_start))

	; other tags here

	; End tag
	dw 0x00	; type
	dw 0x00 ; flags
	dd 0x08	; size

header_end:
