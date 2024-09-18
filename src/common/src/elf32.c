
#include "elf32.h"
#include "string.h"


// 返回elf文件的虚拟入口地址
void *  elf_parse(void *bin_addr) // bin_addr: elf 源二进制程序的地址，解析出elf中的代码组装后复制到的地址
{
    Elf32_Ehdr *elf32_ehdr_ptr;
    Elf32_Addr elf32_entry;
    elf32_ehdr_ptr = bin_addr; //判断魔数是否正确 判断是否是可执行文件
    if( elf32_ehdr_ptr->e_ident[EI_MAG0] == ELFMAG0 && \
        elf32_ehdr_ptr->e_ident[EI_MAG1] == ELFMAG1 && \
        elf32_ehdr_ptr->e_ident[EI_MAG2] == ELFMAG2 && \
        elf32_ehdr_ptr->e_ident[EI_MAG3] == ELFMAG3 && \
        elf32_ehdr_ptr->e_type == ET_EXEC
     )
    {
        elf32_entry = elf32_ehdr_ptr->e_entry;
        Elf32_Half ph_size;
        Elf32_Half ph_num;
        Elf32_Off ph_off;
        Elf32_Word ph_type;

        Elf32_Phdr *ph_addr; //程序头的地址
        ph_size = elf32_ehdr_ptr->e_phentsize; //程序头的长度大小(一般等于 Elf32_Phdr 结构体的大小)
        ph_num = elf32_ehdr_ptr->e_phnum; //程序头的数量
        ph_off = elf32_ehdr_ptr->e_phoff; //第一个程序头偏移量
        ph_addr = bin_addr + ph_off; //第一个程序头的地址

        int i;
        for(i=0;i<ph_num;i++)
        {
            if( ph_addr->p_type != PT_NULL) //程序头表明段类型为空
            {
                memcpy((void *)ph_addr->p_vaddr,(ph_addr->p_offset)+bin_addr,ph_addr->p_filesz);
                ph_addr++;
            }
            else
                ph_addr++;
        }
        return (void *)elf32_entry; //elf文件的虚拟入口地址
    }
    else
    {
        /* code */
        return NULL;
    }
}





