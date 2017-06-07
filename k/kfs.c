#include "k/filesystem.h"

void init_kfs(multiboot_info_t *info)
{
  super = (void *)((module_t*)info->mods_addr)[0].mod_start;
  if (super->magic != KFS_MAGIC)
    return;
  unsigned int checksum = kfs_checksum(super, sizeof(struct kfs_superblock) - sizeof(u32));
  if (checksum != super->cksum)
    return;
  fds = malloc(sizeof(struct kfs_inode *) * super->inode_cnt);
}

int open(const char *pathname, int flags)
{
  if (!pathname)
    return -1;
  struct kfs_blk *blk = (struct kfs_blk *)((void *)super + super->inode_idx *
      KFS_BLK_SZ);
  struct kfs_inode ino = blk->ino;
  u32 size = sizeof(struct kfs_inode) - sizeof(u32);
  u32 checksum = kfs_checksum(&ino, size);
  while (checksum == ino.cksum && strcmp(blk->ino.filename, pathname))
  {
    blk = (struct kfs_blk *)((void *)super + blk->ino.next_inode * KFS_BLK_SZ);
    ino = blk->ino;
    checksum = kfs_checksum(&ino, size);
  }
  if (checksum != ino.cksum)
    return -1;
  struct kfs_inode* table = fds;
  int i = 3;
  for (; table->idx != 0; ++i, ++table)
    continue;
  *table = ino;
  return i;
}
