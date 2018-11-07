#pragma once

#include "ctrl_bus.h"
#include "clock.h"
#include "ram.h"
#include "cpu.h"
#include "ppu.h"
#include "mem_bus.h"
#include "cartridge_slot.h"

#include <utility>

class NES
{
public:
	Clock clock;

	CtrlBus ctrl;

	MemBus bus;
	MemBus vbus;

	CPU cpu;
	PPU ppu;

	RAM ram;
	RAM vram;

	CartridgeSlot cartridgeSlot;
public:
	NES();
	inline void run() { clock.cycle(); }
	inline void setCartridge(Cartridge * cartridge) { cartridgeSlot.setCartridge(cartridge); };
	void memMap();
	void vmemMap();
	std::pair<Memory &, uint16_t> resolveCPU(uint16_t address);
	std::pair<Memory &, uint16_t> resolvePPU(uint16_t address);
};
