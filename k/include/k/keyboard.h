#ifndef K_KBD_H_
#define K_KBD_H

#include "k/kstd.h"

struct registers
{
  u32 ds;
  u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
  u32 int_no, err_code;
  u32 epi, cs, eflags, useresp, ss;
};

int getkey(void);
void keyboard_handler(struct registers regs);

#endif /* K_KBD_H_ */
