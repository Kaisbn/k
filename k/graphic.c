#include "k/kstd.h"
#include "k/graphic.h"

int setvideo(int mode)
{
  if (mode == VIDEO_TEXT)
    libvga_switch_mode3h();
  else if (mode == VIDEO_GRAPHIC)
    libvga_switch_mode13h();
  else
    return -1;
  return 0;
}

void swap_frontbuffer(const void *buffer)
{
  char *buf = libvga_get_framebuffer();
  if (!buf || !buffer)
    return;
  memcpy(buf, buffer, strlen(buffer));
}
