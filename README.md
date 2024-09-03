# Bit OS
A Simple Operating System written in C.

*Currently Only Supports Computers That Use BIOS (Requires VGA 80x25 Text Mode)*

## Building, Writing and Testing
There are a few included shell scripts (That work on Linux) to make it easy to build the OS and write it to a flash drive.
1. `build.sh` Builds the OS and creates the ISO (Requires `binutils`, `gcc`, `grub`, and `xorriso`)
2. `write.sh` Uses `dd` to write the ISO to /dev/sda (Make sure that is the correct drive)
3. `test.sh` Uses `qemu` to emulate the OS booting from the ISO
