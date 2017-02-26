QEMU=qemu-system-x86_64
QEMU_FLAGS=-m 20 -s -cpu Broadwell
BOCHS=bochs
GRUB=grub2




all:
	make -C os


iso: all
	cp os/kernel.bin isofiles/boot/
	$(GRUB)-mkrescue -o os.iso isofiles/

run: iso
	$(QEMU) $(QEMU_FLAGS) -cdrom $(ISO) os.iso

bochs: all
	$(BOCHS) -f $(DEBUG_DIR)/bochs/bochs.conf -q

tags:
	find src/ | xargs ctags


