
# Set the module name
MODULE := test

FILES := test.c

SRC += $(patsubst %, $(MODULE)/%, $(FILES))
