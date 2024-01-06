IRQ_BASE equ 0x20

%macro HandleInterruptRequest 1
    global _ZN17InterruptsManager16HandleException%1()Ev

    section .text
        MOVB [interrupt_number], $%1
        JMP int_bottom
%endmacro

%macro HandleInterruptRequest 1
    global _ZN17InterruptsManager26HandleInterruptRequest%1()Ev

    section .text
        MOVB [interrupt_number], $%1 + IRQ_BASE
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
    PUSHL ds
    PUSHL es
    PUSHL fs
    PUSHL gs


    PUSH esp
    PUSH [interrupt_number]
    CALL _ZN17InterruptsManager15HandleInterruptEhj
    MOV esp, eax

    POF gs
    POP fs
    POP es
    POP ds
    POPA

    IRET    
