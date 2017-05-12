#include <stdint.h>

#include <lib/klib.h>
#include "multiboot2.h"
#include <kernel/interrupt.h>
#include <drivers/keyboard.h>
#include <drivers/pci.h>
#include <init/xsdt.h>
#include <test/test.h>

void main(unsigned long mb_info_struct_addr)
{
	/* Init page tables */
	init_page_tables_identity();
	kprintf("Page tables inited\n");


	uint64_t *ptr = (uint64_t*)0x0000000f000000;
	*ptr = 0xDEADDEAD1337;
	kprintf("PTR: 0x%x\n", *ptr);
	BOCHS_DEBUG;
	HALT;
	/* */
	//xsdt_init();

	//pci_init();

	/* Retrieve information from bootloader */
	struct multiboot_tag *tag;
	uint32_t size;

	const char* mmap_type_to_string[5];
	mmap_type_to_string[0] ="reserved";	// 0 -
	mmap_type_to_string[1] ="available";	// 1 -
	mmap_type_to_string[2] ="_reserved";    // 2 (unspecified?)
	mmap_type_to_string[3] ="usable ACPI";	// 3 -
	mmap_type_to_string[4] ="reserved";	// 4 -


	size = *(uint32_t *) mb_info_struct_addr;
	kprintf ("Announced mbi size 0x%x\n", size);

	for (tag = (struct multiboot_tag *) (mb_info_struct_addr + 8);
	     tag->type != MULTIBOOT_TAG_TYPE_END;
	     tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag
					     + ((tag->size + 7) & ~7)))
	{
		kprintf ("Tag 0x%x, Size 0x%x\n", tag->type, tag->size);
		switch (tag->type)
		{
		case MULTIBOOT_TAG_TYPE_CMDLINE:
			kprintf ("Command line = %s\n",
				 ((struct multiboot_tag_string *) tag)->string);
			break;
		case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
			kprintf ("Boot loader name = %s\n",
				 ((struct multiboot_tag_string *) tag)->string);
			break;
		case MULTIBOOT_TAG_TYPE_MODULE:
			kprintf ("Module at 0x%x-0x%x. Command line %s\n",
				 ((struct multiboot_tag_module *) tag)->mod_start,
				 ((struct multiboot_tag_module *) tag)->mod_end,
				 ((struct multiboot_tag_module *) tag)->cmdline);
			break;
		case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
			kprintf ("mem_lower = %uKB, mem_upper = %uKB\n",
				 ((struct multiboot_tag_basic_meminfo *) tag)->mem_lower,
				 ((struct multiboot_tag_basic_meminfo *) tag)->mem_upper);
			break;
		case MULTIBOOT_TAG_TYPE_BOOTDEV:
			kprintf ("Boot device 0x%x,%u,%u\n",
				 ((struct multiboot_tag_bootdev *) tag)->biosdev,
				 ((struct multiboot_tag_bootdev *) tag)->slice,
				 ((struct multiboot_tag_bootdev *) tag)->part);
			break;
		case MULTIBOOT_TAG_TYPE_MMAP: {
			multiboot_memory_map_t *mmap;

			kprintf ("mmap\n");

			for (mmap = ((struct multiboot_tag_mmap *) tag)->entries;
			     (multiboot_uint8_t *) mmap
			     < (multiboot_uint8_t *) tag + tag->size;
			     mmap = (multiboot_memory_map_t *)
			     ((unsigned long) mmap
			      + ((struct multiboot_tag_mmap *) tag)->entry_size)) {
				/* Print split in two, because kprintf cannot
				 * handle this many format strings */
				kprintf (" base_addr = 0x%x%x,"
					 " length = 0x%x%x ",
					 (unsigned) (mmap->addr >> 32),
					 (unsigned) (mmap->addr & 0xffffffff),
					 (unsigned) (mmap->len >> 32),
					 (unsigned) (mmap->len & 0xffffffff));
				if((unsigned)mmap->type < 4) {
					kprintf("type = 0x%x = %s\n",
						(unsigned) mmap->type,
						mmap_type_to_string[mmap->type]);
				} else {
					kprintf("type = 0x%x\n",
						(unsigned) mmap->type);

				}
			}

		}
			break;

		case MULTIBOOT_TAG_TYPE_VBE: {
			struct multiboot_tag_vbe *tag_vbe
				= (struct multiboot_tag_vbe *) tag;

			break;
		}

		case MULTIBOOT_TAG_TYPE_FRAMEBUFFER: {
			struct multiboot_tag_framebuffer *tag_fb
				= (struct multiboot_tag_framebuffer *) tag;

			break;
		}
		}

	}

	HALT;

	tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag
					+ ((tag->size + 7) & ~7));
	kprintf ("Total mbi size 0x%x\n", (uint64_t)(uint32_t)tag - mb_info_struct_addr);

	kprint("Main()\n");

	DEBUG("INTERRUPT INIT");
	interrupt_init();
	DEBUG("KEYBOARD INIT");
	keyboard_init();

	pci_init();

	DEBUG("LOOP");
	kprintf("PIC MASK: 0x%x\n", pic_get_mask());

	asm volatile("int $02");

	char c[2] = {0};
	for(;;) {
		while(keyboard_keys_available()) {
			c[0] = keyboard_get_key();
			kprintf("%s", c);
		}

	}


	return;
}
