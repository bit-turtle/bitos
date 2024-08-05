// Main Kernel File (kernel.c)

#include "type.h"
#include "terminal.h"
#include "keyboard.h"
#include "buffer.h"

extern void kernel() {	//Kernel start
	disable_cursor();
	move_cursor(0,0);
	clear();
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

  print(buf.data);
}

