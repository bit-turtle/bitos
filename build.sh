#!/bin/bash

checkpkg() {
	if [ -x "$(command -v $1)" ]; then
		echo "	- found $1"
	else
		echo "	- $1 not found"
		echo "Required Package Not Found, Aborting!"
		exit
	fi
}

rm bin/*	# Reset Binary Dir
echo "Compiling BitOS..."
checkpkg "as"
checkpkg "gcc"
checkpkg "ld"
as --march=i386 --32 src/kernel.s -o bin/kernels.o
if [ $? != 0 ]; then
	echo "Error Compiling Assembly!"
	echo "Aborting..."
	exit
fi
gcc -m32 -ffreestanding -fno-builtin -nostdlib -nodefaultlibs -fno-stack-protector -c src/kernel.c -o bin/kernelc.o
if [ $? != 0 ]; then
	echo "Error Compiling C!"
	echo "Aborting..."
	exit
fi
ld -nostdlib -m elf_i386 -T src/linker.ld -o bin/kernel.bin bin/kernels.o bin/kernelc.o
if [ $? != 0 ]; then
	echo "Error Linking BitOS"
	echo "Aborting..."
	exit
fi
echo "Creating ISO..."
checkpkg "grub-mkrescue"
checkpkg "xorriso"
checkpkg "mformat"
cp bin/kernel.bin ./iso/boot/bitos.bin
rm output/*	# Reset output dir
grub-mkrescue -o output/bitos.iso ./iso
echo "Done!" $(realpath output/bitos.iso)
