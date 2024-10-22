// BitOS Buffer Implementation

#include "bool.h"

#ifndef BUFFER_H
#define BUFFER_H

#define BUFFER_LENGTH 2048
struct buffer {
	char data[BUFFER_LENGTH];
	void* pointer;
	bool error;	// Was there an error? (Popping the start or pushing onto the end)
};

void bufinit(struct buffer* buf) {
	buf->pointer = &buf->data[0];
	for (unsigned int i = 0; i < BUFFER_LENGTH; i++) buf->data[i] = 0x00;
}

void bufpush(char data, struct buffer* buf) {
	if (buf->pointer == &buf->data[BUFFER_LENGTH]) {	// Pushing end error
		buf->error = true;
		
	}
	else {
		buf->error = false;
		char* end = (char*) buf->pointer;
		*end = data;
		buf->pointer++;
	}
}

char bufpop(struct buffer* buf) {
	if (buf->pointer == &buf->data[0]) {	// Popping start error
		buf->error = true;
		return (char) 0x00;
	}
	else buf->error = false;
	char* loc = (char*) buf->pointer;
	buf->pointer--;
	char data = *loc;
	*loc = 0x00;
	return data;
}

void bufclear(struct buffer* buf) {
	bufinit(buf);
}

#endif // !BUFFER_H
