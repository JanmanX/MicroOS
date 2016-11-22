ENTRY(start)

SECTIONS {
	. = 1M;

	.boot :
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
