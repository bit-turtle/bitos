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

echo "Compiling BitOS..."
checkpkg "as"
checkpkg "gcc"
checkpkg "ld"
as --march=i386 --32 kernel.s -o kernels.o
if [ $? != 0 ]; then
	echo "Error Compiling Assembly!"
	echo "Aborting..."
	exit
fi
gcc -m32 -ffreestanding -fno-builtin -nostdlib -nodefaultlibs -fno-stack-protector -c kernel.c -o kernelc.o
if [ $? != 0 ]; then
	echo "Error Compiling C!"
	echo "Aborting..."
	exit
fi
ld -nostdlib -m elf_i386 -T linker.ld -o kernel.bin kernels.o kernelc.o
if [ $? != 0 ]; then
	echo "Error Linking BitOS"
	echo "Aborting..."
	exit
fi
rm kernels.o kernelc.o
echo "Creating ISO..."
checkpkg "grub-mkrescue"
checkpkg "xorriso"
checkpkg "mformat"
cp kernel.bin ./iso/boot/kernel.bin
grub-mkrescue -o bitos.iso ./iso
echo "Done!"
