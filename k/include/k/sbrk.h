#ifndef K_SBRK_H_
#define K_SBRK_H_

#include "k/kstd.h"
#include "../multiboot.h"

u32 brk = 0;
memory_map_t *map;

void init_brk(multiboot_info_t *info);
void *sbrk(ssize_t increment);

#endif /* !K_SBRK_H_ */
