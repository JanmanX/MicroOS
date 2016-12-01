CC=x86_64-elf-gcc
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
C_INC=-I ./src/

QEMU=qemu-system-x86_64
QEMU_FLAGS=-m 16G
BOCHS=bochs
AS=nasm
AFLAGS=-f elf64
AS_INC=-I ./src/init/ -I ./src/


LD=ld
LDFLAGS=-n -Map=$(KERNEL_MAP_FILE)
LDSCRIPT=src/linker.ld

ASM_SOURCES=$(wildcard src/*.asm src/init/*.asm)
ASM_OBJECTS=$(ASM_SOURCES:.asm=.o)

SOURCES=$(wildcard src/*.c src/lib/*.c)
OBJECTS=$(SOURCES:.c=.o)

# PATHS
BIN=./bin
SOURCE=src
ISOFILES=isofiles
KERNEL=$(BIN)/kernel.bin
ISO=$(BIN)/os.iso
DEBUG_DIR=./debug

# Miscellaneous
KERNEL_MAP_FILE=./kernel.map
KERNEL_DUMP_FILE=./kernel.dump


.PHONY: clean run iso all

all: $(ISO)

# $<  --- Input file
# $@  --- Input filename
%.o: %.asm
	$(AS) $(AS_INC) $(AFLAGS) $< -o $@

%.o: %.c
	$(CC) $(C_INC) $(CFLAGS) -c $< -o $@

# Compiles the kernel, using LDSCRIPT
$(KERNEL): $(ASM_OBJECTS) $(OBJECTS)
	$(LD) $(LDFLAGS) -o $(KERNEL) -T $(LDSCRIPT) $(ASM_OBJECTS) $(OBJECTS)
	objdump -D $(KERNEL) > $(KERNEL_DUMP_FILE)


$(ISO): $(KERNEL)
	cp $(KERNEL) $(ISOFILES)/boot/
	grub-mkrescue -o $(ISO) $(ISOFILES)

run: $(ISO)
	$(QEMU) $(QEMU_FLAGS) -cdrom $(ISO)

debug: $(ISO)
	$(QEMU) $(QEMU_FLAGS) -cdrom $(ISO) -s -S

bochs: $(ISO)
	$(BOCHS) -f $(DEBUG_DIR)/bochs/bochs.conf -q

clean:
	-rm -rfv bin/*
	-rm -fv src/*.o
	-rm -rfv $(ASM_OBJECTS)
	-rm -rfv $(ISO)
	-rm -fv $(KERNEL_MAP_FILE)
	-rm -fv $(KERNEL_DUMP_FILE)
