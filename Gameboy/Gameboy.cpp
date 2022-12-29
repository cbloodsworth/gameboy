// Gameboy.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include "emulator.h"


int main()
{

	FILE* in;
	in = fopen("Zelda.gb", "rb");
	fread(m_CartridgeMemory, 1, 0x200000, in);
	fclose(in);

}

