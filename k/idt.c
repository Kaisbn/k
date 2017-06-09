#include <k/idt.h>
#include <k/kstd.h>
#include "io.h"

static void load_idtr(void)
{
	asm volatile("lidt %0\n\t"
			:
			: "m"(idtr)
			: "memory");
}

void init_idt(void)
{
	idtr.base = (u32)&idt;
	idtr.limit = sizeof(struct idt_d) * 256 - 1;

  memset(&idt, 0, sizeof(struct idt_d) * 256);
  init_pic();
  set_gates();
  init_irq_gates();
  set_handler(0, timer_handler);
  set_handler(1, keyboard_handler);
  set_syscall_handler(SYSCALL_WRITE, write_handler);
  set_syscall_handler(SYSCALL_GETKEY, getkey_handler);
  set_syscall_handler(SYSCALL_GETTICK, gettick_handler);
  set_syscall_handler(SYSCALL_OPEN, open_handler);
  set_syscall_handler(SYSCALL_READ, read_handler);
  set_syscall_handler(SYSCALL_SEEK, seek_handler);
  set_syscall_handler(SYSCALL_CLOSE, close_handler);
  set_syscall_handler(SYSCALL_SETVIDEO, setvideo_handler);
  set_syscall_handler(SYSCALL_SWAP_FRONTBUFFER, swap_frontbuffer_handler);
  set_syscall_handler(SYSCALL_SBRK, sbrk_handler);
  init_timer();
  load_idtr();
  asm volatile ("sti");
}

void init_desc(u8 nbr, u32 base, u16 sel, u8 type)
{
  struct idt_d *gate = &idt[nbr];
  gate->offset_lo = base & 0xFFFF;
  gate->sel = sel;
  gate->offset_mid = 0;
  gate->type = type;
  gate->offset_hi = (base >> 16) & 0xFFFF;
}
