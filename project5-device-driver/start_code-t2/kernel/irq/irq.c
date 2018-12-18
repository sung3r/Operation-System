#include "irq.h"
#include "mac.h"
#include "time.h"
#include "sched.h"
#include "string.h"
#include "screen.h"
int j = 1;
int location = -2;
int tt = 0;
static void irq_timer()
{
    // TODO clock interrupt handler.
    // scheduler, time counter in here to do, emmmmmm maybe.
    screen_reflush();
    time_elapsed += 200000;
    current_running->cursor_x = screen_cursor_x;
    current_running->cursor_y = screen_cursor_y;
    do_scheduler();
    //if(current_running->pid != 0 && current_running->pid != 1)
    //{
    //    vt100_move_cursor(0+tt++, 13);
    //    printk("%d", current_running->pid);
    //}
    if(!queue_is_empty(&recv_block_queue) && !((*(uint32_t *)recv_flag[ch_flag]) & DescOwnByDma))
        do_unblock_one(&recv_block_queue);
    screen_cursor_x = current_running->cursor_x;
    screen_cursor_y = current_running->cursor_y;
}

void other_exception_handler()
{
    // TODO other exception handler
    time_elapsed += 200000;
}

void interrupt_helper(uint32_t status, uint32_t cause)
{
    // TODO interrupt handler.
    // Leve3 exception Handler.
    // read CP0 register to analyze the type of interrupt.
    uint32_t interrupt = status & cause & 0x0000ff00;
    if(interrupt & 0x00008000)
        irq_timer();
    else
        other_exception_handler();
}