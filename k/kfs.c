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
  if (!pathname || flags != O_RDONLY)
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
    if (count > 0)
    {
      struct kfs_block blk = *((struct kfs_block *)get_blk(ino->d_blks[i]));
      u32 cksum = blk.cksum;
      blk.cksum = 0;
      if (kfs_checksum(&blk, sizeof(struct kfs_block)) != cksum)
        return -1;
      for (int i = table[fd]; count != 0 && i < KFS_BLK_DATA_SZ;
          --count, ++read, ++off, ++i)
        memcpy(buf++, &blk.data[i], sizeof(u8));
    }
    else
      break;
  }
  for (u32 i = 0; i < ino->i_blk_cnt; ++i)
  {
    if (count > 0)
    {
      struct kfs_iblock *iblk = get_blk(ino->i_blks[i]);
      for (u32 j = 0; j < iblk->blk_cnt; ++j)
      {
        if (count > 0)
        {
          struct kfs_block blk = *((struct kfs_block *)get_blk(iblk->blks[j]));
          u32 cksum = blk.cksum;
          blk.cksum = 0;
          if (kfs_checksum(&blk, sizeof(struct kfs_block)) != cksum)
            return -1;
          int i = ino->d_blk_cnt == 0 ? table[fd] : 0;
          for (; count != 0 && i < KFS_BLK_DATA_SZ;
              --count, ++read, ++off, ++i)
            memcpy(buf++, &blk.data[i], sizeof(u8));
        }
        else
          break;
      }
    }
    else
      break;
  }
  table[fd] = ++off;
  return read;
}

off_t seek(int fd, off_t offset, int whence)
{
  if (fd < 0 || table[fd] == -1)
    return -1;
  if (whence == SEEK_SET)
    table[fd] = offset;
  else if (whence == SEEK_CUR)
    table[fd] += offset;
  else if (whence == SEEK_END)
  {
    struct kfs_inode *ino = get_blk(fd);
    table[fd] = ino->file_sz + offset;
  }
  else
    return -1;
  return table[fd];
}

int close(int fd)
{
  if (fd < 0 || table[fd] == -1)
    return -1;
  table[fd] = -1;
  return 0;
}
