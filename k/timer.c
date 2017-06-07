#include "k/timer.h"
#include "io.h"

unsigned long gettick(void)
{
  return counter;
}

void init_timer(void)
{
  u32 internal = 1193182;
  u32 divider = internal / 100;
  u8 lo = divider & 0xFF;
  u8 hi = divider >> 8;
  outb(PIT, MODE2);
  outb(DATA0, lo);
  outb(DATA0, hi);

}

void timer_handler(struct registers regs)
{
  counter++;
  //if (counter % 100 == 0)
    //printf("%d seconds\n", counter / 100);
}
