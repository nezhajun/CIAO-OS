/* 参考文档： https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_chapter/ld_3.html */
SECTIONS
{
    . = 0x0010000; /**/

	.text : {
		init/start.o(.text)
		*(.text)
	} 

	.rodata : {
		*(.rodata)
	}

/*	. = 0x200000; */
	.data : {
		*(.data)
	}

	__bss_start = .;
	.bss : {
		*(.bss)
	}
	__bss_end = .;

}
