
# Set the module name
MODULE := lib

FILES := _asm.asm  circ_buf.c  klib_asm.asm  klib.c cpuid.c

SRC += $(patsubst %, $(MODULE)/%, $(FILES))
