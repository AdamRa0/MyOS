#include "interrupts.h"
#include "types.h"

void cout(char* str);

uint32_t InterruptsManager::HandleInterrupt(uint8_t interrupt_number, uint32_t stack_pointer)
{

    cout((char*) "Interrupt");

    return stack_pointer;
}