CC=x86_64-elf-gcc
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra

QEMU=qemu-system-x86_64
QEMU_FLAGS=-m 16G
BOCHS=bochs
AS=nasm
AFLAGS=-f elf64

LD=ld
LDFLAGS=-n -Map=kernel.map
LDSCRIPT=src/linker.ld

ASM_SOURCES=$(wildcard src/*.asm)
ASM_OBJECTS=$(ASM_SOURCES:.asm=.o)

SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)

# PATHS
BIN=./bin
SOURCE=src
ISOFILES=isofiles
KERNEL=$(BIN)/kernel.bin
ISO=$(BIN)/os.iso
DEBUG_DIR=./debug


.PHONY: clean run iso all

all: iso

# $<  --- Input file
# $@  --- Input filename
%.o: %.asm
	$(AS) $(AFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compiles the kernel, using LDSCRIPT
$(KERNEL): $(ASM_OBJECTS) $(OBJECTS)
	$(LD) $(LDFLAGS) -o $(KERNEL) -T $(LDSCRIPT) $(ASM_OBJECTS) $(OBJECTS)
	objdump -D $(KERNEL) > kernel.dump


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
	-rm -rfv $(ASM_OBJECTS)
	-rm -rfv $(ISO)
