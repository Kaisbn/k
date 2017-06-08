#include "k/filesystem.h"

void *get_blk(int offset)
{
  return (char *)super + offset * KFS_BLK_SZ;
}

void init_kfs(multiboot_info_t *info)
{
  super = (void *)((module_t*)info->mods_addr)[0].mod_start;
  if (super->magic != KFS_MAGIC)
    return;
  unsigned int checksum = kfs_checksum(super, sizeof(struct kfs_superblock)
      - sizeof(u32));
  if (checksum != super->cksum)
    return;
}

int open(const char *pathname, int flags)
{
  if (!pathname)
    return -1;
  struct kfs_inode *ino = get_blk(super->inode_idx);
  u32 size = sizeof(struct kfs_inode) - sizeof(u32);
  u32 checksum = kfs_checksum(ino, size);
  while (checksum == ino->cksum && strcmp(ino->filename, pathname))
  {
    ino = get_blk(ino->next_inode);
    checksum = kfs_checksum(ino, size);
  }
  if (checksum != ino->cksum)
    return -1;
  table[ino->idx] = 0;
  return ino->idx;
}

ssize_t read(int fd, void *buf, size_t count)
{
  if (fd < 0 || table[fd] == -1)
    return -1;
  struct kfs_inode *ino = get_blk(fd);
  size_t read = 0;
  int off = table[fd];
  for (u32 i = 0; i < ino->d_blk_cnt; ++i)
  {
    if (count > read)
    {
      struct kfs_block *blk = get_blk(ino->d_blks[i]);
      for (; count != 0; --count, ++read, ++buf, ++off)
        memcpy(buf, &blk->data[off], sizeof(u8));
    }
    else
      break;
  }
  for (u32 i = 0; i < ino->i_blk_cnt; ++i)
  {
    if (count > read)
    {
      struct kfs_iblock *iblk = get_blk(ino->i_blks[i]);
      for (u32 j = 0; j < iblk->blk_cnt; ++j)
      {
        if (count > read)
        {
          struct kfs_block *blk = get_blk(ino->d_blks[i]);
          for (; count != 0; --count, ++read, ++buf, ++off)
            memcpy(buf, &blk->data[off], sizeof(u8));
        }
        else
          break;
      }
    }
    else
      break;
  }
  table[fd] = off;
  return read;
}

int close(int fd)
{
  if (fd < 0 || table[fd] == -1)
    return -1;
  table[fd] = -1;
  return 0;
}
