section .bss
align 4096
%include "init/defines.inc"

; Page tables for 64GiB
; Each entry is 8 bytes, with 512 slots in each table
; 512 * 8 bytes = 4096 bytes for each table
PML4T:		resb 4096	  		; 1 	PML4E
PDPT:		resb 4096			; 64 	PDPE
PDT:		resb (PAGE_ENTRY_SIZE*64*512)	; 32768 PDE
; 1*64*512 * 2MiB = 64 gibibytes


section .ro_data
; Global Descriptor Table used for long mode
;
; LAYOUT:
; Limit			2 bytes
; Base 0:15		2 bytes
; Base 16:23		1 byte
; Access		1 byte
; Limit 16:19		4 bits
; Flags			4 bits
; Base 24:31		1 byte
;
; User Mode access byte
; +-------+-------+
; |  0xF  |  0xA  |
; +---------------+
; |1|1|1|1|1|0|1|0|
; ++-+-+-+-+-+-+-++
;  | | | | | | | |
;  | | | | | | | +-----> Accessed bit. Set it to zero.
;  | | | | | | +-------> Readable / Writeable bit. Readable bit for Code, Writeable for data sectors
;  | | | | | +---------> Direction Bit.
;  | | | | +-----------> Executable bit. 1 for Code, 0 for data
;  | | | +-------------> Must be 1.
;  | +-+---------------> Privilege, 2 bits. Containing ring level.
;  |
;  +-------------------> Preset bit. Must be 1 for all valid selectors.
gdt64:                               ; Global Descriptor Table (64-bit).
	.null: equ $ - gdt64         ; The null descriptor.
	dw 0                         ; Limit (low).
	dw 0                         ; Base (low).
	db 0                         ; Base (middle)
	db 0                         ; Access.
	db 0                         ; Granularity.
	db 0                         ; Base (high).

; KERNEL
	.km_code: equ $ - gdt64      ; The kernel mode code descriptor.
	dw 0                         ; Limit (low).
	dw 0                         ; Base (low).
	db 0                         ; Base (middle)
	db 10011010b                 ; Access (exec/read).
	db 00100000b                 ; Granularity.
	db 0                         ; Base (high).
	.km_data: equ $ - gdt64         ; The data descriptor.
	dw 0                         ; Limit (low).
	dw 0                         ; Base (low).
	db 0                         ; Base (middle)
	db 10010010b                 ; Access (read/write).
	db 00000000b                 ; Granularity.
	db 0                         ; Base (high).

; USER
	.um_code: equ $ - gdt64
	dw 0
	dw 0
	db 0
	db 0xFA
	db 0xCF
	db 0
	.um_data: equ $ - gdt64
	dw 0
	dw 0
	db 0
	db 0xF2
	db 0xCF
	db 0

	.pointer:                    ; The GDT-pointer.
	dw $ - gdt64 - 1             ; Limit (length of GDT).
	dq gdt64                     ; Address of GDT64

