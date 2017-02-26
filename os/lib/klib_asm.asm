[bits 64]

global kpanic

section .text

kpanic:
	mov al, 4

	; Prints "ERR: <error_code>" and halts
 	mov dword [0xB8000+0x0], 0x4f524f45
 	mov dword [0xB8000+0x4], 0x4f3a4f52
	mov dword [0xB8000+0x8], 0x4f204f20
	mov byte  [0xB8000+0xa], al

	hlt

