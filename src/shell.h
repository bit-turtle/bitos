// Simple Shell for Bit OS
#include "type.h"
#include "terminal.h"
#include "keyboard.h"
#include "buffer.h"

void shellinput(struct buffer* buf) {
	bufinit(buf);
	struct instringbit input;
	do {
		input = inputstring(buf,'\n');
		if (input.changed)
			printc(input.c);
		update_cursor_position();
	}
	while (!input.done);
}

bool strcmp(char* str1,  char* str2) {
	bool match = true;
	while (*str1 != 0x00 && *str2 != 0x00) {
		if (*str1 != *str2) {
			match = false;
			break;
		}
		str1++;
		str2++;
	}
	if (*str1 != *str2) match = false;
	return match;
}

void getword(struct buffer* buf, char* str, unsigned int index, char delim) {
	unsigned int words = 0;
	while (*str != 0x00) {
		if (*str == delim) words ++;
		else if (words == index) bufpush(*str, buf);
		str++;
	}
}

unsigned int strlen(char* str) {
	unsigned int ret = 0;
	while (*str != 0x00) {
		ret++;
		str++;
	}
	return ret;
}

void substr(struct buffer* buf, char* str, unsigned int index) {
	for (;index > 0; index--) str++;
	while (*str != 0x00) bufpush(*++str, buf);
}

void formatstr(struct buffer* buf, char* str) {
	bool escape = false;
	while (*str != 0x00) {
		if (*str == '\\' && escape == false) escape = true;
		else {
			char c = *str;
			if (escape) {
				switch (*str) {
					// \\ Escaped Escape
					case '\\':
						c = '\\';
						break;
					// \n Newline escape
					case 'n':
						c = '\n';
						break;
					// \r Carriage Return
					case 'r':
						c = '\r';
						break;
					// Default: Pretend it wasn't escaped (Example: \m = "\m")
					default:
						bufpush('\\', buf);
				}
			}
			bufpush(c, buf);
			escape = false;
		}
		str++;
	}
}

long numstr(char* str) {
	long number = 0;
	while (*str != 0x00) {
		bool good = true;
		byte digit = 0;
		switch (*str) {
			case '0':
				digit = 0;
				break;
			case '1':
				digit = 1;
				break;
			case '2':
				digit = 2;
				break;
			case '3':
				digit = 3;
				break;
			case '4':
				digit = 4;
				break;
			case '5':
				digit = 5;
				break;
			case '6':
				digit = 6;
				break;
			case '7':
				digit = 7;
				break;
			case '8':
				digit = 8;
				break;
			case '9':
				digit = 9;
				break;
			default:
				print("numstr: Unexpected Character: ");
				printc(*str);
				print("\n");
				good = false;
		}
		if (good) {
			number *= 10;
			number += digit;
		}
		else break;
	}
	return number;
}

bool procshell(struct buffer* line) {
	bool done = false;
	struct buffer cmd;
	bufinit(&cmd);
	getword(&cmd, line->start, 0, ' ');
	struct buffer arg;
	bufinit(&arg);
	substr(&arg, line->start, strlen(cmd.start));
	if (strcmp(cmd.start, "reboot")) {	// `reboot`: Reboot the computer
		print("Rebooting...\n");
		done = true;	// End shell
	}
	else if (strcmp(cmd.start, "clear")) {	// `clear`: Clear Screen
		clear();
		move_cursor(0,0);
	}
	else if (strcmp(cmd.start, "print")) {	// `print`: Unformatted Print
		// Print String
		print(arg.start);
		// Trailing newline
		print("\n");
	}
	else if (strcmp(cmd.start, "echo")) {	// `echo`: Formatted Print
		// Format and Print String
		struct buffer fmt;
		bufinit(&fmt);
		formatstr(&fmt, arg.start);
		print(fmt.start);
		// Trailing newline
		print("\n");
	}
	else {
		print("bitsh: Unknown Command: ");
		print(cmd.start);
		print("\n");
	}
	return done;
}

void shell() {
	print("\n");
	// Create input buffer
	struct buffer input;
	bufinit(&input);
	// Main shell loop
	bool done = false;
	while (!done) {
		print("> ");
		shellinput(&input);
		print("\n");
		done = procshell(&input);
	}
}
