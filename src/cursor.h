// Cursor.c

//Functions to control the hardware cursor

#include "type.h"
#include "io.h"
#include "vga.h"

#ifndef CURSOR_H
#define CURSOR_H

byte cursorx = 0;
byte cursory = 0;

void enable_cursor(byte cstart, byte cend) {
	outb(0x3d4, 0x0a);
	outb(0x3d5, (inb(0x3d5) & 0xc0) | cstart);
	outb(0x3d4, 0x0b);
	outb(0x3d5, (inb(0x3d5) & 0xe0) | cend);
}

void disable_cursor() {
	outb(0x3d4,0x0a);
	outb(0x3d5, 0x20);
}

void move_cursor(byte x, byte y) {
	cursorx = x;
	cursory = y;
}

void update_cursor_position() {
	word pos = cursory * VGA_WIDTH + cursorx;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (byte) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (byte) ((pos >> 8) & 0xFF));
}

#endif
