[bits 64]

extern interrupt_handle
global disable_interrupts
global enable_interrupts

%macro PUSHAQ 0
	push r15
	push r14
	push r13
	push r12
	push r11
	push r10
	push r9
	push r8
	push rdi
	push rsi
	push rbp
	push rsp
	push rbx
	push rdx
	push rcx
	push rax
%endmacro

%macro POPAQ 0
	pop rax
	pop rcx
	pop rdx
	pop rbx
	pop rsp
	pop rbp
	pop rsi
	pop rdi
	pop r8
	pop r9
	pop r10
	pop r11
	pop r12
	pop r13
	pop r14
	pop r15
%endmacro

disable_interrupts:
	cli
	ret

enable_interrupts:
	sti
	ret

exception_gate_main:
	cli		; Disable interrupts
	PUSHAQ		; Save registers
	cld 		; C code following the sysV ABI requires DF to be clear on function entry
	call interrupt_handle

	POPAQ		; Restore registers
	sti		; Reenable interrupts
	iretq		; return from interrupt


%macro exception_gate 1
global exception_gate_%1
exception_gate_%1:
	mov rdi, %1
	jmp exception_gate_main
%endmacro


exception_gate 0
exception_gate 1
exception_gate 2
exception_gate 3
exception_gate 4
exception_gate 5
exception_gate 6
exception_gate 7
exception_gate 8
exception_gate 9
exception_gate 10
exception_gate 11
exception_gate 12
exception_gate 13
exception_gate 14
exception_gate 15
exception_gate 16
exception_gate 17
exception_gate 18
exception_gate 19
exception_gate 20
