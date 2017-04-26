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
	idtr.base = idt;
	idtr.limit = sizeof(idt) - 1;

  memset(&idt, 0, sizeof(struct idt_d) * 256);

	load_idtr();
}
