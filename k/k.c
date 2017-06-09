/*
 * Copyright (c) LSE
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY LSE AS IS AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL LSE BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <k/kstd.h>

#include "multiboot.h"

#define COM1 0x3f8

void k_main(unsigned long magic, multiboot_info_t *info)
{
	(void)magic;
	(void)info;

	char star[4] = "|/-\\";
	char *fb = (void *)0xb8000;
  init_serial(COM1);
  init_kfs(info);
  int fd = open("bush.bmp", O_RDONLY);
  printf("FD: %d\n", fd);
  char buf[60000] = {
    0
  };
  seek(fd, 1, SEEK_CUR);
  ssize_t rd = read(fd, &buf, 10);
  printf("Read: %d\n", rd);
  printf("buffer: %s\n", buf);
  int cl = close(fd);
  printf("Closed: %d\n", cl);
  init_gdt();
  init_idt();
  init_syscall();

  sys_setvideo(VIDEO_GRAPHIC);
	for (unsigned i = 0; ; ) {
		*fb = star[i++ % 4];
	}

	for (;;)
		asm volatile ("hlt");
}
