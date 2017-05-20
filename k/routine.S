.global isr0
.global isr1
.global isr2
.global isr3
.global isr4
.global isr5
.global isr6
.global isr7
.global isr8
.global isr9
.global isr10
.global isr11
.global isr12
.global isr13
.global isr14
.global isr15
.global isr16
.global isr17
.global isr18
.global isr19
.global isr20
.global isr21
.global isr22
.global isr23
.global isr24
.global isr25
.global isr26
.global isr27
.global isr28
.global isr29
.global isr30
.global isr31

isr0:
pushl 0
pushl 0
jmp isr_handler

isr1:
pushl 0
pushl 1
jmp isr_handler

isr2:
pushl 0
pushl 2
jmp isr_handler

isr3:
pushl 0
pushl 3
jmp isr_handler

isr4:
pushl 0
pushl 4
jmp isr_handler

isr5:
pushl 0
pushl 5
jmp isr_handler

isr6:
pushl 0
pushl 6
jmp isr_handler

isr7:
pushl 0
pushl 7
jmp isr_handler

isr8:
pushl 8
jmp isr_handler

isr9:
pushl 0
pushl 9
jmp isr_handler

isr10:
pushl 10
jmp isr_handler

isr11:
pushl 11
jmp isr_handler

isr12:
pushl 12
jmp isr_handler

isr13:
pushl 13
jmp isr_handler

isr14:
pushl 14
jmp isr_handler

isr15:
pushl 0
pushl 15
jmp isr_handler

isr16:
pushl 0
pushl 16
jmp isr_handler

isr17:
pushl 0
pushl 17
jmp isr_handler

isr18:
pushl 0
pushl 18
jmp isr_handler

isr19:
pushl 0
pushl 19
jmp isr_handler

isr20:
pushl 0
pushl 20
jmp isr_handler

isr21:
pushl 0
pushl 21
jmp isr_handler

isr22:
pushl 0
pushl 22
jmp isr_handler

isr23:
pushl 0
pushl 23
jmp isr_handler

isr24:
pushl 0
pushl 24
jmp isr_handler

isr25:
pushl 0
pushl 25
jmp isr_handler

isr26:
pushl 0
pushl 26
jmp isr_handler

isr27:
pushl 0
pushl 27
jmp isr_handler

isr28:
pushl 0
pushl 28
jmp isr_handler

isr29:
pushl 0
pushl 29
jmp isr_handler

isr30:
pushl 0
pushl 30
jmp isr_handler

isr31:
pushl 0
pushl 31
jmp isr_handler

.extern c_handler

isr_handler:
  pusha
  pushw %ds
  pushw %es
  pushw %fs
  pushw %gs

  movw $0x10, %ax
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs
  movl %esp, %eax

  call c_handler 

  popl %eax
  popw %gs
  popw %fs
  popw %es
  popw %ds

  popa
  addl $8, %esp
  iret
