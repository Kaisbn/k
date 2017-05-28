.global irq0
.global irq1
.global irq2
.global irq3
.global irq4
.global irq5
.global irq6
.global irq7
.global irq8
.global irq9
.global irq10
.global irq11
.global irq12
.global irq13
.global irq14
.global irq15
.global irq16
.global irq17
.global irq18
.global irq19
.global irq20
.global irq21
.global irq22
.global irq23
.global irq24
.global irq25
.global irq26
.global irq27
.global irq28
.global irq29
.global irq30
.global irq31

irq0:
cli
pushl $0
pushl $32
jmp irq_handler

irq1:
cli
pushl $0
pushl $33
jmp irq_handler

irq2:
cli
pushl $0
pushl $34
jmp irq_handler

irq3:
cli
pushl $0
pushl $35
jmp irq_handler

irq4:
cli
pushl $0
pushl $36
jmp irq_handler

irq5:
cli
pushl $0
pushl $37
jmp irq_handler

irq6:
cli
pushl $0
pushl $38
jmp irq_handler

irq7:
cli
pushl $0
pushl $39
jmp irq_handler

irq8:
cli
pushl $0
pushl $40
jmp irq_handler

irq9:
cli
pushl $0
pushl $41
jmp irq_handler

irq10:
cli
pushl $0
pushl $42
jmp irq_handler

irq11:
cli
pushl $0
pushl $43
jmp irq_handler

irq12:
cli
pushl $0
pushl $44
jmp irq_handler

irq13:
cli
pushl $0
pushl $45
jmp irq_handler

irq14:
cli
pushl $0
pushl $46
jmp irq_handler

irq15:
cli
pushl $0
pushl $47
jmp irq_handler

.extern c_irq_handler

irq_handler:
  pusha
  movw %ds, %ax
  pushl %eax
  movw $0x10, %ax
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs

  call c_irq_handler

  popl %ebx
  movw %bx, %ds
  movw %bx, %es
  movw %bx, %fs
  movw %bx, %gs
  popa
  addl $8, %esp
  sti
  iret
