#include "k/irq.h"
#include "io.h"

void sendEOI(u8 irq)
{
  if (irq > 7)
    outb(EOI, PIC2);
  outb(EOI, PIC1);
}

void init_pic(void)
{
  outb(0x11, 0x20); 
  outb(0x11, 0xA0); 
  outb(0x20, 0x21);
  outb(0x28, 0xA1);
  outb(0x04, 0x21);
  outb(0x02, 0xA1);
  outb(0x01, 0x21);
  outb(0x01, 0xA1);
  outb(0x0, 0x21);
  outb(0x0, 0xA1);
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
  typedef void (*interrupt)(struct registers);
  sendEOI(irq);
  if (irq_handlers[irq] != 0)
  {
    interrupt handler = irq_handlers[irq];
    handler(regs); 
  }
  printf("IRQ: %d\n", irq);
}
