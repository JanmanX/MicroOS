[bits 64]

global kpanic

%include "src/defines.inc"

section .text

kpanic:
	mov al, ERROR_KERNEL_PANIC

	; Prints "ERR: <error_code>" and halts
 	mov dword [VGA_TEXT_BUFFER+0x0], 0x4f524f45
 	mov dword [VGA_TEXT_BUFFER+0x4], 0x4f3a4f52
	mov dword [VGA_TEXT_BUFFER+0x8], 0x4f204f20
	mov byte  [VGA_TEXT_BUFFER+0xa], al

	hlt


