[BITS 64]

%include "init/defines.inc"

section .multiboot_header
header_start:
	multiboot_magic 	dd MULTIBOOT2_HEADER_MAGIC
	multiboot_arch		dd MULTIBOOT_ARCHITECTURE_I386
	multiboot_header_len	dd header_end - header_start
	multiboot_header_chksm	dd 0x100000000 - (MULTIBOOT2_HEADER_MAGIC \
						+ MULTIBOOT_ARCHITECTURE_I386 \
						+ (header_end - header_start))

	; other tags here

	; End tag
	dw 0x00	; type
	dw 0x00 ; flags
	dd 0x08	; size

header_end:
