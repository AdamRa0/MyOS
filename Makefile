# PARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno builtin -fno-rtti -fno-exceptions -fno-leading-underscore -fno-stack-protector
PARAMS = -m32 -fno-stack-protector
NASM_PARAMS = elf32
OBJECT_FILES = loader.o gdt.o port.o interrupts_nasm.o interrupts.o kernel.o
LD_PARAMS = -melf_i386

%.o: %.cpp
	g++ ${PARAMS} -o $@ -c $<

%.o: %.asm
	nasm -f ${NASM_PARAMS} -o $@ $<

os_kernel.bin: linker.ld ${OBJECT_FILES}
	ld ${LD_PARAMS} -T $< -o $@ ${OBJECT_FILES}

os_kernel.iso: os_kernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "My OS" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/os_kernel.bin' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

.PHONY: clean
clean:
	rm -f ${OBJECT_FILES} os_kernel.bin os_kernel.iso