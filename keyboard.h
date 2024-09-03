// Keyboard driver

#include "type.h"
#include "io.h"

#include "bool.h"

#include "buffer.h"

#ifndef KEYBOARD_H
#define KEYBOARD_H

byte getscancode() {
	return inb(0x60);
}
// List of all Keyboard Scancodes
enum Scancodes {

// Function Row
	ESC = 0x01,
	F1 = 0x3b,
	F2 = 0x3c,
	F3 = 0x3d,
	F4 = 0x3e,
	F5 = 0x3f,
	F6 = 0x40,
	F7 = 0x41,
	F8 = 0x42,
	F9 = 0x43,
	F10 = 0x44,
	F11 = 0x57,
	F12 = 0x58,
	

// Number Row
	BACKTICK = 0x29,
	NUM1 = 0x02,
	NUM2 = 0x03,
	NUM3 = 0x04,
	NUM4 = 0x05,
	NUM5 = 0x06,
	NUM6 = 0x07,
	NUM7 = 0x08,
	NUM8 = 0x09,
	NUM9 = 0x0a,
	NUM0 = 0x0b,
	MINUS = 0x0c,
	PLUS = 0x0d,
	BACKSPACE = 0x0e,
	

// First Row of Letters
	TAB = 0x0f,
	Q = 0x10,
	W = 0x11,
	E = 0x12,
	R = 0x13,
	T = 0x14,
	Y = 0x15,
	U = 0x16,
	I = 0x17,
	O = 0x18,
	P = 0x19,
	BRACKETLEFT = 0x1a,
	BRACKETRIGHT = 0x1b,
	SLASH = 0x2b,

// Second Row of Letters
	A = 0x1e,
	S = 0x1f,
	D = 0x20,
	F = 0x21,
	G = 0x22,
	H = 0x23,
	J = 0x24,
	K = 0x25,
	L = 0x26,
	SEMICOLON = 0x27,
	APOSTROPHE = 0x28,
	ENTER = 0x1c,

// Third Row of Letters
	LEFTSHIFT = 0x2a,
	Z = 0x2c,
	X = 0x2d,
	C = 0x2e,
	V = 0x2f,
	B = 0x30,
	N = 0x31,
	M = 0x32,
	COMMA = 0x33,
	PERIOD = 0x34,
	BACKSLASH = 0x35,
	RIGHTSHIFT = 0x36,

// Spacebar Row
	CTRL = 0x1d,
	ALT = 0x38,
	SPACE = 0x39,
	
// Arrow Keys
	LEFTARROW = 0x4b,
	RIGHTARROW = 0x4d,
	UPARROW = 0x48,
	DOWNARROW = 0x50,

// Locks
	CAPSLOCK = 0x3a,
	NUMLOCK = 0x45,

}; 

struct Keyevent {
	enum Scancodes key;
	bool pressed;
};

struct Keyevent prevent = { (enum Scancodes) 0x00, false };

bool pressedKeys[128];

struct Keyevent getKeyevent() {
	byte scancode = getscancode();
	bool pressed = true;
	if (scancode > 127) {
		pressed = false;
		scancode -= 128;
	}
	struct Keyevent keyevent = { (enum Scancodes) scancode, pressed };
	prevent = keyevent;

        byte index = (byte) keyevent.key;
        if (keyevent.pressed) pressedKeys[index] = true;
        else pressedKeys[index] = false;
	
	return keyevent;
}

bool isKeyPressed(enum Scancodes key) {
	byte index = (byte) key;
	return pressedKeys[index];
}

