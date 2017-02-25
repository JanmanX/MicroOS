
# Set the module name
MODULE := init

FILES := boot.asm kernel.c

SRC += $(patsubst %, $(MODULE)/%, $(FILES))
