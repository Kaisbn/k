#include "k/keyboard.h"
#include "io.h"

int getkey(void)
{
  u8 scan = inb(0x60);
  if (scan & 0x80)
    return -1;
  else
    return scan;
}

void keyboard_handler(struct registers regs)
{
  int scan = getkey();
  if (scan != -1)
    printf("Keyboard scancode: %d\n", scan);
}
