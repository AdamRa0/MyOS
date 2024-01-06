#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "types.h"
#include "port.h"
#include "gdt.h"

class InterruptsManager
{
protected:
    struct GateDescriptor
    {
        uint16_t offest_lo;
        uint16_t gdt_code_segment_selector;
        uint8_t reserved;
        uint8_t access;
        uint16_t offest_hi;
    } __attribute__((packed));

    static GateDescriptor interrupt_descriptor_table[256];
    static void SetInterruptDescriptorTableEntry(
        uint8_t interrupt_number,
        uint16_t code_segment_selector_offeset,
        void (*offset)(),
        uint8_t DescriptorPrivilagesLevel,
        uint8_t GateType);

public:
    InterruptsManager(GlobalDescriptorTable *gdt);
    ~InterruptsManager();

    static uint32_t HandleInterrupt(uint8_t interrupt_number, uint32_t stack_pointer);

    static void IgnoreInterruptRequest0x00();
    static void HandleInterruptRequest0x00();
    static void HandleInterruptRequest0x01();
};

#endif