char toAscii(enum Scancodes scancode) {
	// Shift and Lock
	bool shift = pressedKeys[LEFTSHIFT] || pressedKeys[RIGHTSHIFT];
	bool capslock = pressedKeys[CAPSLOCK];
	bool numlock = pressedKeys[NUMLOCK];

	switch (scancode) {
		// Alphabet
		case A:
			if (shift ^ capslock) return 'A';
			else return 'a';
		case B:
			if (shift ^ capslock) return 'B';
			else return 'b';
		case C:
			if (shift ^ capslock) return 'C';
			else return 'c';
		case D:
			if (shift ^ capslock) return 'D';
			else return 'd';
		case E:
			if (shift ^ capslock) return 'E';
			else return 'e';
		case F:
			if (shift ^ capslock) return 'F';
			else return 'f';
		case G:
			if (shift ^ capslock) return 'G';
			else return 'g';
		case H:
			if (shift ^ capslock) return 'H';
			else return 'h';
		case I:
			if (shift ^ capslock) return 'I';
			else return 'i';
		case J:
			if (shift ^ capslock) return 'J';
			else return 'j';
		case K:
			if (shift ^ capslock) return 'K';
			else return 'k';
		case L:
			if (shift ^ capslock) return 'L';
			else return 'l';
		case M:
			if (shift ^ capslock) return 'M';
			else return 'm';
		case N:
			if (shift ^ capslock) return 'N';
			else return 'n';
		case O:
			if (shift ^ capslock) return 'O';
			else return 'o';
		case P:
			if (shift ^ capslock) return 'P';
			else return 'p';
		case Q:
			if (shift ^ capslock) return 'Q';
			else return 'q';
		case R:
			if (shift ^ capslock) return 'R';
			else return 'r';
		case S:
			if (shift ^ capslock) return 'S';
			else return 's';
		case T:
			if (shift ^ capslock) return 'T';
			else return 't';
		case U:
			if (shift ^ capslock) return 'U';
			else return 'u';
		case V:
			if (shift ^ capslock) return 'V';
			else return 'v';
		case W:
			if (shift ^ capslock) return 'W';
			else return 'w';
		case X:
			if (shift ^ capslock) return 'X';
			else return 'x';
		case Y:
			if (shift ^ capslock) return 'Y';
			else return 'y';
		case Z:
			if (shift ^ capslock) return 'Z';
			else return 'z';

		// Number Keys
		case NUM0:
			if (shift ^ numlock) return ')';
			else return '0';
		case NUM1:
			if (shift ^ numlock) return '!';
			else return '1';
		case NUM2:
			if (shift ^ numlock) return '@';
			else return '2';
		case NUM3:
			if (shift ^ numlock) return '#';
			else return '3';
		case NUM4:
			if (shift ^ numlock) return '$';
			else return '4';
		case NUM5:
			if (shift ^ numlock) return '%';
			else return '5';
		case NUM6:
			if (shift ^ numlock) return '^';
			else return '6';
		case NUM7:
			if (shift ^ numlock) return '&';
			else return '7';
		case NUM8:
			if (shift ^ numlock) return '*';
			else return '8';
		case NUM9:
			if (shift ^ numlock) return '(';
			else return '9';

		// Other Keys
		case SPACE:
			return ' ';
		case BACKTICK:
			if (shift) return '~';
			else return '`';
		case MINUS:
			if (shift) return '_';
			else return '-';
		case PLUS:
			if (shift) return '+';
			else return '=';
		case TAB:
			return '\t';
		case BRACKETLEFT:
			if (shift) return '{';
			else return '[';
		case BRACKETRIGHT:
			if (shift) return '}';
			else return ']';
		case SLASH:
			if (shift) return '|';
			else return '\\';
		case SEMICOLON:
			if (shift) return ':';
			else return ';';
		case APOSTROPHE:
			if (shift) return '"';
			else return '\'';
		case ENTER:
			return '\n';
		case BACKSPACE:
			return '\b';
		case ESC:
			return '\e';	
		case COMMA:
			if (shift) return '<';
			else return ',';
		case PERIOD:
			if (shift) return '>';
			else return '.';
		case BACKSLASH:
			if (shift) return '?';
			else return '/';

		// Arrow Keys (ASCII Device Control)
		case UPARROW:
			return 0x11;
		case DOWNARROW:
			return 0x12;
		case LEFTARROW:
			return 0x13;
		case RIGHTARROW:
			return 0x14;

		// Unknown Keys
		default: // Unknown or Non Character Scancode
			return '\0';
	}
}

struct instringbit {	// Input string return value
	bool done;	// Delimiter reached
	bool changed;	// String Changed?
	char c;		// Character Added
};
// Processes keyinputs and returns true when done
struct instringbit inputstring(struct buffer* buf, char delimiter) {
	struct instringbit ret = {false,false,0x00};
	struct Keyevent previous = prevent;
	struct Keyevent event = getKeyevent();
	if (event.pressed == false) return ret;
	if (event.key == previous.key && previous.pressed) return ret;
	char c = toAscii(event.key);
	if (c == 0x00) return ret;
	else if (c == delimiter) {
		ret.done = true;
		return ret;
	}
	else if (c == '\b') {
		bufpop(buf);
		if (buf->error) return ret;
	}
	else bufpush(c,buf);
	ret.changed = true;
	ret.c = c;
	return ret;
}

#endif
