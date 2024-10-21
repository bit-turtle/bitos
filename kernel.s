# C Kernel Caller
.code32

.section .text
multiboot2_start:
	# Multiboot 2
	.align 4
	.long 0xe85250d6		# Multiboot magic
	.long 0x00			# Architecture
	.long (multiboot2_end - multiboot2_start)			# Header Length
	.long - (0xe85250d6 + 0x00 + (multiboot2_end - multiboot2_start))	# Checksum (magic + architecture + length + checksum) = 0
multiboot2_end:

multiboot2_return:
	.skip 4 * 13

.globl start
.extern kernel

start:
	cli		# Disable Interrupts
	call kernel	# Call Kernel defined in kernel.c
	hlt		# Halt CPU after Kernel is Done
