#include <string.h>

#define COM1 0x3f8

static void outb(unsigned short port, unsigned char val)
{
asm volatile ("outb %0, %1\n\t"
		:
		: "a"(val), "d"(port));
}

static unsigned char inb(unsigned short port)
{
unsigned char res;
asm volatile("inb %1, %0\n\t"
		: "=&a"(res)
		: "d"(port));
return res;
}

int write(const char *str, size_t length)
{
if (!str)
	return -1;
outb(COM1 + 1, 0x03);//Enable THR Empty Interrupt (000000010)
outb(COM1 + 3, 0x80); //Set DLAB
outb(COM1, 0x03); //Latch High
outb(COM1 + 1, 0x00); //Latch Low
outb(COM1 + 3, 0x03); //Set baudrate to 115200/38400 = 3
outb(COM1 + 2, 0xc7);//Enable FIFO, CR, CT, 14bytes (11000111)
length = strlen(str) < length ? strlen(str) : length;
for (size_t i = 0; i < length; i++) {
if (str[i] == '\n') {
outb(COM1, '\r');
outb(COM1, str[i]);
} else
outb(COM1, str[i]);
}
return length;
}
