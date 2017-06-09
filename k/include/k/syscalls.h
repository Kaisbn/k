#ifndef K_SYSCALLS_H_
#define K_SYSCALLS_H_

#include "k/types.h"

#define D_INT 0x8E

extern void sys_int();

struct registers
{
  u32 gs, fs, es, ds;
  u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
  u32 int_no, err_code;
  u32 epi, cs, eflags, useresp, ss;
};

void *syscall_handlers[256] = {0};
typedef void (*syscall)(struct registers*);

void set_syscall_handler(int id, syscall handler);
void c_syscall_handler(struct registers *regs);
void print_handler(struct registers *regs);
void write_handler(struct registers *regs);
void getkey_handler(struct registers *regs);
void gettick_handler(struct registers *regs);
void open_handler(struct registers *regs);
void read_handler(struct registers *regs);
void seek_handler(struct registers *regs);
void close_handler(struct registers *regs);

#endif /* !K_SYSCALLS_H_ */
