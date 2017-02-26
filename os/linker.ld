ENTRY(start)

SECTIONS {
	. = 1M;

	/* Boot region. Ensure aligning to 64 bit */
	.boot ALIGN(0x40):
	{
		/* ensure that the multiboot header is at the beginning */
		KEEP(*(.multiboot_header))
	}

	.text :
	{
		*(.text)
	}

	/* Read-only data. */
	.ro_data BLOCK(4K) : ALIGN(4K)
	{
		*(.ro_data)
	}

	/* Read-write data (initialized) */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
}
