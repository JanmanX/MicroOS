; RSDP
; Root System Description Pointer
;
; This assembly is used to find the RSDP.
;
;
; Layout of RSDP:
;                   struct RSDPDescriptor20 {
;                         RSDPDescriptor firstPart;
;
;                         uint32_t Length;
;                         uint64_t XsdtAddress;
;                         uint8_t ExtendedChecksum;
;                         uint8_t reserved[3];
;                   } __attribute__ ((packed));
;
[BITS 64]

%define SIGNATURE "RSD PTR "

section .text

global get_rsdp

; int64_t* get_rsdp()
; 	IN:
; 	OUT: pointer to RSD, or 0 as error.
get_rsdp:
; Search range 0x000E0000 - 0x000FFFFF first
	pushf
	cld
	mov rax, SIGNATURE
	mov rdi, 0x000E0000
	mov rcx, 0x000FFFFF

.loop:
	cmp rax, [rdi]
	je .return_rsdp		; Match found

	add rdi, 0x10		; Move 16 bytes. RSDP is always on 16 byte boundary
	cmp rdi, rcx
	jb .loop		; loop if within search memory


.search_edba:
	mov rdi, 0x000A0000
	mov rcx, 0x00000400

.loop2:
	cmp rax, [rdi]
	je .return_rsdp		; Match found

	add rdi, 0x10		; Move 16 bytes. RSDP is always on 16 byte boundary
	cmp rdi, rcx
	jb .loop2		; loop if within search memory

	; Nothing found
	popf
	xor rax, rax
	ret

.return_rsdp:
	popf
	xchg rax, rdi		; Put address into RAX (return register)
	ret

