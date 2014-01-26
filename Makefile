all:
	rm -r obj; mkdir obj{,/kernel{,/desctables}}
	nasm      src/kernel/multiboot.s      -o obj/kernel/multiboot.s.o      -f elf
	gcc -g -c src/kernel/terminal.c       -o obj/kernel/terminal.c.o       -std=c99 -O3
	gcc -g -c src/kernel/kernel.c         -o obj/kernel/kernel.c.o         -std=c99 -O3
	gcc -g -c src/kernel/common.c         -o obj/kernel/common.c.o         -std=c99 -O3
	nasm      src/kernel/common.s         -o obj/kernel/common.s.o         -f elf
	gcc -g -c src/kernel/desctables/gdt.c -o obj/kernel/desctables/gdt.c.o -std=c99 -O3
	gcc -g -c src/kernel/desctables/idt.c -o obj/kernel/desctables/idt.c.o -std=c99 -O3
	nasm      src/kernel/desctables/idt.s -o obj/kernel/desctables/idt.s.o -f elf
	i686-elf-ld -T linker.ld -nostdlib -nodefaultslibs -o bin/os obj/kernel/{,desctables/}*.o
	ls -lh bin/os
	cp bin/os cdroot/boot/kernel
	mkisofs -o output.iso -b boot/isolinux/isolinux.bin -c boot/isolinux/boot.cat -no-emul-boot -boot-load-size 4 -boot-info-table cdroot
