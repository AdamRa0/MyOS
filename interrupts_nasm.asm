IRQ_BASE equ 0x20

%macro HandleException 1
global _ZN17InterruptsManager16HandleException%1Ev
_ZN17InterruptsManager16HandleException%1Ev:
    MOV BYTE [interrupt_number], %1
    JMP int_bottom
%endmacro

%macro HandleInterruptRequest 1
global _ZN17InterruptsManager26HandleInterruptRequest%1Ev
_ZN17InterruptsManager26HandleInterruptRequest%1Ev:
    MOV BYTE [interrupt_number], %1 + IRQ_BASE
    JMP int_bottom
%endmacro

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01

section .data
    interrupt_number DB 0

section .text

extern _ZN17InterruptsManager15HandleInterruptEhj

int_bottom:

    PUSHA
    PUSH ds
    PUSH es
    PUSH fs
    PUSH gs


    PUSH esp
    MOVZX eax, BYTE [interrupt_number]
    PUSH eax
    CALL _ZN17InterruptsManager15HandleInterruptEhj
    MOV esp, eax

    POP gs
    POP fs
    POP es
    POP ds
    POPA

    IRET    
