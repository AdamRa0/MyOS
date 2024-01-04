#include "types.h"
#include "gdt.h"

typedef void (*constructor)();

extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

void cout(char *str)
{
    static uint16_t *video_memory = (uint16_t *)0xb8000;
    static uint8_t x = 0, y = 0; // Create cursor

    for (int i = 0; str[i] != '\0'; i++)
    {

        switch (str[i])
        {
        case '\n':
            y ++;
            x = 0;
            break;

        default:
            // Calculate position of cursor in memory and write character to that position
            video_memory[80 * y + x] = (video_memory[80 * y + x] & 0XFF00) | str[i];

            // Move cursor to the right
            x++;
        }

        // If end of screen width, move to new line
        if (x >= 80)
        {
            y++;
            x = 0;
        }

        // If screen is full, clear screen
        if (y >= 25)
        {
            for (y = 0; y < 25; y++)
            {
                for (x = 0; x < 80; x++)
                {
                    video_memory[80 * y + x] = (video_memory[80 * y + x] & 0XFF00) | ' ';
                }
            }

            x = 0;
            y = 0;
        }
    }
}

extern "C" void KernelMain(void *multiboot_structure, uint32_t magic_number)
{

    cout((char *)"Bare Metal OS\n");
    cout((char *)"Bare Metal OS");

    GlobalDescriptorTable gdt;

    while (true)
        ;
}

extern "C" void CallConstructors()
{
    for (constructor *i = &start_ctors; i != &end_ctors; i++)
    {
        (*i)();
    }
}