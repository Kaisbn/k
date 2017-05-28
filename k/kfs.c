#include "k/filesystem.h"
#include "k/kfs.h"

void init_kfs(multiboot_info_t *info)
{
  struct kfs_superblock *super = (void *)((module_t*)info->mods_addr)[0].mod_start; 
  if (super->magic != KFS_MAGIC)
    return;
  unsigned int checksum = kfs_checksum(super, 4096);
  if (checksum != super->cksum)
    return;
  int table[super->inode_cnt];
  memset(&table, 0, sizeof(int) * super->inode_cnt);
  fds = (int*)&table;
  printf("%d\n", fds);
}

int open(const char *pathname, int flags)
{
  if (!pathname)
    return -1;
  return 0;
}
