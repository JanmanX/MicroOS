CC=x86_64-elf-gcc
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra

QEMU=qemu-system-x86_64
QEMU_FLAGS=-m 16G
BOCHS=bochs
AS=nasm
AFLAGS=-f elf64

LD=ld
LDFLAGS=-n
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
ISO=os.iso
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


iso: $(KERNEL)
	mv $(KERNEL) $(ISOFILES)/boot/
	grub-mkrescue -o $(BIN)/$(ISO) $(ISOFILES)

run: iso
	$(QEMU) $(QEMU_FLAGS) -cdrom $(ISO)

debug: iso
	$(QEMU) $(QEMU_FLAGS) -cdrom $(ISO) -s -S

bochs: iso
	$(BOCHS) -f $(DEBUG_DIR)/bochs/bochs.conf -q

clean:
	-rm -rfv bin/*
	-rm -rfv $(ASM_OBJECTS)
	-rm -rfv $(ISO)
