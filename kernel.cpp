#include "types.h"
#include "gdt.h"

typedef void (*constructor)();

extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

void cout(char* str)
{
    static uint16_t* video_memory = (uint16_t*) 0xb8000;

    for (int i = 0; str[i] != '\0'; i++)
    {
        video_memory[i] = (video_memory[i] & 0XFF00) | str[i];
    }
    
}

extern "C" void KernelMain(void *multiboot_structure, uint32_t magic_number)
{

    cout((char *)"Bare Metal OS");

    GlobalDescriptorTable gdt;

    while (true)
        ;
}

extern "C" void CallConstructors()
{
    for (constructor* i = &start_ctors; i != &end_ctors; i++)
    {
        (*i)();
    }
    
}