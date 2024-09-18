#include "INC.h"
.section boot_start
.text  # 以下是代码区
.code16 # 指定以下的代码生成16位的机器指令，这样才能在启动时的实模式下运行
.global _start  # 声明本地以下符号是全局的，在其它源文件中可以访问
.extern boot_entry 
_start:
jmp _start_s

#.align 1 # 事实上8086指令不需要对齐，对齐会浪费存储，这里只是为了方便
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
    movw $0x8000, %bx
    movb $0x00, %ch
    movb $0x2, %cl
    movb $0x02, %ah
    movb $0x20, %al 
    movb $0x00, %dh
    movb $0x80, %dl
    int $0x0013
    jc _copy_from_disk_to_mem	# 读取失败，则重复
# jmp _loop
.test:
push %eax
pop %eax
_boot_entry_c:
call boot_entry 
add $4, %esp
_loop_16:
    jmp .
_my_string:
    # .byte 0x48, 0x65, 0x6C, 0x6C, 0x6F
    .asciz "Hello, World! 16bit Mode now..."
