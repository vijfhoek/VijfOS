all:
	fasm src/multiboot.asm obj/multiboot.o
	fasm src/terminal.asm obj/terminal.o
	fasm src/kernel.asm obj/kernel.o
	i686-elf-ld -T src/linker.ld -o bin/os.bin obj/multiboot.o obj/terminal.o obj/kernel.o
	cp bin/os.bin cdroot/boot/kernel
	mkisofs -o output.iso -b boot/isolinux/isolinux.bin -c boot/isolinux/boot.cat -no-emul-boot -boot-load-size 4 -boot-info-table cdroot
