extern KernelMain

section .data
    MAGIC_NUM equ 0x1badb002
    FLAGS equ (1<<0) | (1 << 1)
    CHECKSUM dd -(MAGIC_NUM + FLAGS)

section .text
    global loader

loader:
    MOV esp, kernel_stack_pointer
    PUSH eax
    PUSH ebx
    CALL KernelMain

_stop:
    CLI
    HLT
    JMP _stop

section .bss
    space resb 2*1024*1024

kernel_stack_pointer:
