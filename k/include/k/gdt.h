#ifndef K_GDT_H_
#define K_GDT_H_

#include <k/types.h>

#define G_SET             0x8
#define DB_SET            0x4
#define L_SET             0x2
#define AVL_SET           0x1

#define P_SET             0x80
#define DPL_USER          0x60
#define S_SET             0x10
#define TYPE_RX           0xA
#define TYPE_RW           0x2

struct gdt_r
{
  u16 limit;
  u32 base;
}__attribute__((packed));

struct gdt_d
{
  u16 limit_lo;
  u16 base_lo;
  u8 base_mid;
  u8 type : 4;
  u8 s : 1;
  u8 dpl : 2;
  u8 p : 1;
  u8 limit_hi : 4;
  u8 avl : 1;
  u8 l : 1;
  u8 db : 1;
  u8 g : 1;
  u8 base_hi;
}__attribute__((packed));

void init_gdt();

#endif /* !K_GDT_H_ */
