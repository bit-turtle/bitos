// Main Kernel File (kernel.c)

#include "vga.h"
#include "type.h"
#include "cursor.h"
#include "terminal.h"
#include "keyboard.h"
#include "buffer.h"
#include "shell.h"

extern void kernel() {	//Kernel start
	clear();
	move_cursor(0,0);
	print("Welcome To Bit OS!\n");
	move_cursor(0,1);
	enable_cursor(0,15);
	shell();	// Start Shell
	update_cursor_position();
}

