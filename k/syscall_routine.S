.global sys_int

sys_int:
  pushl $0
  pushl $0x80
  jmp syscall_handler

.extern c_syscall_handler

syscall_handler:
  pusha
  pushl %ds
  pushl %es
  pushl %fs
  pushl %gs

  movw $0x10, %ax
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs
  movl %esp, %eax
  pushl %eax

  call c_syscall_handler

  popl %ebx
  popl %ds
  popl %es
  popl %fs
  popl %gs

  popa
  addl $8, %esp
  iret
