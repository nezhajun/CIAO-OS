#include "INC.h"

.text  # 以下是代码区
.code16 # 指定以下的代码生成16位的机器指令，这样才能在启动时的实模式下运行
.global _start  # 声明本地以下符号是全局的，在其它源文件中可以访问

_start:
jmp _start_s

# gdt描述符，由lgdt加载
.align 8     # gdt需要8字节对齐
GDT_BASE:   .long 0x00000000
            .long 0x00000000

CODE_DESC:  .long 0x0000FFFF
            .long 0x00cf9a00

DATA_DESC:  .long 0x0000FFFF
            .long 0x00cf9300

VIDEO_DESC: .long 0x80000007
            .long 0x00000000

.equ GDT_SIZE, (.-GDT_BASE)
.equ GDT_LIMIT, (GDT_SIZE-1)


.align 1 # 事实上8086指令不需要对齐，对齐会浪费存储，这里只是为了方便

gdt_addr_:
    .word GDT_LIMIT
    .long GDT_BASE

_start_s:
    mov $0x00, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %ss
    mov $_start, %esp

_clear_screen:
    mov $0x600, %ax
    mov $0x700, %bx
    mov $0x00, %cx
    mov $0x184F, %dx
    int $0x10

    jmp _set_cursor

_get_cursor:
    mov $0x03, %ah
    mov $0x00, %bh
    int $0x10

_set_cursor:
    # 设置光标位置到VGA模式的0，0处
    mov $0x02, %ah     # 功能号：设置光标位置
    mov $0x00, %bh     # 页号（VGA模式）
    mov $0x00, %dh     # 行号
    mov $0x00, %dl     # 列号
    int $0x10          # 调用BIOS中断

_print_str:
    mov $_my_string, %ax
    mov %eax, %ebp
    mov $0x1F, %cx
    mov $0x1301, %ax
    mov $0x02, %bx
    int $0x10


# copy 32KB disk to memory
# %bx  # 读取到的内存地址
# ch 磁道号，cl起始扇区号(从 1 开始计数)
# ah 0x02读磁盘命令, al=0x20 32个扇区，多读一些, 16KB
# dh 磁头号，dl驱动器号0x80(磁盘1)
_copy_from_disk_to_mem:
    movw $_start_32, %bx
    movb $0x00, %ch
    movb $0x2, %cl
    movb $0x02, %ah
    movb $0x20, %al 
    movb $0x00, %dh
    movb $0x80, %dl
    int $0x0013
    jc _copy_from_disk_to_mem	# 读取失败，则重复
# jmp _loop

_goto_protected_mode: # 进入32位保护模式
    cli					# 关中断
	lgdt gdt_addr_ #加载gdt表，原来写的是[gdt_desc]，在windows上不识别，所以改了
	mov $1, %ax
	lmsw %ax		# 设置PE位，进入保护模式
    sti                 # 开中断
	jmp $SELECTOR_CODE, $_start_32	# 进入32位保护模式代码，可以运行32位指令

_loop_16:
    jmp .
_my_string:
    # .byte 0x48, 0x65, 0x6C, 0x6C, 0x6F
    .asciz "Hello, World! 16bit Mode now..."

.org 0x1fe
.byte 0x55,0xaa
.text
.code32

//.align 4 //从16位切换到32位需要被对齐
_start_32: # 重新加载数据段寄存器
	mov $SELECTOR_DATA, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss
	mov $_start, %esp
    sub $2, %esp
    jmp _entry_

_loop_32:
    jmp .


# 跳转到C语言位置运行 在C语言中重新设置idt和gdt表 加载kernel 最后开启分页模式，跳转到kernel入口

# C语言中还需要实现磁盘读写的C函数版，用于加载kernel
# 整体扇区划分为3部分，512字节的引导扇区头，32KB的加载程序，其余是kernel程序

# gdt描述符，由lgdt加载
// .align 8 //gdt需要8字节对齐
// gdt_desc: .word (256*8) - 1
// 	.long gdt_table

