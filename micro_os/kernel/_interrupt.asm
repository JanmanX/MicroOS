[bits 64]

%include "lib/_asm.asm"

extern interrupt_handle
global disable_interrupts
global enable_interrupts

global interrupt_dummy_handler

_debug_str db 'DUMMY INTR', 0x0A, 0x00
extern kprintf
extern pic_eoi
interrupt_dummy_handler:
	cli
	mov rdi, _debug_str
	call kprintf
	sti
	iretq

disable_interrupts:
	cli
	ret

enable_interrupts:
	sti
	ret

interrupt_handler_main:
	cli		; Disable interrupts

	PUSHAQ		; Save registers

	cld 		; C code following the sysV ABI requires DF to be clear on function entry

	mov rdi, rsp 	; Arguments are on stack

	call interrupt_handle
	xchg bx, bx


	POPAQ		; Restore registers
	add rsp, 0x8	; pop the orig_ax

	sti		; Reenable interrupts

	iretq		; return from interrupt


%macro interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	push qword %1
	jmp interrupt_handler_main
%endmacro


interrupt_handler 0
interrupt_handler 1
interrupt_handler 2
interrupt_handler 3
interrupt_handler 4
interrupt_handler 5
interrupt_handler 6
interrupt_handler 7
interrupt_handler 8
interrupt_handler 9
interrupt_handler 10
interrupt_handler 11
interrupt_handler 12
interrupt_handler 13
interrupt_handler 14
interrupt_handler 15
interrupt_handler 16
interrupt_handler 17
interrupt_handler 18
interrupt_handler 19
interrupt_handler 20
