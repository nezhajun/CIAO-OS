#include "timer.h"
#include "irq.h"
#include "cpu_instr.h"
#include "ctask.h"
#include "printk.h"

static uint32_t sys_tick;						// 系统启动后的tick数量

static void init_pit (void) {
    uint32_t reload_count = PIT_OSC_FREQ / (1000.0 / OS_TICK_MS);

    // 2023-3-18 写错了，应该是模式3或者模式2
    //outb(PIT_COMMAND_MODE_PORT, PIT_CHANNLE0 | PIT_LOAD_LOHI | PIT_MODE0);
    outb(PIT_COMMAND_MODE_PORT, PIT_CHANNLE0 | PIT_LOAD_LOHI | PIT_MODE3);
    outb(PIT_CHANNEL0_DATA_PORT, reload_count & 0xFF);   // 加载低8位
    outb(PIT_CHANNEL0_DATA_PORT, (reload_count >> 8) & 0xFF); // 再加载高8位

    irq_install(IRQ0_TIMER, (irq_handler_t)exception_handler_timer);
    irq_enable(IRQ0_TIMER);
    irq_enable_global();
}

void time_init (void) {
    sys_tick = 0;
    init_pit();
}


void do_handler_timer(exception_frame_t * frame)
{
    pic_send_eoi(IRQ0_TIMER); // 向 PIC 发送 EOI 清除PIC 的中断位，但是IF中断位依旧是0 ，总中断被禁止
    // printk("frame->eflags:0x%x \r\n",frame->eflags);
    sys_tick ++;
    cTaskSystemTickHandler();
    
}


