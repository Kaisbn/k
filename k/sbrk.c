#include "k/sbrk.h"

void init_brk(multiboot_info_t *info)
{
  map = (memory_map_t *)info->mmap_addr;
  u32 mod_end = ((module_t *)info->mods_addr)[0].mod_end;
  while ((u32)map < info->mmap_addr + info->mmap_length &&
      (map->base_addr_low + map->length_low < mod_end))
    map = (memory_map_t *)((unsigned int) map + map->size + sizeof(map->size));
  brk = mod_end > map->base_addr_low ? mod_end : map->base_addr_low;
}

void *sbrk(ssize_t increment)
{
  void *ptr = (void *)brk;
  if (brk + increment < brk + map->length_low)
    brk += increment;
  else
    return (void *)-1;
  return ptr;
}
