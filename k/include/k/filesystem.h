#ifndef K_FILESYSTEM_H_
#define K_FILESYSTEM_H_

#include "k/kstd.h"
#include "k/kfs.h"
#include "../multiboot.h"

int table[256] = {-1};
struct kfs_superblock *super = NULL;

void init_kfs(multiboot_info_t *info);

int open(const char *pathname, int flags);
ssize_t read(int fd, void *buf, size_t count);
off_t seek(int fd, off_t offset, int whence);
int close(int fd);

#endif /* !K_FILESYSTEM_H_ */
