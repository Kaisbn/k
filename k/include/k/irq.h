#ifndef K_IRQ_H_
#define K_IRQ_H_

#include "k/types.h"

#define PIC1 0x20
#define PIC2 0xA0
#define EOI  0x20
#define D_INT             0x8E

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

struct registers
{
  u32 ds;
  u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
  u32 int_no, err_code;
  u32 epi, cs, eflags, useresp, ss;
};

void *irq_handlers[16] = { 0 };

void sendEOI(u8 irq);
void init_pic(void);
void init_irq_gates(void);

#endif /* K_IRQ_H_ */
