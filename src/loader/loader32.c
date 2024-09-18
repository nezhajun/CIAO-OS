#include "types.h"
#include "cpu_instr.h"
#include "boot_info.h"
#include "elf32.h"
#include "string.h"


extern boot_info_t boot_info;
/**
* 使用LBA48位模式读取磁盘
*/
static void read_disk(int sector, int sector_count, uint8_t * buf) {
    outb(0x1F6, (uint8_t) (0xE0));

	outb(0x1F2, (uint8_t) (sector_count >> 8));
    outb(0x1F3, (uint8_t) (sector >> 24));		// LBA参数的24~31位
    outb(0x1F4, (uint8_t) (0));					// LBA参数的32~39位
    outb(0x1F5, (uint8_t) (0));					// LBA参数的40~47位

    outb(0x1F2, (uint8_t) (sector_count));
	outb(0x1F3, (uint8_t) (sector));			// LBA参数的0~7位
	outb(0x1F4, (uint8_t) (sector >> 8));		// LBA参数的8~15位
	outb(0x1F5, (uint8_t) (sector >> 16));		// LBA参数的16~23位

	outb(0x1F7, (uint8_t) 0x24);

	// 读取数据
	uint16_t *data_buf = (uint16_t*) buf;
	while (sector_count-- > 0) {
		// 每次扇区读之前都要检查，等待数据就绪
		while ((inb(0x1F7) & 0x88) != 0x8) {}

		// 读取并将数据写入到缓存中
		for (int i = 0; i < SECTOR_SIZE / 2; i++) {
			*data_buf++ = inw(0x1F0);
		}
	}
}

/**
 * 死机
 */
static void die (int code) {
    for (;;) {
    }
}

/**
 * 解析elf文件，提取内容到相应的内存中
 * https://wiki.osdev.org/ELF
 * @param file_buffer
 * @return
 */
//static uint32_t reload_elf_file (uint8_t * file_buffer) {
//    // 读取的只是ELF文件，不像BIN那样可直接运行，需要从中加载出有效数据和代码
//    // 简单判断是否是合法的ELF文件
//    Elf32_Ehdr * elf_hdr = (Elf32_Ehdr *)file_buffer;
//    if ((elf_hdr->e_ident[0] != ELF_MAGIC) || (elf_hdr->e_ident[1] != 'E')
//        || (elf_hdr->e_ident[2] != 'L') || (elf_hdr->e_ident[3] != 'F')) {
//        return 0;
//    }
//
//    // 然后从中加载程序头，将内容拷贝到相应的位置
//    for (int i = 0; i < elf_hdr->e_phnum; i++) {
//        Elf32_Phdr * phdr = (Elf32_Phdr *)(file_buffer + elf_hdr->e_phoff) + i;
//        if (phdr->p_type != PT_LOAD) {
//            continue;
//        }
//
//		// 全部使用物理地址，此时分页机制还未打开
//        uint8_t * src = file_buffer + phdr->p_offset;
//        uint8_t * dest = (uint8_t *)phdr->p_paddr;
//        for (int j = 0; j < phdr->p_filesz; j++) {
//            *dest++ = *src++;
//        }
//
//		// memsz和filesz不同时，后续要填0
////		dest= (uint8_t *)phdr->p_paddr + phdr->p_filesz;
////		for (int j = 0; j < phdr->p_memsz - phdr->p_filesz; j++) {
////			*dest++ = 0;
////		}
//    }
//
//    return elf_hdr->e_entry;
//}

void protect_mode_entry()
{
	asm volatile(
        "jmp $8, $refresh_cs_segment_\n\t"
        "refresh_cs_segment_:"
        "movw $16, %%ax\n\t"
        "movw %%ax, %%ds\n\t"
        "movw %%ax, %%ss\n\t"
        "movw %%ax, %%es\n\t"
        "movw %%ax, %%gs\n\t"
        "movw %%ax, %%fs\n\t"
		"movl $0x10000, %%eax\n\t"
		"sub $8, %%eax\n\t"
		"movl %%eax, %%esp"
		::
	);
    read_disk(100,500,(void *)(SYS_KERNEL_LOAD_ADDR));
    //asm volatile(" jmp $8, $SYS_KERNEL_LOAD_ADDR"::);
    uint32_t kernel_entry =(uint32_t)elf_parse((void *)SYS_KERNEL_LOAD_ADDR);
	if (kernel_entry == 0) {
		die(-1);
	}

	// 转换为函数指针，然后跳进内核
//    ((void (*) (void)) kernel_entry )();
    ((void (*)(boot_info_t *))kernel_entry)(&boot_info);
    for (;;)
    {
        /* code */
    }
    
}