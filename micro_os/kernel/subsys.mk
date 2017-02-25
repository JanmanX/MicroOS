
# Set the module name
MODULE := kernel

FILES := pic.c  idt.c  interrupt.c  _interrupt.asm

SRC += $(patsubst %, $(MODULE)/%, $(FILES))
