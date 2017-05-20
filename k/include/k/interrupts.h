#ifndef K_INT_H_
#define K_INT_H_

#include "k/types.h"

#define D_INT             0x8E
#define D_TRAP            0x8F

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();


const char* messages[] = {
  "Division By Zero",
  "Debug",
  "NMI",
  "Breakpoint",
  "Overflow",
  "Bound Range Exceeded",
  "Invalid Opcode",
  "Device Not Available",
  "Double Fault",
  "Coprocessor",
  "Invalid TSS",
  "Segment not present",
  "Stack Segment Fault",
  "General Protection",
  "Page Fault",
  "Reserved",
  "Math Fault",
  "Alignment Check",
  "Machine Check",
  "SMD Floating Point Ex.",
  "Virtualization Ex.",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
};

struct registers
{
  u32 ds;
  u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
  u32 int_no, err_code;
  u32 epi, cs, eflags, useresp, ss;
};

void set_gates(void);
void c_handler(struct registers regs);

#endif /* !K_INT_H_ */
