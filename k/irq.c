#include "k/irq.h"
#include "io.h"

void sendEOI(u8 irq)
{
  if (irq > 7)
    outb(PIC2, EOI);
  outb(PIC1, EOI);
}

void set_handler(u8 irq, interrupt handler)
{
  irq_handlers[irq] = handler;
}

void init_pic(void)
{
  outb(0x20, 0x11);
  outb(0xA0, 0x11);
  outb(0x21, 0x20);
  outb(0xA1, 0x28);
  outb(0x21, 0x04);
  outb(0xA1, 0x02);
  outb(0x21, 0x01);
  outb(0xA1, 0x01);
  outb(0x21, 0x00);
  outb(0xA1, 0x00);
}

void init_irq_gates(void)
{
  init_desc(32, (u32)irq0, 0x8, D_INT);
  init_desc(33, (u32)irq1, 0x8, D_INT);
  init_desc(34, (u32)irq2, 0x8, D_INT);
  init_desc(35, (u32)irq3, 0x8, D_INT);
  init_desc(36, (u32)irq4, 0x8, D_INT);
  init_desc(37, (u32)irq5, 0x8, D_INT);
  init_desc(38, (u32)irq6, 0x8, D_INT);
  init_desc(39, (u32)irq7, 0x8, D_INT);
  init_desc(40, (u32)irq8, 0x8, D_INT);
  init_desc(41, (u32)irq9, 0x8, D_INT);
  init_desc(42, (u32)irq10, 0x8, D_INT);
  init_desc(43, (u32)irq11, 0x8, D_INT);
  init_desc(44, (u32)irq12, 0x8, D_INT);
  init_desc(45, (u32)irq13, 0x8, D_INT);
  init_desc(46, (u32)irq14, 0x8, D_INT);
  init_desc(47, (u32)irq15, 0x8, D_INT);
}

void c_irq_handler(struct registers regs)
{
  u8 irq = regs.int_no - 32;
  printf("IRQ: %d\n", irq);
  interrupt handler = irq_handlers[irq];
  if (handler)
    handler(regs);
  sendEOI(irq);
}
