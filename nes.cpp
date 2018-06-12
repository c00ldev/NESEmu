#include "nes.h"

NES::NES()
	: clock(21477272)
	, cpu(mmu)
	, ram(0x800)
	, mmu()
{
	clock.addHandler(12, cpu);
	mmu.map(0x0000, ram);
}
