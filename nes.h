#pragma once

#include "clock.h"
#include "ram.h"
#include "cpu.h"
#include "mmu.h"
#include "ppu.h"

class NES
{
public:
	Clock clock;

	RAM ram;
	CPU cpu;
	MMU mmu;
	PPU ppu;
public:
	NES();
	void start();
};
