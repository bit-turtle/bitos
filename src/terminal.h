// Terminal.h

#include "type.h"
#include "io.h"

#include "cursor.h"

#include "vga.h"

#ifndef TERMINAL_H
#define TERMINAL_H

#define TAB_LENGTH (byte) 8

char* terminal = (char*) 0xb8000;

enum Color { BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, GRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE };

struct Theme {
	enum Color color;
	enum Color background;
};

struct Theme currentTheme = { WHITE, BLACK };

byte encodeTheme() {
	return (currentTheme.background << 4) | currentTheme.color;
}

void wchar(char c, byte x, byte y) {
	terminal[x * 2 - 1 + y * VGA_WIDTH * 2] = encodeTheme();
	terminal[x * 2 + y * VGA_WIDTH * 2] = c;
}

void clearl(byte line) {
	for (byte i = 0; i < VGA_WIDTH; i++) wchar(' ',i,line);
}

void clear() {
	for (byte line = 0; line < VGA_HEIGHT; line++) clearl(line);
}

char gchar(int x, int y) {
	return terminal[x * 2 + y * VGA_WIDTH * 2];
}

void scrollup() {
	for (int y = 1; y < VGA_HEIGHT; y++) {
		for (int x = 0; x < VGA_WIDTH; x++) wchar(gchar(x,y),x,y-1);
	}
	clearl(VGA_HEIGHT-1);
}

void print(char* string) {
	while (*string != '\0') {
		//Print character
		if (*string == '\n') {	// Newline
			cursory++;
			cursorx = 0;
		}
		else if (*string == '\r') cursorx = 0;	// Carriage Return
		else if (*string == '\b') {	// Backspace
			if (cursorx == 0 && cursory != 0) {
				cursorx = VGA_WIDTH-1;
				cursory--;
			}
			else cursorx--;
			wchar('\0',cursorx,cursory);
		}
		else if (*string == '\t') {	// Tab
			cursorx += TAB_LENGTH - cursorx%TAB_LENGTH;
		}
		else {
			wchar(*string, cursorx, cursory);
			cursorx++;
		}
		//Wrap cursor
		if (cursorx >= VGA_WIDTH) {
			cursory++;
			cursorx = 0;
		}
		if (cursory >= VGA_HEIGHT) {
			cursory = VGA_HEIGHT-1;
			scrollup();
		}
		
		if (cursorx < 0) cursorx = 0;
		if (cursory < 0) cursory = 0;

		string++;
	}

	move_cursor(cursorx,cursory);
}

void printc(char c) {
	char cstr[2] = { c, '\0' };
	print(cstr);
}

char tohex(byte val) {
	char ret = '0';
	switch(val) {
		case 0x0:
			ret = '0';
			break;
		case 0x1:
			ret = '1';
			break;
		case 0x2:
			ret = '2';
			break;
		case 0x3:
			ret = '3';
			break;
		case 0x4:
			ret = '4';
			break;
		case 0x5:
			ret = '5';
			break;
		case 0x6:
			ret = '6';
			break;
		case 0x7:
			ret = '7';
			break;
		case 0x8:
			ret = '8';
			break;
		case 0x9:
			ret = '9';
			break;
		case 0xA:
			ret = 'A';
			break;
		case 0xB:
			ret = 'B';
			break;
		case 0xC:
			ret = 'C';
			break;
		case 0xD:
			ret = 'D';
			break;
		case 0xE:
			ret = 'E';
			break;
		case 0xF:
			ret = 'F';
			break;
	}
	return ret;
}

void printhex(byte val) {
	byte top = val >> 4;
	byte bot = val & 0x0f;
	char hex[6] = "0x00\0";
	hex[2] = tohex(top);
	hex[3] = tohex(bot);
	print(&hex[0]);
}

#endif
