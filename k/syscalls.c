#include "k/syscalls.h"

void init_syscall()
{
  init_desc(0x80, (u32)sys_int, 0x8, D_INT);
}

void set_syscall_handler(int id, syscall handler)
{
  syscall_handlers[id] = handler;
}

void c_syscall_handler(struct registers *regs)
{
  u8 id = regs->eax;
  syscall handler = syscall_handlers[id];
  if (handler)
    handler(regs);
}

void write_handler(struct registers *regs)
{
  char *buf = (char *)regs->ebx;
  size_t length = regs->ecx;
  regs->eax = write(buf, length);
}

void getkey_handler(struct registers *regs)
{
  regs->eax = getkey();
}

void gettick_handler(struct registers *regs)
{
  regs->eax = gettick();
}

void open_handler(struct registers *regs)
{
  regs->eax = open((char *)regs->eax, regs->ebx);
}

void read_handler(struct registers *regs)
{
  regs->eax = read(regs->eax, (void *)regs->ebx, regs->ecx);
}

void seek_handler(struct registers *regs)
{
  regs->eax = seek(regs->eax, regs->ebx, regs->ecx);
}

void close_handler(struct registers *regs)
{
  regs->eax = close(regs->eax);
}

static inline u32 syscall0(int syscall_nb)
{
	u32 res;

	asm volatile ("int $0x80" : "=a"(res) : "a"(syscall_nb));

	return res;
}

static inline u32 syscall1(int syscall_nb, u32 ebx)
{
	u32 res;

	asm volatile ("int $0x80" : "=a"(res) : "a"(syscall_nb), "b"(ebx));

	return res;
}

static inline u32 syscall2(int syscall_nb, u32 ebx, u32 ecx)
{
	u32 res;

	asm volatile ("int $0x80" : "=a"(res) : "a"(syscall_nb), "b"(ebx), "c"(ecx));

	return res;
}

static inline u32 syscall3(int syscall_nb, u32 ebx, u32 ecx, u32 edx)
{
	u32 res;

	asm volatile ("int $0x80" : "=a"(res) : "a"(syscall_nb), "b"(ebx), "c"(ecx), "d"(edx));

	return res;
}
