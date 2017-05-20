#include <k/idt.h>
#include "multiboot.h"

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
  set_gates();
  init_irq_gates();
	load_idtr();
  __asm__ volatile("int $0x20");
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
