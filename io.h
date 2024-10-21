#include "type.h"

#ifndef IO_LIB
#define IO_LIB

static inline void outb(word port, byte val)
{
    __asm__ volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

static inline byte inb(word port)
{
    byte result;
    __asm__ volatile ( "inb %w1, %b0" : "=a"(result) : "Nd"(port) : "memory");
    return result;
}

static inline void outw(word port, word val)
{
    __asm__ volatile ( "outw %0, %1" : : "a"(val), "Nd"(port) );
}

static inline word inw(word port)
{
    byte result;
    __asm__ volatile ( "inw %w1, %b0" : "=a"(result) : "Nd"(port) : "memory");
    return result;
}
#endif
