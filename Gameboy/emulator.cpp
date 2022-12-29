#include "emulator.h"

void Emulator::Init() 
{
	memset(m_CartridgeMemory, 0, sizeof(m_CartridgeMemory));
	in = fopen("Zelda.gb", "rb");
	fread(m_CartridgeMemory, 1, 0x200000, in);
	fclose(in);

	m_ProgramCounter = 0x100;
	m_RegisterAF.reg = 0x01B0;
	m_RegisterBC.reg = 0x0013;
	m_RegisterDE.reg = 0x00D8;
	m_RegisterHL.reg = 0x014D;
	m_StackPointer.reg = 0xFFFE;
	m_Rom[0xFF05] = 0x00;
	m_Rom[0xFF06] = 0x00;
	m_Rom[0xFF07] = 0x00;
	m_Rom[0xFF10] = 0x80;
	m_Rom[0xFF11] = 0xBF;
	m_Rom[0xFF12] = 0xF3;
	m_Rom[0xFF14] = 0xBF;
	m_Rom[0xFF16] = 0x3F;
	m_Rom[0xFF17] = 0x00;
	m_Rom[0xFF19] = 0xBF;
	m_Rom[0xFF1A] = 0x7F;
	m_Rom[0xFF1B] = 0xFF;
	m_Rom[0xFF1C] = 0x9F;
	m_Rom[0xFF1E] = 0xBF;
	m_Rom[0xFF20] = 0xFF;
	m_Rom[0xFF21] = 0x00;
	m_Rom[0xFF22] = 0x00;
	m_Rom[0xFF23] = 0xBF;
	m_Rom[0xFF24] = 0x77;
	m_Rom[0xFF25] = 0xF3;
	m_Rom[0xFF26] = 0xF1;
	m_Rom[0xFF40] = 0x91;
	m_Rom[0xFF42] = 0x00;
	m_Rom[0xFF43] = 0x00;
	m_Rom[0xFF45] = 0x00;
	m_Rom[0xFF47] = 0xFC;
	m_Rom[0xFF48] = 0xFF;
	m_Rom[0xFF49] = 0xFF;
	m_Rom[0xFF4A] = 0x00;
	m_Rom[0xFF4B] = 0x00;
	m_Rom[0xFFFF] = 0x00;
}

// Emulation loop
void Emulator::Update()
{
	// The gameboy executes 4194304 clock cycles a second, and
	// refreshes 60 times a second. As such, the maximum amount
	// of clock cycles in one second will be 69905.
	const int MAXCYCLES = 69905;
	int cyclesThisUpdate = 0;

	while (cyclesThisUpdate < MAXCYCLES) {
		int cycles = ExecuteNextOpcode();
		cyclesThisUpdate += cycles;
		UpdateTimes(cycles);
		UpdateGraphics(cycles);
		DoInterrupts();
	}
	
	RenderScreen();
}

void Emulator::WriteMemory(WORD address, BYTE data) 
{
	// Addresses 0x0000 - 0x8000 are read only
	if (address < 0x8000) {}

	// Write to ECHO, but also write to RAM
	else if ((address >= 0xE000) && (address < 0xFE00)) {
		m_Rom[address] = data; // Write to ECHO
		WriteMemory(address - 0x2000, data); // Write to RAM
	}
	
	// More off-limits
	else if ((address >= 0xFEA0) && (address < 0xFEFF)) {}

	// No control necessary, just write
	else {
		m_Rom[address] = data;
	}
}