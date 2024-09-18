.text
.code32
.extern kernel_init

_start:
    push %ebp
    movl %esp, %ebp
    movl 0x08(%ebp), %eax
    
    push %eax
    call kernel_init
    jmp .