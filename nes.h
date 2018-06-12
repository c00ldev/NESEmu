#pragma once

#include "clock.h"
#include "ram.h"
#include "cpu.h"
#include "mmu.h"

class NES
{
public:
	Clock clock;

	RAM ram;
	CPU cpu;
	MMU mmu;
public:
	NES();
};
