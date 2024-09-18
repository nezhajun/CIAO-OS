
.text
.global cTaskSwitchContext
/*
    cTaskSwitch  ( &from , to)
*/
cTaskSwitchContext: /* 任务切换的核心是切换栈（新的任务的栈存储了地址），而不是jmp 到新的地址*/
// pushal /*EAX ECX EDX EBX ESP EBP ESI EDI*/
// pushfl /* eflag */
    push %ebp
    push %ebx
    push %esi
    push %edi
    movl 20(%esp), %eax /* 获取第一个参数 &current_cTask_t  */
    movl (%eax), %edx /* current_cTask */
    movl %esp, (%edx) /*  *current_cTask_t = %esp  */

    movl 24(%esp), %edx /* 获取第二个函数参数 next_cTask_t */
    movl (%edx) , %esp /* esp 指向要跳转的栈地址 恢复新栈的内容 */

    movl %edx, (%eax) /* 修改 current_cTask_t， current_cTask_t = next_cTask_t */
    pop %edi
    pop %esi
    pop %ebx
    pop %ebp
//    popfl
//    popal
    ret
