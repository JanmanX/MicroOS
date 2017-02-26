
# Set the module name
MODULE := init

FILES := boot.asm  rsdp.asm  kernel.c  multiboot_header.asm  xsdt.c

SRC += $(patsubst %, $(MODULE)/%, $(FILES))
