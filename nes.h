#pragma once

#include "clock.h"
#include "ram.h"
#include "cpu.h"
#include "mmu.h"

#include "nrom.h"

class NES
{
public:
	Clock clock;

	RAM ram;
	CPU cpu;
	MMU mmu;

	NROM * nrom;
public:
	NES();
	void setROM(NROM * nrom1);
};
