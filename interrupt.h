// Interrupt Controller
#include "bool.h"
#include "type.h"

#ifndef INTERRUPT_H
#define INTERRUPT_H

bool interruptstate = false;

static inline void disableinterrupts() {
	__asm__ volatile ( "cli" );
	interruptstate = false;
}

static inline void enableinterrupts() {
	__asm__ volatile ( "sti" );
	interruptstate = true;
}

byte InterruptDefaultType = 0x8e;

struct InterruptDescriptor {
	word offset1;	// First half of offset
	word selector;
	byte zero;	// Set To 0
	byte type;	// Gate type, dpl, and p fields
	word offset2;	// Second half of offset
};

word createselector(word gdtindex) { // Only multiples of 8 (8,16,24,32) [Index Segment Descriptors in Global Descriptor Table]
	gdtindex && 0b1111111111111000;	// Use GDT with max privelege
	return gdtindex;
}

struct InterruptDescriptor createinterruptdescriptor(doubleword offset, word selector) {
	struct InterruptDescriptor ret;
	ret.zero = 0x00;
	ret.type = InterruptDefaultType;
	ret.selector = selector;
	word* offsetptr = (word*) &offset;
	ret.offset1 = offsetptr[0];
	ret.offset2 = offsetptr[1];
	return ret;
}

struct SegmentDescriptor {
	word limit1;
	word base1;
	byte base2;
	byte accessbyte;
	byte flagslimit2;
	byte base3;
};

struct SegmentDescriptor createsegmentdescriptor(doubleword address) {
	struct SegmentDescriptor ret;
	ret.limit1 = 0xffff;
	ret.accessbyte = 0b10011111; // Valid Segment, Highest Privelege, Code Segment, Executable, Grows Up, Readable, Accessed
	ret.flagslimit2 = 0b11001111;	// Limit is in 4KiB Pages and Segment is 32bit Protected Mode
	byte* addrptr = (byte*) &address;
	ret.base1 = addrptr[0];
	ret.base1 << 8;
	ret.base1 = addrptr[1];
	ret.base2 = addrptr[2];
	ret.base3 = addrptr[3];
	return ret;
}

// Interrupt Descriptor Table
struct InterruptDescriptor idt[256];
extern void* getidt() {
	return &idt;
}

// Global Descriptor Table (Leave [0] Empty)
struct SegmentDescriptor gdt[256];
extern void* getgdt() {
	return &gdt;
}

#endif
