#include "ppu.h"


PPU::PPU()
	: PPUCTRL(0)
	, PPUMASK(0)
	, PPUSTATUS(0)
	, OAMADDR(0)
	, OAMDATA(0)
	, PPUSCROLL(0)
	, PPUADDR(0)
	, PPUDATA(0)
	, OAMDMA(0)
	, regs1(&PPUCTRL, 8)
{
}

Memory & PPU::getRegs()
{
	return regs1;
}
