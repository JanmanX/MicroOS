#ifndef INTERRUPT_H
#define INTERRUPT_H


void exception_gate_00(void);
void exception_gate_01(void);
void exception_gate_02(void);
void exception_gate_03(void);
void exception_gate_04(void);
void exception_gate_05(void);
void exception_gate_06(void);
void exception_gate_07(void);
void exception_gate_08(void);
void exception_gate_09(void);
void exception_gate_10(void);
void exception_gate_11(void);
void exception_gate_12(void);
void exception_gate_13(void);
void exception_gate_14(void);
void exception_gate_15(void);
void exception_gate_16(void);
void exception_gate_17(void);
void exception_gate_18(void);
void exception_gate_19(void);


void disable_interrupts(void);
void enable_interrupts(void);
void interrupt_init();

#endif
