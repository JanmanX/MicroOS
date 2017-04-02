
# Set the module name
MODULE := mem

FILES := vm.c

SRC += $(patsubst %, $(MODULE)/%, $(FILES))
