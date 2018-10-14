#pragma once

#include "clock.h"
#include "ram.h"
#include "cpu.h"
#include "ppu.h"
#include "mem_bus.h"
#include "cartridge_slot.h"

class NES
{
public:
	Clock clock;

	RAM ram;
	RAM vram;

	CPU cpu;
	PPU ppu;

	CartridgeSlot cartridgeSlot;

	MemBus mem;
	VMemBus vmem;
public:
	NES();
	void powerUp();
	void run();
	void setCartridge(Cartridge * cartridge);
};
