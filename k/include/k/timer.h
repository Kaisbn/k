#ifndef K_TIMER_H_
#define K_TIMER_H_

#include "k/types.h"

#define PIT   0x43
#define DATA0 0x40
#define MODE2 0x34

unsigned long counter = 0;

struct registers
{
  u32 ds;
  u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
  u32 int_no, err_code;
  u32 epi, cs, eflags, useresp, ss;
};

unsigned long gettick(void);
void timer_handler(struct registers regs);
void init_timer(void);

#endif /* K_TIMER_H_ */
