#pragma once

#include "ctrl_bus.h"
#include "clock.h"
#include "ram.h"
#include "cpu.h"
#include "ppu.h"
#include "mem_bus.h"
#include "cartridge_slot.h"

class NES
{
public:
	CtrlBus ctrl;

	Clock clock;

	MemBus bus;
	MemBus vbus;

	RAM ram;
	RAM vram;

	CPU cpu;
	//PPU ppu;

	CartridgeSlot cartridgeSlot;
public:
	NES();
	void powerUp();
	void run();
	void setCartridge(Cartridge * cartridge);
	void memMap();
	void vmemMap();
};
