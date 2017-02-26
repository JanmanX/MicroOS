
# Set the module name
MODULE := init

FILES := boot.asm kernel.c multiboot_header.asm

SRC += $(patsubst %, $(MODULE)/%, $(FILES))
