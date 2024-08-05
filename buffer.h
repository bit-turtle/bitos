// BitOS Buffer Implementation

#include "bool.h"

#ifndef BUFFER_H
#define BUFFER_H

struct buffer {
  char data[2048];
  void* pointer;
};

void bufinit(struct buffer* buf) {
  buf->pointer = &buf->data[0];
}

void bufpush(char data, struct buffer* buf) {
  char* end = (char*) buf->pointer;
  *end = data;
  buf->pointer++;
}

char bufpop(struct buffer* buf) {
  char* loc = (char*) buf->pointer;
  buf->pointer--;
  char data = *loc;
  *loc = 0x00;
  return data;
}

#endif // !BUFFER_H
