all:
	gcc -c src/terminal.c  -o obj/terminal.o  -std=c99 -O3
	gcc -c src/kernel.c    -o obj/kernel.o    -std=c99 -O3
	gcc -c src/common.c    -o obj/common.o    -std=c99 -O3
	gcc -c src/gdt.c       -o obj/gdt.o       -std=c99 -O3
	gcc -c src/idt.c       -o obj/idtc.o      -std=c99 -O3
	nasm   src/multiboot.s -o obj/multiboot.o -f elf
	nasm   src/idt.s       -o obj/idts.o      -f elf
	
	i686-elf-ld -T src/linker.ld -o bin/os.bin obj/multiboot.o obj/terminal.o obj/kernel.o obj/common.o obj/gdt.o obj/idtc.o \
						obj/idts.o
	ls -lh bin/os.bin
	cp bin/os.bin cdroot/boot/kernel
	mkisofs -o output.iso -b boot/isolinux/isolinux.bin -c boot/isolinux/boot.cat -no-emul-boot -boot-load-size 4 -boot-info-table cdroot
