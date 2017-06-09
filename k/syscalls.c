#include "k/syscalls.h"
#include "k/kstd.h"

void init_syscall()
{
  init_desc(0x80, (u32)sys_int, 0x8, D_TRAP);
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
  regs->eax = open((char *)regs->ebx, regs->ecx);
}

void read_handler(struct registers *regs)
{
  regs->eax = read(regs->ebx, (void *)regs->ecx, regs->edx);
}

void seek_handler(struct registers *regs)
{
  regs->eax = seek(regs->ebx, regs->ecx, regs->edx);
}

void close_handler(struct registers *regs)
{
  regs->eax = close(regs->ebx);
}

void setvideo_handler(struct registers *regs)
{
  regs->eax = setvideo(regs->ebx);
}

void swap_frontbuffer_handler(struct registers *regs)
{
  swap_frontbuffer(regs->ebx);
  regs->eax = 0;
}

void sbrk_handler(struct registers *regs)
{
  regs->eax = sbrk(regs->ebx);
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

int sys_setvideo(int mode)
{
  return (int)(syscall1(SYSCALL_SETVIDEO, mode));
}
