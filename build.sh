as --march=i386 --32 kernel.s -o kernels.o
gcc -m32 -ffreestanding -fno-builtin -nostdlib -c kernel.c -o kernelc.o
ld -m elf_i386 -T linker.ld -o kernel kernels.o kernelc.o
rm kernels.o kernelc.o
