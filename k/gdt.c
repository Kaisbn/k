#include "multiboot.h"
#include <k/gdt.h>

struct gdt_d gdt[5];
struct gdt_r gdtr;

static void
print_desc (const struct gdt_d *gdt)
{
  printf ("Base (31:24): %u\tG: %u\tD/B: %u\tL: %u\tAVL: %u\t\
		Limit (19:16): %u\t",
          gdt->base_hi, gdt->g, gdt->db, gdt->l, gdt->avl, gdt->limit_hi);
  printf ("P: %u\tDPL: %u\tS: %u\tType: %u\tBase (23:16): %u\n\t", gdt->p,
          gdt->dpl, gdt->s, gdt->type, gdt->base_mid);
  printf ("Base (15:00): %u\tLimit (15:00): %u\n", gdt->base_lo,
          gdt->limit_lo);
}

static void
print_gdt (void)
{
  printf ("GDT:\n\tbase: %u\n\tlimit: %u\n", gdtr.base, gdtr.limit);
  printf ("Descriptors:\n");
  printf (" NULL:\n\t");
  print_desc (&gdt[0]);
  printf (" Kernel Code:\n\t");
  print_desc (&gdt[1]);
  printf (" Kernel Data:\n\t");
  print_desc (&gdt[2]);
  printf (" Userland Code:\n\t");
  print_desc (&gdt[3]);
  printf (" Userland Data:\n\t");
  print_desc (&gdt[4]);
}

static void
init_desc (u32 base, u32 limit, u8 access, u8 flags, struct gdt_d *gdt)
{
  gdt->base_lo = (base & 0xffff);
  gdt->limit_lo = (limit & 0xffff);
  gdt->base_mid = (base & 0xff0000) >> 16;
  gdt->g = (flags >> 3) & 0x1;
  gdt->db = (flags >> 2) & 0x1;
  gdt->l = (flags >> 1) & 0x1;
  gdt->avl = flags & 0x1;
  gdt->limit_hi = (limit & 0xf0000) >> 16;
  gdt->p = (access >> 7) & 0x1;
  gdt->dpl = (access >> 5) & 0x3;
  gdt->s = (access >> 4) & 0x1;
  gdt->type = access & 0xf;
  gdt->base_hi = (base & 0xff000000) >> 24;
}

static void
load_gdtr (void)
{
  asm volatile("lgdt %0\n\t" : : "m"(gdtr) : "memory");
}

static void
enable_prot (void)
{
  asm volatile("movl %cr0, %eax\n\t"
               "movl $0x1, %ebx\n\t"
               "or %ebx, %eax\n\t"
               "movl %eax, %cr0\n\t"); // Switch PE bit if not set
}

static void
reload_segments (void)
{
  asm volatile("movw $0x10, %ax\n\t"
               "movw %ax, %ds\n\t"
               "movw %ax, %es\n\t"
               "movw %ax, %fs\n\t"
               "movw %ax, %gs\n\t"
               "movw %ax, %ss\n\t");

  asm volatile("pushl $0x08\n\t"
               "pushl $1f\n\t"
               "lret\n\t"
               "1:\n\t");
}

void
init_gdt (void)
{
  gdtr.base = &gdt;
  gdtr.limit = (sizeof (struct gdt_d) * 5) - 1;

  init_desc (0x0, 0x0, 0x0, 0x0, &gdt[0]); // NULL SEGMENT

  init_desc (0x0, 0xFFFFFFFF, P_SET | S_SET | TYPE_RX, G_SET | DB_SET,
             &gdt[1]); // Kernel Code Segment

  init_desc (0x0, 0xFFFFFFFF, P_SET | S_SET | TYPE_RW, G_SET | DB_SET,
             &gdt[2]); // Kernel Data Segment

  init_desc (0x0, 0xFFFFFFFF, P_SET | DPL_USER | S_SET | TYPE_RX,
             G_SET | DB_SET, &gdt[3]); // Userland Code Segment

  init_desc (0x0, 0xFFFFFFFF, P_SET | DPL_USER | S_SET | TYPE_RW,
             G_SET | DB_SET, &gdt[4]); // Userland Data Segment

  enable_prot ();
  load_gdtr ();
  reload_segments ();
}
