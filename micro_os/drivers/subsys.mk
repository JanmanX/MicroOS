
# Set the module name
MODULE := drivers

FILES := disk.c  pci.c  keyboard.c  _keyboard.asm

SRC += $(patsubst %, $(MODULE)/%, $(FILES))
