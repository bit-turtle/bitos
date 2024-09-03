# C Kernel Caller
.code32

.section .text
	# Multiboot
	.align 4
	.long 0x1badb002	# The magic GRUB number
	.long 0x00	# Flags
	.long - (0x1badb002 + 0x00) # Checksum (magic + flags - checksum) = 0

.globl start
.extern kernel
.extern getidt
.extern getgdt

start:
	cli	# Disable interrupts
	call getgdt	# Get Pointer To Global Descriptor Table
	lgdt (%eax)	# Load Global Descriptor Table
	call getidt	# Get Pointer To Interrupt Descriptor Table
	lidt (%eax)	# Load Interrupt Descriptor Table
	call kernel	# Call Kernel defined in kernel.c
	hlt		# Halt CPU after Kernel is Done
