[bits 64]

global disable_interrupts
global enable_interrupts

global exception_gate_00
global exception_gate_01
global exception_gate_02
global exception_gate_03
global exception_gate_04
global exception_gate_05
global exception_gate_06
global exception_gate_07
global exception_gate_08
global exception_gate_09
global exception_gate_10
global exception_gate_11
global exception_gate_12
global exception_gate_13
global exception_gate_14
global exception_gate_15
global exception_gate_16
global exception_gate_17
global exception_gate_18
global exception_gate_19


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

	mov dword [0xB8000], 0x4f524f45
	hlt
	POPAQ		; Restore registers
	sti		; Reenable interrupts
	iretq		; return from interrupt


exception_gate_00:
        mov al, 0x00
        jmp exception_gate_main

exception_gate_01:
        mov al, 0x01
        jmp exception_gate_main

exception_gate_02:
        mov al, 0x02
        jmp exception_gate_main

exception_gate_03:
        mov al, 0x03
        jmp exception_gate_main

exception_gate_04:
        mov al, 0x04
        jmp exception_gate_main

exception_gate_05:
        mov al, 0x05
        jmp exception_gate_main

exception_gate_06:
        mov al, 0x06
        jmp exception_gate_main

exception_gate_07:
        mov al, 0x07
        jmp exception_gate_main

exception_gate_08:
        mov al, 0x08
        jmp exception_gate_main

exception_gate_09:
        mov al, 0x09
        jmp exception_gate_main

exception_gate_10:
        mov al, 0x0A
        jmp exception_gate_main

exception_gate_11:
        mov al, 0x0B
        jmp exception_gate_main

exception_gate_12:
        mov al, 0x0C
        jmp exception_gate_main

exception_gate_13:
        mov al, 0x0D
        jmp exception_gate_main

exception_gate_14:
        mov al, 0x0E
        jmp exception_gate_main

exception_gate_15:
        mov al, 0x0F
        jmp exception_gate_main

exception_gate_16:
        mov al, 0x10
        jmp exception_gate_main

exception_gate_17:
        mov al, 0x11
        jmp exception_gate_main

exception_gate_18:
        mov al, 0x12
        jmp exception_gate_main

exception_gate_19:
        mov al, 0x13
        jmp exception_gate_main

