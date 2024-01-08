#include "interrupts.h"
#include "types.h"

void cout(char *str);

uint32_t InterruptsManager::HandleInterrupt(uint8_t interrupt_number, uint32_t stack_pointer)
{

    cout((char *)"Interrupt");

    return stack_pointer;
}

InterruptsManager::GateDescriptor InterruptsManager::interrupt_descriptor_table[256];

void InterruptsManager::SetInterruptDescriptorTableEntry(
    uint8_t interrupt_number,
    uint16_t code_segment_selector_offeset,
    void (*offset)(),
    uint8_t DescriptorPrivilagesLevel,
    uint8_t GateType)
{
    const uint8_t IDT_DESC_PRESENT = 0x80;

    interrupt_descriptor_table[interrupt_number].offest_lo = ((uint32_t)offset) & 0xFFF;
    interrupt_descriptor_table[interrupt_number].offest_hi = (((uint32_t)offset) >> 16) & 0xFFF;
    interrupt_descriptor_table[interrupt_number].gdt_code_segment_selector = code_segment_selector_offeset;
    interrupt_descriptor_table[interrupt_number].access = IDT_DESC_PRESENT | GateType | ((DescriptorPrivilagesLevel & 3) << 5);
    interrupt_descriptor_table[interrupt_number].reserved = 0;
}

InterruptsManager::InterruptsManager(GlobalDescriptorTable *gdt)
{
    uint16_t CodeSegment = gdt->GetCodeSegment();
    const uint8_t IDT_INTERRUPT_GATE = 0xE;

    int i = 0;

    while (i < 256)
    {
        SetInterruptDescriptorTableEntry(i, CodeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPT_GATE);
        i++;
    }

    SetInterruptDescriptorTableEntry(0x20, CodeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x21, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);

    InterruptDescriptorTablePointer idt;
    idt.size = 256 * sizeof(GateDescriptor) - 1;
    idt.base = (uint32_t)interrupt_descriptor_table;
    asm volatile("lidt %0" : : "m" (idt));
}

InterruptsManager::~InterruptsManager() {}

void InterruptsManager::Activate()
{
    asm("sti");
}