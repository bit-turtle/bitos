// Main Kernel File (kernel.c)

#include "vga.h"
#include "type.h"
#include "terminal.h"
#include "keyboard.h"
#include "buffer.h"

extern void kernel() {	//Kernel start
	clear();
	move_cursor(0,0);
	print("Welcome To BitOS! Write Something and Click [Enter]\n");
	
	disable_cursor();
	move_cursor(0,1);
	enable_cursor(0,15);
	struct buffer buf;
	bufinit(&buf);
	struct instringbit input;
	do {
		input = inputstring(&buf,'\n');
		if (input.changed) printc(input.c);
		update_cursor_position();
	}
	while (!input.done);

	print("\n\nYou Wrote:\n");
	print(&buf.data[0]);

	update_cursor_position();
}

