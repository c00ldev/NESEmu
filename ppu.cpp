#include "ppu.h"

#include "ctrl_bus.h"
#include "mem_bus.h"


PPU::PPU(CtrlBus & ctrl, MemBus & bus)
	: ctrl(ctrl)
	, bus(bus)
	, palettes(0x20)
	, PPUCTRL(0)
	, PPUMASK(0)
	, PPUSTATUS(0)
	, OAMADDR(0)
	, OAMDATA(0)
	, PPUSCROLL(0)
	, PPUADDR(0)
	, PPUDATA(0)
	, OAMDMA(0)
	, regs1(&PPUCTRL, 8)
	, OAM(0x100)
{
}

void PPU::tick()
{

}

Memory & PPU::getRegs()
{
	return regs1;
}

Memory & PPU::getPalettes()
{
	return palettes;
}
