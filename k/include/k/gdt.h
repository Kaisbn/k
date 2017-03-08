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
  u16 limit_lo; //15:00 => & 0xffff
  u16 base_lo; //15:00  => & Oxffff
  u8 base_mid; //23:16 => & 0xff0000
  u8 type : 4;
  u8 s : 1;
  u8 dpl : 2;
  u8 p : 1;
  u8 limit_hi : 4;  //19:16 => 0xf0000
  u8 avl : 1;
  u8 l : 1;
  u8 db : 1;
  u8 g : 1;
  u8 base_hi; //31:24 => & 0xff000000
}__attribute__((packed));

void init_gdt();
void print_gdt();
struct gdt_r gdtr;
struct gdt_d gdt[3];

#endif /* !K_GDT_H_ */
