#ifndef _K_BINARY_H_
#define _K_BINARY_H_

#include "../multiboot.h"
#include "gdt.h"

extern struct gdt_d gdt[5];

void load(multiboot_info_t *info);

#endif /* !_K_BINARY_H_ */
