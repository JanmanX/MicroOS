
# Set the module name
MODULE :=

FILES :=

SRC += $(patsubst %, $(MODULE)/%, $(FILES))
