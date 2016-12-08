[bits 64]

extern interrupt_handle
global disable_interrupts
global enable_interrupts

; Push and pop in the order as defined in struct pt_regs (interrupt.h)
%macro PUSHAQ 0
	push rdi
	push rsi
	push rdx
	push rcx
	push rax
	push r8
	push r9
	push r10
	push r11
	push rbx
	push rbp
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro POPAQ 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbp
	pop rbx
	pop r11
	pop r10
	pop r9
	pop r8
	pop rax
	pop rcx
	pop rdx
	pop rsi
	pop rdi
%endmacro


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

	hlt
	POPAQ		; Restore registers
	sti		; Reenable interrupts
	iretq		; return from interrupt


%macro interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	mov rdi, %1
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
