[BITS 64]
%include "lib/_asm.asm"

section .text

msg: db 'KEYBOARD INT HANDLED', 0x0A, 0x00

global _keyboard_interrupt_handler
extern keyboard_interrupt_handler
extern kprintf
extern pic_eoi

_keyboard_interrupt_handler:
	cli		; Disable interrupts

	PUSHAQ		; Save registers

	cld 		; C code following the sysV ABI requires DF to be clear on function entry

	call keyboard_interrupt_handler

	POPAQ		; Restore registers

	sti		; Reenable interrupts

	xchg bx, bx

	iretq		; return from interrupt
