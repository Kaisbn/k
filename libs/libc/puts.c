#include <string.h>
#include <k/types.h>

#define COM1 0x3f8

static inline void outb(u16 port, u8 val)
{
  asm volatile ("outb %0, %1\n\t"
               :
               :"a"(val), "d"(port));
}

static inline u8 inb(u16 port)
{
  u8 res;
  asm volatile("inb %1, %0\n\t"
              : "=&a"(res)
              : "d"(port));
  return res;
}

int write(const char *s, size_t nb)
{
  outb(COM1 + 1, 2);//Enable THR Empty Interrupt (000000010)
  outb(COM1 + 2, 0xc7);//Enable, CR, CT, 14bytes (11000111)
  outb(COM1 + 3, 0x80); //Set DLAB
  outb(COM1    , 3); //Latch High
  outb(COM1 + 1, 0); //Latch Low
  outb(COM1 + 3, 0x3); //Set baudrate to 115200/38400 = 3
  for (int i = 0; i < nb; i++)
    outb(COM1, s[i]);
  return nb;
}

int puts(const char *s)
{
	return write(s, strlen(s));
}
