# PARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno builtin -fno-rtti -fno-exceptions -fno-leading-underscore
PARAMS = -m32
NASM_PARAMS = elf32
OBJECT_FILES = loader.o kernel.o
LD_PARAMS = -melf_i386

%.o: %.cpp
	g++ ${PARAMS} -o $@ -c $<

%.o: %.asm
	nasm -f ${NASM_PARAMS} -o $@ $<

os_kernel.bin: linker.ld ${OBJECT_FILES}
	ld ${LD_PARAMS} -T $< -o $@ ${OBJECT_FILES}

install: os_kernel.bin
	sudo cp $< /boot/os_kernel.bin