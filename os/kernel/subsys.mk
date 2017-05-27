
# Set the module name
MODULE := kernel

FILES := pic.c  idt.c  interrupt.c  _interrupt.asm  apic.c

SRC += $(patsubst %, $(MODULE)/%, $(FILES))
