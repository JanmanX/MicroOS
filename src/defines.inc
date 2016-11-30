%ifndef ASM_DEFINES
%define ASM_DEFINES

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; MEMORY AREAS ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; VGA Video memory
%define VGA_TEXT_BUFFER	0xB8000

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; IDT ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%define IDT_DESC_BIT16                  0x07    ; 16 Bit
%define IDT_DESC_BIT32                  0x0F    ; 32 Bit Trap Gate
%define IDT_DESC_RING1                  0x40    ; Priveligie Level 1
%define IDT_DESC_RING2                  0x20    ; Priveligie Level 2
%define IDT_DESC_RING3                  0x60    ; Priveligie Level 3
%define IDT_DESC_PRESENT                0x80    ; Is it present?


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; PAGING ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%define PAGE_PRESENT    0x01
%define PAGE_WRITE      0x02
%define PAGE_SIZE_2MIB   (1 << 7)

%define PAGE_ENTRY_SIZE 8

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ERROR CODES ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; up to 255
%define ERROR_NO_MULTIBOOT '0'
%define ERROR_NO_CPUID	   '1'
%define ERROR_NO_LONG_MODE '2'
%define ERROR_KERNEL_PANIC '3'
%define ERROR_DEBUG	   '255'

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; MULTIBOOT 2 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; How many bytes from the start of the file we search for the header.
%define MULTIBOOT_SEARCH			32768
%define MULTIBOOT_HEADER_ALIGN			8

; The magic field should contain this.
%define MULTIBOOT2_HEADER_MAGIC			0xe85250d6

; This should be in %eax.
%define MULTIBOOT2_BOOTLOADER_MAGIC		0x36d76289

; Alignment of multiboot modules.
%define MULTIBOOT_MOD_ALIGN			0x00001000

; Alignment of the multiboot info structure.
%define MULTIBOOT_INFO_ALIGN			0x00000008

%define MULTIBOOT_TAG_ALIGN                  8
%define MULTIBOOT_TAG_TYPE_END               0
%define MULTIBOOT_TAG_TYPE_CMDLINE           1
%define MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME  2
%define MULTIBOOT_TAG_TYPE_MODULE            3
%define MULTIBOOT_TAG_TYPE_BASIC_MEMINFO     4
%define MULTIBOOT_TAG_TYPE_BOOTDEV           5
%define MULTIBOOT_TAG_TYPE_MMAP              6
%define MULTIBOOT_TAG_TYPE_VBE               7
%define MULTIBOOT_TAG_TYPE_FRAMEBUFFER       8
%define MULTIBOOT_TAG_TYPE_ELF_SECTIONS      9
%define MULTIBOOT_TAG_TYPE_APM               10
%define MULTIBOOT_TAG_TYPE_EFI32             11
%define MULTIBOOT_TAG_TYPE_EFI64             12
%define MULTIBOOT_TAG_TYPE_SMBIOS            13
%define MULTIBOOT_TAG_TYPE_ACPI_OLD          14
%define MULTIBOOT_TAG_TYPE_ACPI_NEW          15
%define MULTIBOOT_TAG_TYPE_NETWORK           16
%define MULTIBOOT_TAG_TYPE_EFI_MMAP          17
%define MULTIBOOT_TAG_TYPE_EFI_BS            18

%define MULTIBOOT_HEADER_TAG_END  0
%define MULTIBOOT_HEADER_TAG_INFORMATION_REQUEST  1
%define MULTIBOOT_HEADER_TAG_ADDRESS  2
%define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS  3
%define MULTIBOOT_HEADER_TAG_CONSOLE_FLAGS  4
%define MULTIBOOT_HEADER_TAG_FRAMEBUFFER  5
%define MULTIBOOT_HEADER_TAG_MODULE_ALIGN  6
%define MULTIBOOT_HEADER_TAG_EFI_BS        7

%define MULTIBOOT_ARCHITECTURE_I386  0
%define MULTIBOOT_ARCHITECTURE_MIPS32  4
%define MULTIBOOT_HEADER_TAG_OPTIONAL 1

%define MULTIBOOT_CONSOLE_FLAGS_CONSOLE_REQUIRED 1
%define MULTIBOOT_CONSOLE_FLAGS_EGA_TEXT_SUPPORTED 2

%endif
