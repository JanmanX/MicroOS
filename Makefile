QEMU=qemu-system-x86_64
QEMU_FLAGS=-m 100M -s #-cpu host -enable-kvm
#QEMU_DRIVE=-drive id=disk,file=hdd.bin,if=none -device ahci,id=ahci -device ide-drive,drive=disk,bus=ahci.0

GRUB=grub2
GRUB_KERNEL=#-bios ./debug/qemu/bios.bin
BOCHS=bochs
DEBUG_DIR=./debug

all:
	make -C os


iso: all
	cp os/kernel.bin isofiles/boot/
	$(GRUB)-mkrescue -o os.iso isofiles/

run: iso
	$(QEMU) $(GRUB_KERNEL) $(QEMU_FLAGS) -cdrom  os.iso

debug: iso
	$(QEMU) $(GRUB_KERNEL) $(QEMU_FLAGS) $(QEMU_DRIVE)  -S -cdrom  os.iso



bochs: iso
	$(BOCHS) -f $(DEBUG_DIR)/bochs/bochs.conf -q

tags:
	find os/ | xargs ctags


