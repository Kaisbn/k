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
	idtr.base = &idt;
	idtr.limit = sizeof(idt) - 1;

  printf("Memset\n");
  memset(&idt, 0, sizeof(idt));
  printf("Setting Gates\n");
  set_gates();
  printf("Loading idtr\n");
	load_idtr();
  printf("Interruption\n");
  __asm__ volatile("int $0x10");
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
