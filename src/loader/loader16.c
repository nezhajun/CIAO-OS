__asm__(".code16gcc");
//asm(".code16");

#include "loader16.h"
#include "types.h"
#include "boot_info.h"
#include "cpu_instr.h"
boot_info_t boot_info;			// 启动参数信息
func_t init_sequence[] = 
{
    show_message,
    detect_mem_is_ok,
    enter_protect_mode,
    NULL,
};

struct gdt_entry gdt_table[4] __attribute__((aligned(8))) =
{
    [0]={0},
    [1]={0xffff, 0x0000, 0x9a00, 0x00cf},
    [2]={0xffff, 0x0000, 0x9200, 0x00cf},
};


// 在链接时候没有_start标号会报错，实际上只要构造函数名称为_start即可，用下面的函数可以
// 替换掉start.S 文件，为了统一方便，还是使用了start.S 文件，下面的函数就没有使用
void _start() 
{
    asm volatile("nop");
    loader16_init();
    for (;;)
    {
        /* code */
    }
    
}

static void my_puts(const char * msg) {
    char c;

	// 使用bios写显存，持续往下写
	while ((c = *msg++) != '\0') {
		__asm__ __volatile__(
				"movb $0xe, %%ah\n\t"
				"movb %[ch], %%al\n\t"
				"int $0x10"::[ch]"r"(c));
	}
}

static void  detect_memory(void) {
	uint32_t contID = 0;
	SMAP_entry_t smap_entry;
	int signature, bytes;

    my_puts("try to detect memory:");

	// 初次：EDX=0x534D4150,EAX=0xE820,ECX=24,INT 0x15, EBX=0（初次）
	// 后续：EAX=0xE820,ECX=24,
	// 结束判断：EBX=0
	boot_info.ram_region_count = 0;
	for (int i = 0; i < BOOT_RAM_REGION_MAX; i++) {
		SMAP_entry_t * entry = &smap_entry;

		__asm__ __volatile__("int  $0x15"
			: "=a"(signature), "=c"(bytes), "=b"(contID)
			: "a"(0xE820), "b"(contID), "c"(24), "d"(0x534D4150), "D"(entry));
		if (signature != 0x534D4150) {
            my_puts("failed.\r\n");
			return;
		}

		// todo: 20字节
		if (bytes > 20 && (entry->ACPI & 0x0001) == 0){
			continue;
		}

        // 保存RAM信息，只取32位，空间有限无需考虑更大容量的情况
        if (entry->Type == 1) {
            boot_info.ram_region_cfg[boot_info.ram_region_count].start = entry->BaseL;
            boot_info.ram_region_cfg[boot_info.ram_region_count].size = entry->LengthL;
            boot_info.ram_region_count++;
        }

		if (contID == 0) {
			break;
		}
	}
    my_puts("ok.\r\n");
}



void loader16_init(void)
{
    uint16_t a =12;
    uint32_t b =234556;
    b = a+b;
    func_t * func_t_p; 
    for (func_t_p = init_sequence; *func_t_p != NULL; func_t_p ++)
    {
        int res = (*func_t_p)(NULL); 
        if (!res)
        {
        }
        
    }
}

int show_message()
{
    my_puts("\r\nEnter loader16...\r\n");
    return 0;
}

int enter_protect_mode()
{
    cli();
    uint8_t v = inb(0x92);
    outb(0x92, v | 0x2);

    struct gdt_n gdt_n_t;
    gdt_n_t.gdt_limit = sizeof(gdt_table) - 1;
    gdt_n_t.gdt_base = (uint32_t)&gdt_table[0];
    lgdt((uint32_t)gdt_n_t.gdt_base, gdt_n_t.gdt_limit);
    uint32_t cr0 = read_cr0();
    write_cr0(cr0 | (1 << 0));
    asm volatile (
       "jmp $8,$protect_mode_entry"
        ::);

    return 0;
}


int detect_mem_is_ok()
{
    detect_memory();
    return 0;
}
