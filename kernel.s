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

start:
	cli	# Remove interrupts
	call kernel	# Call Kernel defined in kernel.c
	hlt	# Stop CPU if Kernel ends
