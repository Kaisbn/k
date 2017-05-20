#include "k/interrupts.h"

void set_gates()
{
  init_desc(0, (u32)isr0, 0x8, D_INT);
  init_desc(1, (u32)isr1, 0x8, D_INT);
  init_desc(2, (u32)isr2, 0x8, D_INT);
  init_desc(3, (u32)isr3, 0x8, D_INT);
  init_desc(4, (u32)isr4, 0x8, D_INT);
  init_desc(5, (u32)isr5, 0x8, D_INT);
  init_desc(6, (u32)isr6, 0x8, D_INT);
  init_desc(7, (u32)isr7, 0x8, D_INT);
  init_desc(8, (u32)isr8, 0x8, D_INT);
  init_desc(9, (u32)isr9, 0x8, D_INT);
  init_desc(10, (u32)isr10, 0x8, D_INT);
  init_desc(11, (u32)isr11, 0x8, D_INT);
  init_desc(12, (u32)isr12, 0x8, D_INT);
  init_desc(13, (u32)isr13, 0x8, D_INT);
  init_desc(14, (u32)isr14, 0x8, D_INT);
  init_desc(15, (u32)isr15, 0x8, D_INT);
  init_desc(16, (u32)isr16, 0x8, D_INT);
  init_desc(17, (u32)isr17, 0x8, D_INT);
  init_desc(18, (u32)isr18, 0x8, D_INT);
  init_desc(19, (u32)isr19, 0x8, D_INT);
  init_desc(20, (u32)isr20, 0x8, D_INT);
  init_desc(21, (u32)isr21, 0x8, D_INT);
  init_desc(22, (u32)isr22, 0x8, D_INT);
  init_desc(23, (u32)isr23, 0x8, D_INT);
  init_desc(24, (u32)isr24, 0x8, D_INT);
  init_desc(25, (u32)isr25, 0x8, D_INT);
  init_desc(26, (u32)isr26, 0x8, D_INT);
  init_desc(27, (u32)isr27, 0x8, D_INT);
  init_desc(28, (u32)isr28, 0x8, D_INT);
  init_desc(29, (u32)isr29, 0x8, D_INT);
  init_desc(30, (u32)isr30, 0x8, D_INT);
  init_desc(31, (u32)isr31, 0x8, D_INT);
}

void c_handler(struct registers regs)
{
  if (regs.int_no < 32)
  {
    printf("Interrupt: %s\n", messages[regs.int_no]);
    for (;;);
  }
}
