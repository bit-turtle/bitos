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

void getword(struct buffer* buf, char* str, unsigned int index) {
	unsigned int words = 0;
	while (*str != 0x00) {
		if (*str == ' ') words ++;
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
		struct buffer cmd;
		bufinit(&cmd);
		getword(&cmd, &input.data[0], 0);
		struct buffer arg;
		bufinit(&arg);
		substr(&arg, &input.data[0], strlen(&cmd.data[0]));
		if (strcmp(&cmd.data[0], "reboot")) {
			print("Rebooting...\n");
			done = true;
		}
		else if (strcmp(&cmd.data[0], "clear")) {
			clear();	// Clear Screen
			move_cursor(0,0);
		}
		else if (strcmp(&cmd.data[0], "print")) {
			// Print String
			print(&arg.data[0]);
			// Trailing newline
			print("\n");
		}
		else if (strcmp(&cmd.data[0], "echo")) {
			// Format and Print String
			struct buffer fmt;
			bufinit(&fmt);
			formatstr(&fmt, &arg.data[0]);
			print(&fmt.data[0]);
			// Trailing newline
			print("\n");
		}
		else {
			print("bitsh: Unknown Command: ");
			print(&cmd.data[0]);
			print("\n");
		}
	}
}
