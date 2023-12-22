typedef void (*constructor)();

extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

void cout(char* str)
{
    unsigned short* video_memory = (unsigned short*) 0xb8000;

    for (int i = 0; str[i] != '\0'; i++)
    {
        video_memory[i] = str[i];
    }
    
}

extern "C" void KernelMain(void *multiboot_structure, unsigned int magic_number)
{

    cout((char *)"Bare Metal OS");

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