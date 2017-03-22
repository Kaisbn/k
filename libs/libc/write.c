#include <string.h>
#include <io.h>

#define COM1 0x3f8

void init_serial(unsigned int port)
{
	outb(port + 1, 0x03);//Enable THR Empty Interrupt (000000010)
	outb(port + 3, 0x80); //Set DLAB
	outb(port    , 0x03); //Latch High
	outb(port + 1, 0x00); //Latch Low
	outb(port + 3, 0x03); //Set baudrate to 115200/38400 = 3
	outb(port + 2, 0xc7);//Enable FIFO, CR, CT, 14bytes (11000111)
}

int write(const char *str, size_t length)
{
	if (!str)
		return -1;
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
