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

reboot:	# Reboot using a 8042 Reset
	mov $0x02, %al	# Loop while good
reboot_loop:
	mov %al, %ah
	and $0x64, %ah
	cmp $0x00, %ah
	jz reboot_done
	inb $0x64, %al
	jmp reboot_loop
reboot_done:
	mov $0xfe, %al
	outb %al, $0x64
	hlt

start:
	cli		# Disable Interrupts
	call kernel	# Call Kernel defined in kernel.c
	jmp reboot	# Reboot Computer after Kernel Finishes
