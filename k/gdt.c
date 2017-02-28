#include <k/gdt.h>

void init_desc(u32 base, u32 limit, u8 access, u8 flags, struct gdt_d *gdt)
{
  gdt->base_lo = (base & 0xffff);
  gdt->limit_lo = (limit & 0xffff);
  gdt->base_mid = (base & 0xff0000) >> 16;
  gdt->access = access;
  gdt->limit_hi = (limit & 0xf0000) >> 16;
  gdt->flags = flags;
  gdt->base_hi = (base & 0xff000000) >> 24;
}

static inline void load_gdtr(struct gdt_r gdtr)
{
  asm volatile("lgdt %0\n\t"
              :
              : "m"(gdtr)
              : "memory");
}

void init_gdt()
{
  struct gdt_r gdtr;
  gdtr.base = 0x0;
  gdtr.limit = sizeof(gdtr) - 1;

  struct gdt_d gdt[6];
// Flags : G = 1, D/B = 1 , L = 0, AVL = 1

  init_desc(0x0, 0x0, 0x0, 0x0, &gdt[0]); // NULL SEGMENT

  init_desc(0x0, gdtr.limit, 0x9A, 0xD, &gdt[1]); // Kernel Code Segment
// Access: P = 1, DPL = 0, S = 1 (code or data), Type = 0xA (code r-x)

  init_desc(0x0, gdtr.limit, 0x92, 0xD, &gdt[2]); // Kernel Data Segment
// Access: P = 1, DPL = 0, S = 1 (code or data), Type = 0x2 (data rw-)

  init_desc(0x0, gdtr.limit, 0xFA, 0xD, &gdt[3]); // Userland Code Segment
// Access: P = 1, DPL = 3, S = 1 (code or data), Type = 0xA (code r-x)

  init_desc(0x0, gdtr.limit, 0xF2, 0xD, &gdt[4]); // Userland Data Segment
// Access: P = 1, DPL = 3, S = 1 (code or data), Type = 0x2 (code rw-)

  //TODO: tss
  load_gdtr(gdtr);
}
