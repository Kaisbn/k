#ifndef K_GDT_H_
#define K_GDT_H_

#include <k/types.h>

struct gdt_r
{
  u16 limit;
  u32 base;
}__attribute__((packed));

struct gdt_d
{
  u16 base_lo; //15:00  => & Oxffff
  u16 limit_lo; //15:00 => & 0xffff
  u8 base_mid; //23:16 => & 0xff0000
  u8 access; // P DPL S Type
  u8 limit_hi : 4;  //19:16 => 0xf0000
  u8 flags : 4; // G D/B L AVL => Oxf
  u8 base_hi; //31:24 => & 0xff000000
}__attribute__((packed));

void init_gdt();

#endif /* !K_GDT_H_ */
