global start

%include "defines.inc"


section .text
[BITS 32]

%macro BOCHS_BREAK 0
	xchg bx, bx
%endmacro

%define NUM_PML4E	1
%define NUM_PDPE	64
%define NUM_PDE		512 * NUM_PDPE


; On i386 machine, when loaded by multiboot-compliant bootloader, the state of
; the registers are:
; EAX -> Magic value
; EBX -> Contains the 32bit physical address of the multiboot information struct
;  --
; A20 gate -> enabled
; GDTR -> GDTR may be invalid
; IDTR -> not setup
start:
	; Setup stack
	mov esp, stack_top

	; Save multiboot info pointer
	push ebx

	; Check that the CPU is up for x86_64
	call check_multiboot
	call check_cpuid
	call check_long_mode

	call setup_page_tables
	call enable_paging

	lgdt [gdt64.pointer]

	; Retrieve multiboot info pointer
	pop edi
	jmp gdt64.km_code:long_mode_start

	; This code should not be reached
	hlt


; check_multiboot()
;
; Checks if kernel was loaded by multiboot compliant bootloader. Jumps to error
; if multiboot is not detected.
; IN: EAX with initial value after boot
check_multiboot:
	cmp eax, MULTIBOOT2_BOOTLOADER_MAGIC
	jne .no_multiboot
	ret
.no_multiboot:
	mov al, ERROR_NO_MULTIBOOT
	jmp error


; check_cpuid()
;
; Checks if CPUID is supported.
; Jumps to error if CPUID is not supported
check_cpuid:
	; Store EFLAGS twice
	pushfd
	pushfd

	; Flip the ID bit (bit 21)
	xor dword [esp], 1 << 21

	; Set EFLAGS and retrieve it again
	popfd
	pushfd

	; Compare the popped EFLAGS with the previous EFLAGS
	pop eax
	xor eax,[esp]

	; Restore the old EFLAGS
	popfd

	; Check if ID bit is flipped
	; If eax == 0, ID bit cannot be changed
	and eax, 1 << 21
	jz .no_cpuid

	ret

.no_cpuid:
	mov eax, ERROR_NO_CPUID
	jmp error



; check_long_mode()
;
; Checks if long-mode is available. Jumps to error if not
check_long_mode:
	; To test for long mode, we will use extended functions of CPUID.
	; Before we do this, we have to make sure extended functions are
	; actually available.

	; EAX=80000000h: Get Highest Extended Function Supported
	mov eax, 0x80000000
	cpuid

	; Compare with highest extended function supported.
	; If below, there is no long mode
	cmp eax, 0x80000001
	jb .no_long_mode


	; Detect long mode using CPUID
	; EAX=80000001h: Extended Processor Info and Feature Bits
	mov eax, 0x80000001
	cpuid
	test edx, 1 << 29 ; bit 29 = long mode bit
	jz .no_long_mode

	ret

.no_long_mode:
	mov eax, ERROR_NO_LONG_MODE
	jmp error



; set_up_page_tables()
;
; Identity maps the first 1GiB of memory into 2MiB page-tables
setup_page_tables:
	; Create an entry in PML4T
	mov eax, PDPT
	or eax, PAGE_PRESENT | PAGE_WRITE
	mov [PML4T], eax

	; Create an entry in PDPT
	mov eax, PDT
	or eax, PAGE_PRESENT | PAGE_WRITE
	mov [PDPT], eax

	; Create 512 entries in PDT
	xor ecx, ecx	; ecx = counter
.setup_pdt:
	mov eax, 0x200000	; 2MiB
	mul ecx
	or eax, PAGE_PRESENT | PAGE_WRITE | PAGE_SIZE_2MIB
	mov [PDT + PAGE_ENTRY_SIZE * ecx], eax	; store it

	inc ecx
	cmp ecx, 512
	jne .setup_pdt

	ret


; enable_paging()
;
; Enables paging. Page tables must be setup
enable_paging:
	; Load the address of PML4T into CR3 (used for page lookup)
	mov eax, PML4T
	mov cr3, eax

	; Enable PAE-flag (Physical Address Extension (64 bit))
	; http://wiki.osdev.org/CPU_Registers_x86#CR4
	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax

	; Setup longmode in the EFER MSR (Model Specific Register)
	; http://wiki.osdev.org/CPU_Registers_x86-64#EFER
	mov ecx, 0xC0000080
	rdmsr	; reads model specific register into edx:eax
	or eax, 1 << 8 ; bit 8 -> Long mode enable
	wrmsr

	; Enable paging
	; http://wiki.osdev.org/CPU_Registers_x86#CR0
	mov eax, cr0
	or eax, 1 << 31 ; paging bit
	mov cr0, eax

	ret


; error()
;
; Prints an error code to the screen and halts
; IN: 	al: error code
; OUT:	-
error:
	; Prints "ERR: <error_code>" and halts
 	mov dword [VGA_TEXT_BUFFER+0x0], 0x4f524f45
 	mov dword [VGA_TEXT_BUFFER+0x4], 0x4f3a4f52
	mov dword [VGA_TEXT_BUFFER+0x8], 0x4f204f20
	mov byte  [VGA_TEXT_BUFFER+0xa], al
	hlt


;--------------------------------- 64 bit -------------------------------------
[BITS 64]
extern main
section .text

; long_mode_start(*mb_info_ptr);
;
;
long_mode_start:
	; Clear long-mode registers
	; Setup data segments
        mov ax, gdt64.km_data
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax

        xor r8, r8
        xor r9, r9
        xor r10, r10
        xor r11, r11
        xor r12, r12
        xor r13, r13
        xor r14, r14
        xor r15, r15
        cld

	; Expand paging to 64GiB
	call extend_page_tables

	; mb_info_ptr is already in rdi
	mov rsi, PML4T
	call main
	hlt

; extend_page_tables()
;
; Extends the mapping to 64GiB
extend_page_tables:

	; Extend the PDP Table
	xor rcx, rcx
	inc rcx		; One page is already loaded, thus inc by 1
	mov rax, PDT
.extend_pdpt:
	add rax, 512 * PAGE_ENTRY_SIZE
	lea rax, [PDT + PAGE_ENTRY_SIZE * rcx]
	or rax, PAGE_PRESENT | PAGE_WRITE
	mov [PDPT + rcx * PAGE_ENTRY_SIZE], rax

	inc rcx
	cmp rcx, NUM_PDPE
	jne .extend_pdpt


	; Extend the PD Table
	xor rcx, rcx	; ecx = counter
.extend_pdt:
	mov rax, 0x200000	; 2MiB
	mul rcx
	or rax, PAGE_PRESENT | PAGE_WRITE | PAGE_SIZE_2MIB
	mov [PDT + PAGE_ENTRY_SIZE * rcx], rax	; store it

	inc rcx
	cmp rcx, NUM_PDE
	jne .extend_pdt


	; Flush TLB
	mov rax, cr3
	mov cr3, rax

	; return
	ret
;------------------------------------------------------------------------------
section .bss
align 4096	; ensures the tables are page-aligned

stack_bottom:
	resb 4096
stack_top:

%include "vars.asm"
