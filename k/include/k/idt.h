#ifndef K_IDT_H_
#define K_IDT_H_

#include <k/types.h>

#define D_INT             0x8E
#define D_TRAP            0x8F

struct idt_r
{
  u16 limit;
  u32 base;
}__attribute__((packed));

struct idt_d
{
  u16 offset_lo;
  u16 sel;
  u8 offset_mid;
  u8 type;
  u16 offset_hi;
}__attribute__((packed));

void init_idt(void);
void init_desc(u8 nbr, u32 base, u16 sel, u8 type);

void init_idt();
struct idt_r idtr;
struct idt_d idt[256];

extern void keyboard_handler();
extern void timer_handler();
extern void write_handler(struct registers *regs);
extern void getkey_handler(struct registers *regs);
extern void gettick_handler(struct registers *regs);
extern void open_handler(struct registers *regs);
extern void read_handler(struct registers *regs);
extern void seek_handler(struct registers *regs);
extern void close_handler(struct registers *regs);

#endif /* !K_IDT_H_ */
