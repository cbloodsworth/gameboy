#include <iostream>
#pragma once

// Flags for the F register, each value is the
// bit in the flag register for this flag
#define FLAG_Z 7 // Zero flag
#define FLAG_N 6 // Subtraction flag
#define FLAG_H 5 // Half-carry flag
#define FLAG_C 4 // Carry flag

// TYPEDEFS
// The gameboy has a word size of 16 bits
typedef unsigned char BYTE;
typedef char SIGNED_BYTE;
typedef unsigned short WORD;
typedef signed short SIGNED_WORD;


class Emulator {
	BYTE m_ScreenData[160][144][3];
	BYTE m_CartridgeMemory[0x200000];
	BYTE m_Rom[0x10000];

	FILE* in;
	// The gameboy has 8 registers: A,B,C,D,E,F,H,L.
	// Each are 1 byte in length. Often times the registers 
	// are combined to form one word length: AF, BC, DE, HL.
	// We will emulate that using a union:
	// Every field in a union occupies the same region in memory.
	// Example: m_RegisterAF.reg = 0xAABB
	//			m_registerAF.hi == 0xAA
	//			m_registerAF.lo == 0xBB
	union Register
	{
		WORD reg;
		struct
		{
			BYTE lo;
			BYTE hi;
		};
	};

	WORD m_ProgramCounter;
	Register m_StackPointer;


	Register m_RegisterAF;
	Register m_RegisterBC;
	Register m_RegisterDE;
	Register m_RegisterHL;
	
public:
	void Init();
	void Update();
	void WriteMemory(WORD address, BYTE data);
	void ReadMemory();

};