[BITS 64]

%ifndef _ASM_ASM
%define _ASM_ASM


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

%endif ; _ASM_ASM
