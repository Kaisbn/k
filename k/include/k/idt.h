#ifndef K_IDT_H_
#define K_IDT_H_

#include <k/types.h>

#define P_SET             0x01
#define DPL               0x00
#define D_TRAP            0xF
#define D_INT             0xE

struct idt_r
{
  u16 limit;
  u32 base;
}__attribute__((packed));

struct idt_d
{
  u16 offset_lo;
  u16 seg;
  u8 res : 8;
  u8 gate : 5;
  u8 dpl : 2;
  u8 p : 1;
  u16 offset_hi;
}__attribute__((packed));

void init_idt();
struct idt_r idtr;
struct idt_d idt[256];

#endif /* !K_GDT_H_ */
