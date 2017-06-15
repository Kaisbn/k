#include "k/binary.h"
#include "k/kstd.h"
#include "elf.h"

static int check_elf(Elf32_Ehdr hdr)
{
  if (hdr.e_ident[EI_MAG0] != ELFMAG0 ||
      hdr.e_ident[EI_MAG1] != ELFMAG1 ||
      hdr.e_ident[EI_MAG2] != ELFMAG2 ||
      hdr.e_ident[EI_MAG3] != ELFMAG3 ||
      hdr.e_ident[EI_CLASS] != ELFCLASS32 ||
      hdr.e_ident[EI_DATA] != ELFDATA2LSB ||
      hdr.e_ident[EI_VERSION] != EV_CURRENT)
    return 0;
  return 1;
}

int load_elf(multiboot_info_t *info)
{
  char *cmd = (char *)info->cmdline + 1;
  int fd = open(cmd, O_RDONLY);
  Elf32_Ehdr hdr;
  if (fd != -1)
  {
    read(fd, &hdr, sizeof(Elf32_Ehdr));
    if (!check_elf(hdr))
    {
      close(fd);
      return 0;
    }
    for (int i = 0; i < hdr.e_phnum; i++)
    {
      Elf32_Phdr phdr;
      seek(fd, hdr.e_phoff + i * hdr.e_phentsize, SEEK_SET);
      read(fd, &phdr, hdr.e_phentsize);
      if (phdr.p_type != PT_LOAD)
        continue;
      seek(fd, phdr.p_offset, SEEK_SET);
      if (PF_X & phdr.p_flags)
      {
        read(fd, (void *)&gdt[1] + phdr.p_vaddr, phdr.p_filesz);
        if (phdr.p_filesz < phdr.p_memsz)
          memset((void *)&gdt[1] + phdr.p_vaddr + phdr.p_filesz, 0,
              phdr.p_memsz - phdr.p_filesz);
      }
      else
      {
        read(fd, (void *)&gdt[2] + phdr.p_vaddr, phdr.p_filesz);
        if (phdr.p_filesz < phdr.p_memsz)
          memset((void *)&gdt[2] + phdr.p_vaddr + phdr.p_filesz, 0,
              phdr.p_memsz - phdr.p_filesz);
      }
    }
    close(fd);
    return hdr.e_entry;
  }
  return 0;
}
